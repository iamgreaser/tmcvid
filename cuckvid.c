#include <stdint.h>

#ifdef CUCK_ENCODER
static int8_t cuck_dithtab[4][4] = {
	{-8,+0,-6,+2},
	{+4,-4,+6,-2},
	{-5,+3,-7,+1},
	{+7,-1,+5,-3},
};
#endif

/*
pattern codings:

0YX: 

---: 01234567
000: 11111111
001: reserved
002: 00001111
003: 11110000
004: 00110011
005: 11001100
006: 01010101
007: 10101010

Y follows suit

special case:
001 = reset to solid colour
*/

const uint32_t cuck_dectab_tobytes[16] = {
	0x00000000, 0x000000FF, 0x0000FF00, 0x0000FFFF,
	0x00FF0000, 0x00FF00FF, 0x00FFFF00, 0x00FFFFFF,
	0xFF000000, 0xFF0000FF, 0xFF00FF00, 0xFF00FFFF,
	0xFFFF0000, 0xFFFF00FF, 0xFFFFFF00, 0xFFFFFFFF,
};

#define CUCK_DECTYPES 170
const uint32_t cuck_dectab[CUCK_DECTYPES*2] = {
	0xFFFFFFFFU, 0xFFFFFFFFU,
	0xFFFFFFFFU, 0xFFFFFFFFU,
	0x0F0F0F0FU, 0x0F0F0F0FU,
	0xF0F0F0F0U, 0xF0F0F0F0U,
	0xFFFFFFFFU, 0x00000000U,
	0x00000000U, 0xFFFFFFFFU,
	0x0F0F0F0FU, 0x00000000U,
	0xF0F0F0F0U, 0x00000000U,
	0x00000000U, 0x0F0F0F0FU,
	0x00000000U, 0xF0F0F0F0U,
	0x03030303U, 0x00000000U,
	0x00000F0FU, 0x00000000U,
	0x0C0C0C0CU, 0x00000000U,
	0x0F0F0000U, 0x00000000U,
	0x30303030U, 0x00000000U,
	0x00000000U, 0x00000F0FU,
	0xC0C0C0C0U, 0x00000000U,
	0x00000000U, 0x0F0F0000U,
	0x00000000U, 0x03030303U,
	0x0000F0F0U, 0x00000000U,
	0x00000000U, 0x0C0C0C0CU,
	0xF0F00000U, 0x00000000U,
	0x00000000U, 0x30303030U,
	0x00000000U, 0x0000F0F0U,
	0x00000000U, 0xC0C0C0C0U,
	0x00000000U, 0xF0F00000U,
	0x00000303U, 0x00000000U,
	0x00000C0CU, 0x00000000U,
	0x00003030U, 0x00000000U,
	0x0000C0C0U, 0x00000000U,
	0x03030000U, 0x00000000U,
	0x0C0C0000U, 0x00000000U,
	0x30300000U, 0x00000000U,
	0xC0C00000U, 0x00000000U,
	0x00000000U, 0x00000303U,
	0x00000000U, 0x00000C0CU,
	0x00000000U, 0x00003030U,
	0x00000000U, 0x0000C0C0U,
	0x00000000U, 0x03030000U,
	0x00000000U, 0x0C0C0000U,
	0x00000000U, 0x30300000U,
	0x00000000U, 0xC0C00000U,
	0x00000003U, 0x00000000U,
	0x00000101U, 0x00000000U,
	0x0000000CU, 0x00000000U,
	0x01010000U, 0x00000000U,
	0x00000030U, 0x00000000U,
	0x00000000U, 0x00000101U,
	0x000000C0U, 0x00000000U,
	0x00000000U, 0x01010000U,
	0x00000300U, 0x00000000U,
	0x00000202U, 0x00000000U,
	0x00000C00U, 0x00000000U,
	0x02020000U, 0x00000000U,
	0x00003000U, 0x00000000U,
	0x00000000U, 0x00000202U,
	0x0000C000U, 0x00000000U,
	0x00000000U, 0x02020000U,
	0x00030000U, 0x00000000U,
	0x00000404U, 0x00000000U,
	0x000C0000U, 0x00000000U,
	0x04040000U, 0x00000000U,
	0x00300000U, 0x00000000U,
	0x00000000U, 0x00000404U,
	0x00C00000U, 0x00000000U,
	0x00000000U, 0x04040000U,
	0x03000000U, 0x00000000U,
	0x00000808U, 0x00000000U,
	0x0C000000U, 0x00000000U,
	0x08080000U, 0x00000000U,
	0x30000000U, 0x00000000U,
	0x00000000U, 0x00000808U,
	0xC0000000U, 0x00000000U,
	0x00000000U, 0x08080000U,
	0x00000000U, 0x00000003U,
	0x00001010U, 0x00000000U,
	0x00000000U, 0x0000000CU,
	0x10100000U, 0x00000000U,
	0x00000000U, 0x00000030U,
	0x00000000U, 0x00001010U,
	0x00000000U, 0x000000C0U,
	0x00000000U, 0x10100000U,
	0x00000000U, 0x00000300U,
	0x00002020U, 0x00000000U,
	0x00000000U, 0x00000C00U,
	0x20200000U, 0x00000000U,
	0x00000000U, 0x00003000U,
	0x00000000U, 0x00002020U,
	0x00000000U, 0x0000C000U,
	0x00000000U, 0x20200000U,
	0x00000000U, 0x00030000U,
	0x00004040U, 0x00000000U,
	0x00000000U, 0x000C0000U,
	0x40400000U, 0x00000000U,
	0x00000000U, 0x00300000U,
	0x00000000U, 0x00004040U,
	0x00000000U, 0x00C00000U,
	0x00000000U, 0x40400000U,
	0x00000000U, 0x03000000U,
	0x00008080U, 0x00000000U,
	0x00000000U, 0x0C000000U,
	0x80800000U, 0x00000000U,
	0x00000000U, 0x30000000U,
	0x00000000U, 0x00008080U,
	0x00000000U, 0xC0000000U,
	0x00000000U, 0x80800000U,
	0x00000001U, 0x00000000U,
	0x00000002U, 0x00000000U,
	0x00000004U, 0x00000000U,
	0x00000008U, 0x00000000U,
	0x00000010U, 0x00000000U,
	0x00000020U, 0x00000000U,
	0x00000040U, 0x00000000U,
	0x00000080U, 0x00000000U,
	0x00000100U, 0x00000000U,
	0x00000200U, 0x00000000U,
	0x00000400U, 0x00000000U,
	0x00000800U, 0x00000000U,
	0x00001000U, 0x00000000U,
	0x00002000U, 0x00000000U,
	0x00004000U, 0x00000000U,
	0x00008000U, 0x00000000U,
	0x00010000U, 0x00000000U,
	0x00020000U, 0x00000000U,
	0x00040000U, 0x00000000U,
	0x00080000U, 0x00000000U,
	0x00100000U, 0x00000000U,
	0x00200000U, 0x00000000U,
	0x00400000U, 0x00000000U,
	0x00800000U, 0x00000000U,
	0x01000000U, 0x00000000U,
	0x02000000U, 0x00000000U,
	0x04000000U, 0x00000000U,
	0x08000000U, 0x00000000U,
	0x10000000U, 0x00000000U,
	0x20000000U, 0x00000000U,
	0x40000000U, 0x00000000U,
	0x80000000U, 0x00000000U,
	0x00000000U, 0x00000001U,
	0x00000000U, 0x00000002U,
	0x00000000U, 0x00000004U,
	0x00000000U, 0x00000008U,
	0x00000000U, 0x00000010U,
	0x00000000U, 0x00000020U,
	0x00000000U, 0x00000040U,
	0x00000000U, 0x00000080U,
	0x00000000U, 0x00000100U,
	0x00000000U, 0x00000200U,
	0x00000000U, 0x00000400U,
	0x00000000U, 0x00000800U,
	0x00000000U, 0x00001000U,
	0x00000000U, 0x00002000U,
	0x00000000U, 0x00004000U,
	0x00000000U, 0x00008000U,
	0x00000000U, 0x00010000U,
	0x00000000U, 0x00020000U,
	0x00000000U, 0x00040000U,
	0x00000000U, 0x00080000U,
	0x00000000U, 0x00100000U,
	0x00000000U, 0x00200000U,
	0x00000000U, 0x00400000U,
	0x00000000U, 0x00800000U,
	0x00000000U, 0x01000000U,
	0x00000000U, 0x02000000U,
	0x00000000U, 0x04000000U,
	0x00000000U, 0x08000000U,
	0x00000000U, 0x10000000U,
	0x00000000U, 0x20000000U,
	0x00000000U, 0x40000000U,
	0x00000000U, 0x80000000U,
};

