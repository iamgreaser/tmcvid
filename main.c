#include <stdint.h>

#include "gba.h"
#define NULL ((void *)0)

#define CUCK_DEINT
#include "cuckvid.c"

#define F3M_FREQ 16384
#define F3M_BUFLEN 273
#define ABLK_MAX 0x200

static uint8_t obuf[3][F3M_BUFLEN];
static int ablk_pos = 0;
static int ablk_pred = 0;
static int ablk_step = 0;
static int ablk_len = 512-8;
static uint32_t ablk_val = 0;
static uint8_t *adpcm_data;
static uint8_t *video_data;

const int8_t ima_index_table[16] = {
  -1, -1, -1, -1, 2, 4, 6, 8,
  -1, -1, -1, -1, 2, 4, 6, 8,
}; 

const int16_t ima_step_table[89] = { 
  7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 
  19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 
  50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 
  130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
  337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
  876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 
  2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
  5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 
  15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767,
};

volatile uint8_t mod_bump = 0;
volatile uint8_t vint_get = 0;
volatile int vid_frame_ctr = 0;
volatile int trace_page = 0;
int vid_frame_ctr_expect = 0;
int keypad = 0;
int okeypad = 0;

static void adpcm_update(uint8_t *buf)
{
	int i;

	for(i = 0; i < F3M_BUFLEN; i++)
	{
		if(ablk_pos == 0)
		{
			// Read header
			ablk_pred = (int)*(int16_t *)adpcm_data; adpcm_data += 2;
			ablk_step = (int)*(uint8_t *)adpcm_data; adpcm_data += 2;
			if(ablk_step > 88) ablk_step = 88;
		}

		if((ablk_pos & 7) == 0)
		{
			// Read sample
			ablk_val = *(uint32_t *)adpcm_data; adpcm_data += 4;
		}

		// Read val
		int val = (ablk_val>>((ablk_pos&7)*4))&0xF;
		int mag = (((val&7)<<1)+1) * (int)ima_step_table[ablk_step];
		mag >>= 3;
		if(val&8) ablk_pred -= mag;
		else ablk_pred += mag;
		if(ablk_pred < -0x8000) ablk_pred = -0x8000;
		if(ablk_pred >  0x7FFF) ablk_pred =  0x7FFF;
		ablk_step += ima_index_table[val];
		if(ablk_step < 0) ablk_step = 0;
		if(ablk_step > 88) ablk_step = 88;

		// Emit
		*(buf++) = ablk_pred>>8;

		// Advance
		ablk_pos++;

		if(ablk_pos >= ablk_len) ablk_pos = 0;
	}
}

static void isr_handler(void)
{
	//asm("mov pc, lr;\n");
	uint16_t isr_state = IF;

	if(isr_state & 0x0001)
	{
		// Set correct rendering page
		DISPCNT = ((DISPCNT & ~(1<<4)) | 
			(trace_page == 0 ? (1<<4) : 0));

		if(mod_bump != 0)
		{
			// Start DMA1 (sound/music)
			DMA1CNT_H = 0x0000;
			DMA1SAD = obuf[0];
			DMA1DAD = &FIFO_A;
			DMA1CNT_H = 0xB600;

			mod_bump = 0;
		}

		// Acknowledge vblank
		IF = 0x0001;
		ISR_flags |= 0x0001;
		vint_get = 1;
		vid_frame_ctr++;
	}

	//asm("mov r0, #0x08000000 ; bx r0 ;\n");
}

static void wait_timer()
{
	while(!(ISR_flags & 0x0001)) {}
	ISR_flags &= ~0x0001;
}

int decode_line = 0;
void game_update_disp(void)
{
	//
	int i;
	for(i = 0; i < 8; i++)
	{
		cuck_decode_line(decode_line,
			(uint8_t *)(VRAM0D + 0x5000*trace_page),
			(uint8_t *)(VRAM0D + 0x5000*(1-trace_page)),
			video_data);
		decode_line++;
		if(decode_line >= 20)
		{
			decode_line = 0;
			video_data += 30*20*2;
			trace_page = 1-trace_page;
		}
	}
}