#define CUCK_YTAB_SUB(a,b,c,d,e,f,g,h) \
	(0xFF^((a<<0)|(b<<1)|(c<<2)|(d<<3)|(e<<4)|(f<<5)|(g<<6)|(h<<7))) \

#define CUCK_YTAB(a,b,c,d,e,f,g,h) \
	(CUCK_YTAB_SUB(a,b,c,d,e,f,g,h)^((CUCK_YTAB_SUB(a,b,c,d,e,f,g,h)<<1)&0xFF)), \

static const uint8_t cuck_pattab_y[8] = {
	CUCK_YTAB(1,1,1,1,1,1,1,1)
	CUCK_YTAB(1,1,1,1,1,1,1,1)
	CUCK_YTAB(0,0,0,0,1,1,1,1)
	CUCK_YTAB(1,1,1,1,0,0,0,0)
	CUCK_YTAB(0,0,1,1,0,0,1,1)
	CUCK_YTAB(1,1,0,0,1,1,0,0)
	CUCK_YTAB(0,1,0,1,0,1,0,1)
	CUCK_YTAB(1,0,1,0,1,0,1,0)
};

#ifdef CUCK_ENCODER
static const uint8_t cuck_pattab_y_sub[8] = {
	CUCK_YTAB_SUB(1,1,1,1,1,1,1,1),
	CUCK_YTAB_SUB(1,1,1,1,1,1,1,1),
	CUCK_YTAB_SUB(0,0,0,0,1,1,1,1),
	CUCK_YTAB_SUB(1,1,1,1,0,0,0,0),
	CUCK_YTAB_SUB(0,0,1,1,0,0,1,1),
	CUCK_YTAB_SUB(1,1,0,0,1,1,0,0),
	CUCK_YTAB_SUB(0,1,0,1,0,1,0,1),
	CUCK_YTAB_SUB(1,0,1,0,1,0,1,0),
};
#endif

#define CUCK_XTAB(a,b,c,d,e,f,g,h) \
	((a*0x000000FFU)|(b*0x0000FF00U)|(c*0x00FF0000U)|(d*0xFF000000U)), \
	((e*0x000000FFU)|(f*0x0000FF00U)|(g*0x00FF0000U)|(h*0xFF000000U)), \

static const uint32_t cuck_pattab_x[32] = {
	CUCK_XTAB(1,1,1,1,1,1,1,1)
	CUCK_XTAB(1,1,1,1,1,1,1,1)
	CUCK_XTAB(0,0,0,0,1,1,1,1)
	CUCK_XTAB(1,1,1,1,0,0,0,0)
	CUCK_XTAB(0,0,1,1,0,0,1,1)
	CUCK_XTAB(1,1,0,0,1,1,0,0)
	CUCK_XTAB(0,1,0,1,0,1,0,1)
	CUCK_XTAB(1,0,1,0,1,0,1,0)
};

#ifdef CUCK_ENCODER
#define CUCK_FILT_ENC_MAX 16
static const uint8_t cuck_patenc_sel[CUCK_FILT_ENC_MAX] = {
	000, 002, 004, 006,
	020, 022, 024, 026,
	040, 042, 044, 046,
	060, 062, 064, 066,
};
#endif