void game_update_tick(void)
{
	
}

int fs_get(const char *name, void **loc, uint32_t *len)
{
	const uint64_t *match = (const uint64_t *)name;

	void *fol = (void *)0x080000C4;

	while(*((uint32_t *)(fol+0x0)) != 0)
	{
		void *floc = *((void **)(fol+0x0));
		uint32_t flen = *((uint32_t *)(fol+0x4));
		uint64_t fname = *((uint64_t *)(fol+0x8));
		if(fname == *match)
		{
			if(loc != NULL) *loc = floc;
			if(len != NULL) *len = flen;
			return 1;
		}

		fol += 0x10;
	}

	return 0;
}

int fs_get_must(const char *name, void **loc, uint32_t *len)
{
	if(!fs_get(name, loc, len))
	{
		// lock up
		VPAL0[0] = 0xFFF;
		for(;;) {}
	}
}

void _start(void)
{
	int x, y, i;

	//WAITCNT = 0x431B;

	DISPCNT = 0x0404;
	IME = 0;
	ISR_funct = isr_handler;
	IE = 0x0001;
	IME = 1;

	// Clear VRAM and OAM
	for(i = 0; i < (0x18000>>2); i++)
		VRAM0D32[i] = 0;

	for(i = 0; i < 128; i++)
	{
		VOAM16[i*4+0] = 0x02F0;
		VOAM16[i*4+1] = 0x0000;
		VOAM16[i*4+2] = 0x0000;
		VOAM16[i*4+3] = 0x0000;
	}

	// Generate 233 RGB palette
	for(i = 0; i < 256; i++)
	{
		int r = (i>>6)&3;
		int g = (i>>3)&7;
		int b = (i>>0)&7;

		r = (r + (r<<2) + (r<<4))>>1;
		g = (g + (g<<3))>>1;
		b = (b + (b<<3))>>1;

		r <<= 0;
		g <<= 5;
		b <<= 10;

		VPAL0[i] = r|g|b;
		VPAL1[i] = r|g|b;
	}

	// Load images
	//tga_load(*(uint8_t **)0x080000C8, VRAM0D + ((0x00000)>>1), VPAL0, 128, 128);

	// Set up audio
	fs_get_must("vid01s  ", (void **)&adpcm_data, NULL);
	fs_get_must("vid01v  ", (void **)&video_data, NULL);

	adpcm_data = *(uint8_t **)0x080000C4;
	fs_get_must("vid01s  ", (void **)&adpcm_data, NULL);
	adpcm_data += 0x3C;
	adpcm_update(obuf[0]);
	adpcm_update(obuf[1]);

	// Init sound properly
	SOUNDCNT_X = (1<<7);
	SOUNDCNT_L = (7<<0) | (7<<4);
	SOUNDCNT_H = (2<<0) | (1<<2) | (1<<11) | (3<<8);

	TM0CNT_H = 0;

	DMA1SAD = obuf[0];
	DMA1DAD = &FIFO_A;
	DMA1CNT_H = 0xB600;

	TM0CNT_L = 0x10000-((1<<24)/F3M_FREQ);
	TM0CNT_H = 0x0080;

	// Enable interrupts and run
	DISPSTAT |= 0x0008;
	for(;;)
	{
		wait_timer();
		adpcm_update(obuf[0]);
		// copy a bit to the end
		((uint32_t *)(obuf[2]))[0] = ((uint32_t *)(obuf[0]))[0];
		((uint32_t *)(obuf[2]))[1] = ((uint32_t *)(obuf[0]))[1];
		((uint32_t *)(obuf[2]))[2] = ((uint32_t *)(obuf[0]))[2];
		((uint32_t *)(obuf[2]))[3] = ((uint32_t *)(obuf[0]))[3];
		mod_bump = 1;
		game_update_disp();
		game_update_tick();
		wait_timer();
		adpcm_update(obuf[1]);
		game_update_disp();
		game_update_tick();
	}

	for(;;) {}
}