void cuck_clear_raw(uint8_t *raw_buf)
{
	int i;

	for(i = 0; i < 240*160; i += 8)
		*(uint64_t *)(raw_buf + i) = 0;
}

void cuck_gen_palette_32(uint8_t *pal)
{
	int i;

	for(i = 0; i < 256; i++)
	{
		int r = (i>>6)&3;
		int g = (i>>3)&7;
		int b = (i>>0)&7;

		pal[4*i+0] = (b<<5)|(b<<2)|(b>>1);
		pal[4*i+1] = (g<<5)|(g<<2)|(g>>1);
		pal[4*i+2] = r*0x55;
	}
}

#ifdef CUCK_ENCODER
void cuck_tc_to_pal(uint8_t *raw_buf, uint8_t *tc_buf)
{
	int x, y, i, j;

	for(i = 0, y = 0; y < 160; y++)
	for(x = 0; x < 240; x++, i++)
	{
		j = (x&7)+(y&7)*8 + 64*((x>>3) + (y>>3)*30);
		int b = tc_buf[4*i+0];
		int g = tc_buf[4*i+1];
		int r = tc_buf[4*i+2];

		int d = 0;//cuck_dithtab[y&3][x&3];
		r += d<<2;
		g += d<<1;
		b += d<<1;
		if(r < 0) r = 0; if(r > 255) r = 255;
		if(g < 0) g = 0; if(g > 255) g = 255;
		if(b < 0) b = 0; if(b > 255) b = 255;

		r >>= 6;
		g >>= 5;
		b >>= 5;

		r <<= 6;
		g <<= 3;
		b <<= 0;

		raw_buf[j] = r|g|b;
	}
}

void cuck_pal_to_tc(uint8_t *raw_buf, uint8_t *tc_buf)
{
	int x, y, i, j;

	for(i = 0, y = 0; y < 160; y++)
	for(x = 0; x < 240; x++, i++)
	{
		j = (x&7)+(y&7)*8 + 64*((x>>3) + (y>>3)*30);
		int v = raw_buf[j];
		int r = (v>>6)&3;
		int g = (v>>3)&7;
		int b = (v>>0)&7;

		tc_buf[4*i+0] = (b<<5)|(b<<2)|(b>>1);
		tc_buf[4*i+1] = (g<<5)|(g<<2)|(g>>1);
		tc_buf[4*i+2] = r*0x55;
		tc_buf[4*i+3] = 0xFF;
	}
}
#endif

void cuck_decode_block(uint8_t *raw, uint8_t *raw_src, uint8_t *cuck)
{
	int x, y, i;

	if(cuck[0] == 1)
	{
		uint32_t v = 0x01010101U*cuck[1];
		for(i = 0, y = 0; y < 8; y++, i += 8)
		{
	#ifdef CUCK_DEINT
			*(uint32_t *)(raw + 0) = v;
			*(uint32_t *)(raw + 4) = v;
			raw += 240;
	#else
			*(uint32_t *)(raw + i + 0) = v;
			*(uint32_t *)(raw + i + 4) = v;
	#endif
		}

		return;
	}

	uint32_t mask0 = 0xC738C738U;
	uint32_t  tip0 = 0x08410841U;

	uint32_t mask1 = 0x38C738C7U;
	uint32_t  tip1 = 0x41084108U;

	// the U is vital here!
	uint32_t addmaskb = 0x01010101U*cuck[1];
	uint32_t addmask0 = addmaskb & mask0;
	uint32_t addmask1 = addmaskb & mask1;
	uint32_t inv0 = cuck_dectab[cuck[0]*2 + 0];
	uint32_t inv1 = cuck_dectab[cuck[0]*2 + 1];
	uint32_t inv = inv0;

	for(i = 0, y = 0; y < 8; y++, i += 8)
	{
#ifdef CUCK_DEINT
		uint32_t v0b = *(uint32_t *)(raw_src + 0);
		uint32_t v1b = *(uint32_t *)(raw_src + 4);
#else
		uint32_t v0b = *(uint32_t *)(raw_src + i + 0);
		uint32_t v1b = *(uint32_t *)(raw_src + i + 4);
#endif
		uint32_t v00 = (v0b&mask0)+tip0;
		uint32_t v01 = (v0b&mask1)+tip1;
		uint32_t v10 = (v1b&mask0)+tip0;
		uint32_t v11 = (v1b&mask1)+tip1;

		uint32_t add0b = addmaskb & cuck_dectab_tobytes[inv&15]; inv >>= 4;
		uint32_t add1b = addmaskb & cuck_dectab_tobytes[inv&15]; inv >>= 4;
		if(y == 3) inv = inv1;
		uint32_t add00 = add0b&mask0;
		uint32_t add01 = add0b&mask1;
		uint32_t add10 = add1b&mask0;
		uint32_t add11 = add1b&mask1;

		v00 += add00;
		v01 += add01;
		v10 += add10;
		v11 += add11;

#ifdef CUCK_DEINT
		*(uint32_t *)(raw + 0) = (v00&mask0)|(v01&mask1);
		*(uint32_t *)(raw + 4) = (v10&mask0)|(v11&mask1);
		raw += 240;
		raw_src += 240;
#else
		*(uint32_t *)(raw + i + 0) = (v00&mask0)|(v01&mask1);
		*(uint32_t *)(raw + i + 4) = (v10&mask0)|(v11&mask1);
#endif
	}
}

#ifdef CUCK_ENCODER
int filtsel = 0;
int filtsel_base = 0;
void cuck_encode_block(uint8_t *raw, uint8_t *img, uint8_t *cuck)
{
	int x, y, i, j;
	
	// get mean of each

	int32_t mean_raw[170];

	int biggest_diff = -1;
	int best_filter = 0;//(filtsel == 0 ? 1 : 0);

	for(i = 0; i < CUCK_DECTYPES; i++)
	{
		if(i == 1 ? best_filter != 1 : best_filter == 1)
			continue;

		int32_t max_img_r = 0;
		int32_t max_img_g = 0;
		int32_t max_img_b = 0;

		int32_t min_img_r = 3;
		int32_t min_img_g = 7;
		int32_t min_img_b = 7;

		int32_t mean_img_r = 0;
		int32_t mean_img_g = 0;
		int32_t mean_img_b = 0;

		int32_t mean_raw_r = 0;
		int32_t mean_raw_g = 0;
		int32_t mean_raw_b = 0;

		int32_t mean_count = 0;

		for(j = 0, y = 0; y < 8; y++)
		for(x = 0; x < 8; x++, j++)
		{
			if(i!=1 && ((cuck_dectab[i*2 + ((y>>2)&1)]>>(j&31))&1) == 0)
				continue;

			int val_img = img[j];
			int val_raw = raw[j];

			int ir = (val_img>>6)&3;
			int ig = (val_img>>3)&7;
			int ib = (val_img>>0)&7;

			if(max_img_r < ir) max_img_r = ir;
			if(min_img_r > ir) min_img_r = ir;
			if(max_img_g < ig) max_img_g = ig;
			if(min_img_g > ig) min_img_g = ig;
			if(max_img_b < ib) max_img_b = ib;
			if(min_img_b > ib) min_img_b = ib;

			int rr = (val_raw>>6)&3;
			int rg = (val_raw>>3)&7;
			int rb = (val_raw>>0)&7;

			mean_img_r += ir;
			mean_img_g += ig;
			mean_img_b += ib;

			mean_raw_r += rr;
			mean_raw_g += rg;
			mean_raw_b += rb;

			mean_count += 1;
		}

		mean_raw_r = (((mean_raw_r + (mean_count/2))/mean_count)&3);
		mean_raw_g = (((mean_raw_g + (mean_count/2))/mean_count)&7);
		mean_raw_b = (((mean_raw_b + (mean_count/2))/mean_count)&7);

		mean_img_r = (((mean_img_r + (mean_count/2))/mean_count)&3);
		mean_img_g = (((mean_img_g + (mean_count/2))/mean_count)&7);
		mean_img_b = (((mean_img_b + (mean_count/2))/mean_count)&7);

		// do diff
		if(i != 1)
		{
			mean_raw_r = (mean_raw_r - mean_img_r);
			mean_raw_g = (mean_raw_g - mean_img_g);
			mean_raw_b = (mean_raw_b - mean_img_b);

			if(min_img_r + mean_raw_r < 0) mean_raw_r = -min_img_r;
			if(max_img_r + mean_raw_r > 3) mean_raw_r = 3-max_img_r;
			if(min_img_g + mean_raw_g < 0) mean_raw_g = -min_img_g;
			if(max_img_g + mean_raw_g > 7) mean_raw_g = 7-max_img_g;
			if(min_img_b + mean_raw_b < 0) mean_raw_b = -min_img_b;
			if(max_img_b + mean_raw_b > 7) mean_raw_b = 7-max_img_b;
		}

		int cdiff = 0;
		cdiff += (mean_raw_r*mean_raw_r);
		cdiff += (mean_raw_g*mean_raw_g);
		cdiff += (mean_raw_b*mean_raw_b);
		if(cdiff > biggest_diff)
		{
			best_filter = i;
			biggest_diff = cdiff;
		}

		mean_raw_r &= 3;
		mean_raw_g &= 7;
		mean_raw_b &= 7;

		// merge
		mean_raw[i] = (mean_raw_r<<6) | (mean_raw_g<<3) | (mean_raw_b<<0);
	}

	cuck[0] = best_filter;
	//cuck[0] = cuck_patenc_sel[filtsel];
	cuck[1] = mean_raw[cuck[0]];
	//filtsel = (filtsel+1) % CUCK_FILT_ENC_MAX;
	filtsel = (filtsel+1) % 137;

	//printf("%02X %02X %02X\n", mean_raw_r, mean_raw_g, mean_raw_b);

	// decode
	cuck_decode_block(img, img, cuck);
}
#endif

void cuck_decode_line(int line, uint8_t *raw_buf, uint8_t *raw_src_buf, uint8_t *cuck_buf)
{

#ifdef CUCK_DEINT
	int x;

	for(x = 0; x < 30; x++)
		cuck_decode_block(
			raw_buf + 240*8*line + 8*x, 
			raw_src_buf + 240*8*line + 8*x, 
			cuck_buf + 2*(x + line*30));
#else
	int i;

	for(i = 0; i < 20*30; i++)
		cuck_decode_block(
			raw_buf + 8*8*(i + line*30),
			raw_src_buf + 8*8*(i + line*30),
			cuck_buf + 2*(i + line*30));
#endif
}


void cuck_decode(uint8_t *raw_buf, uint8_t *cuck_buf)
{

#ifdef CUCK_DEINT
	int x, y, i;
	for(i = 0, y = 0; y < 20; y++)
	for(x = 0; x < 30; x++, i++)
		cuck_decode_block(
			raw_buf + 240*8*y + 8*x,
			raw_buf + 240*8*y + 8*x,
			cuck_buf + 2*i);
#else
	int i;

	for(i = 0; i < 20*30; i++)
		cuck_decode_block(
			raw_buf + 8*8*i,
			raw_buf + 8*8*i,
			cuck_buf + 2*i);
#endif
}

#ifdef CUCK_ENCODER
void cuck_encode(uint8_t *raw_buf, uint8_t *img_buf, uint8_t *cuck_buf)
{
	int i;

	filtsel = filtsel_base;
	filtsel_base = (filtsel_base + 37) % 137;
#pragma omp parallel for
	for(i = 0; i < 20*30; i++)
		cuck_encode_block(raw_buf + 8*8*i, img_buf + 8*8*i, cuck_buf + 2*i);
}
#endif

