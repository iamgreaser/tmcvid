#include <stdint.h>

#define CUCK_DELTA
#ifdef CUCK_ENCODER
#define CUCK_ENCODE_ANTI_RAINBOW
#include <math.h>
static int8_t cuck_dithtab[4][4] = {
	{-8,+0,-6,+2},
	{+4,-4,+6,-2},
	{-5,+3,-7,+1},
	{+7,-1,+5,-3},
};
#endif

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

#ifdef CUCK_ENCODER
int cuck_enc_initialised = 0;
int32_t cuck_mean_count[CUCK_DECTYPES];
float cuck_mean_count_reduced[CUCK_DECTYPES];
uint32_t cuck_last[20*30][CUCK_DECTYPES][2];
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

	// the U is vital here!
	uint32_t addmaskb = 0x01010101U*cuck[1];
#ifdef CUCK_DELTA
	uint32_t mask0 = 0xC738C738U;
	uint32_t  tip0 = 0x08410841U;

	uint32_t mask1 = 0x38C738C7U;
	uint32_t  tip1 = 0x41084108U;

	uint32_t addmask0 = addmaskb & mask0;
	uint32_t addmask1 = addmaskb & mask1;
#endif
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

#ifdef CUCK_DELTA
		// DELTA
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

#else
		// NON-DELTA
		uint32_t imask0 = cuck_dectab_tobytes[inv&15]; inv >>= 4;
		uint32_t imask1 = cuck_dectab_tobytes[inv&15]; inv >>= 4;
		if(y == 3) inv = inv1;
		uint32_t v0 = v0b ^ ((v0b^addmaskb) & imask0);
		uint32_t v1 = v1b ^ ((v1b^addmaskb) & imask1);

#ifdef CUCK_DEINT
		*(uint32_t *)(raw + 0) = v0;
		*(uint32_t *)(raw + 4) = v1;
		raw += 240;
		raw_src += 240;
#else
		*(uint32_t *)(raw + i + 0) = v0;
		*(uint32_t *)(raw + i + 4) = v1;
#endif

#endif
		// END OF CODEC-SPECIFIC STUFF
	}
}

#ifdef CUCK_ENCODER
void cuck_encode_block(int idx, uint8_t *raw, uint8_t *img, uint8_t *cuck)
{
	int x, y, i, j;
	
	// get mean of each

	int32_t mean_raw[CUCK_DECTYPES];
	int8_t diff_each[64][4];
	int8_t img_each[64][4];

	float biggest_diff = -10000.0f;
	int best_filter = 0;

	for(j = 0, y = 0; y < 8; y++)
	for(x = 0; x < 8; x++, j++)
	{
		int val_img = img[j];
		int val_raw = raw[j];

		int ir = (val_img>>6)&3;
		int ig = (val_img>>3)&7;
		int ib = (val_img>>0)&7;

		int rr = (val_raw>>6)&3;
		int rg = (val_raw>>3)&7;
		int rb = (val_raw>>0)&7;

#ifdef CUCK_DELTA
		int dr = (rr - ir);
		int dg = (rg - ig);
		int db = (rb - ib);
#else
		int dr = rr;
		int dg = rg;
		int db = rb;
#endif

		diff_each[j][0] = dr<<1;
		diff_each[j][1] = dg;
		diff_each[j][2] = db;

		img_each[j][0] = ir<<1;
		img_each[j][1] = ig;
		img_each[j][2] = ib;
	}

	for(i = 0; i < CUCK_DECTYPES; i++)
	{
		if(i == 1 ? best_filter != 1 : best_filter == 1)
			continue;

		if(i > 1)
		{
			if(cuck_last[idx][i][0] & cuck_dectab[2*i+0]) continue;
			if(cuck_last[idx][i][1] & cuck_dectab[2*i+1]) continue;
		}

		int32_t max_diff_r = 6;
		int32_t max_diff_g = 7;
		int32_t max_diff_b = 7;

		int32_t min_diff_r = -6;
		int32_t min_diff_g = -7;
		int32_t min_diff_b = -7;

		int32_t mean_diff_r = 0;
		int32_t mean_diff_g = 0;
		int32_t mean_diff_b = 0;
		float mean_diff_t = 0;
		float amean_diff_t = 0;
		float var_diff_t = 0;

		int32_t mean_count = 0;

#ifdef CUCK_DELTA
#ifdef CUCK_ENCODE_ANTI_RAINBOW
		// get min/max diff
		for(j = 0, y = 0; y < 8; y++)
		for(x = 0; x < 8; x++, j++)
		{
			if(i!=1 && ((cuck_dectab[i*2 + ((y>>2)&1)]>>(j&31))&1) == 0)
				continue;

			int ir = img_each[j][0];
			int ig = img_each[j][1];
			int ib = img_each[j][2];

			if(ir+max_diff_r > 6) max_diff_r = 6-ir;
			if(ir+min_diff_r < 0) min_diff_r = 0-ir;
			if(ig+max_diff_g > 7) max_diff_g = 7-ig;
			if(ig+min_diff_g < 0) min_diff_g = 0-ig;
			if(ib+max_diff_b > 7) max_diff_b = 7-ib;
			if(ib+min_diff_b < 0) min_diff_b = 0-ib;
		}
#endif
#endif

		// get mean diff
		for(j = 0, y = 0; y < 8; y++)
		for(x = 0; x < 8; x++, j++)
		{
			if(i!=1 && ((cuck_dectab[i*2 + ((y>>2)&1)]>>(j&31))&1) == 0)
				continue;

			int ir = img_each[j][0];
			int ig = img_each[j][1];
			int ib = img_each[j][2];

			int dr = diff_each[j][0];
			int dg = diff_each[j][1];
			int db = diff_each[j][2];

			//int dt = dr*dr + dg*dg + db*db;
			int dt = dr + dg + db;
			int dt2 = dr*dr + dg*dg + db*db;

			mean_diff_r += dr;
			mean_diff_g += dg;
			mean_diff_b += db;
			mean_diff_t += dt;
			amean_diff_t += (dt < 0 ? -dt : dt);
			var_diff_t += dt2;
		}

		amean_diff_t = (amean_diff_t/cuck_mean_count[i]);
		//amean_diff_t = (mean_diff_t < 0 ? -mean_diff_t : mean_diff_t)/sqrtf(cuck_mean_count[i]);
		mean_diff_t = (mean_diff_t/cuck_mean_count[i]);
		amean_diff_t = (mean_diff_t < 0 ? -mean_diff_t : mean_diff_t);
		var_diff_t = -(var_diff_t/cuck_mean_count[i]);
		var_diff_t += mean_diff_t*mean_diff_t;
		var_diff_t *= pow(cuck_mean_count[i], 0.25f);

		// do diff
		if(i == 1)
			abort();

		//float cdiff = (i == 0 ? 100 : 0);
		//float cdiff = amean_diff_t + var_diff_t*10000.0f;
		//float cdiff = amean_diff_t + var_diff_t;
		float cdiff = amean_diff_t;
		if(cdiff > biggest_diff)
		{
			best_filter = i;
			biggest_diff = cdiff;

			mean_diff_r = ((mean_diff_r + (cuck_mean_count[i]/2))/cuck_mean_count[i]);
			mean_diff_g = ((mean_diff_g + (cuck_mean_count[i]/2))/cuck_mean_count[i]);
			mean_diff_b = ((mean_diff_b + (cuck_mean_count[i]/2))/cuck_mean_count[i]);

#ifdef CUCK_DELTA
#ifdef CUCK_ENCODE_ANTI_RAINBOW
			if(mean_diff_r > 0 && mean_diff_r > max_diff_r) mean_diff_r = max_diff_r;
			if(mean_diff_r < 0 && mean_diff_r < min_diff_r) mean_diff_r = min_diff_r;
			if(mean_diff_g > 0 && mean_diff_g > max_diff_g) mean_diff_g = max_diff_g;
			if(mean_diff_g < 0 && mean_diff_g < min_diff_g) mean_diff_g = min_diff_g;
			if(mean_diff_b > 0 && mean_diff_b > max_diff_b) mean_diff_b = max_diff_b;
			if(mean_diff_b < 0 && mean_diff_b < min_diff_b) mean_diff_b = min_diff_b;
#endif
#endif

			mean_diff_r &= 7;
			mean_diff_r >>= 1;
			mean_diff_g &= 7;
			mean_diff_b &= 7;

			mean_raw[i] = (mean_diff_r<<6) | (mean_diff_g<<3) | (mean_diff_b<<0);
		}

		// merge
	}

	cuck[0] = best_filter;
	cuck[1] = mean_raw[cuck[0]];

	i = cuck[0];
	if(1)
	{
		cuck_last[idx][i][0] = 0;
		cuck_last[idx][i][1] = 0;
	} else {
		cuck_last[idx][i][0] = cuck_dectab[i*2+0];
		cuck_last[idx][i][1] = cuck_dectab[i*2+1];
	}


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
	int x, y, i, j;

	if(!cuck_enc_initialised)
	{
		for(i = 0; i < CUCK_DECTYPES; i++)
		{
			for(j = 0; j < 30*20; j++)
				cuck_last[j][i][0] = cuck_last[j][i][1] = 0;

			cuck_mean_count[i] = 0;
			for(j = 0, y = 0; y < 8; y++)
			for(x = 0; x < 8; x++, j++)
			{
				if(i!=1 && ((cuck_dectab[i*2 + ((y>>2)&1)]>>(j&31))&1) == 0)
					continue;

				cuck_mean_count[i] += 1;
			}

			cuck_mean_count_reduced[i] = pow(cuck_mean_count[i], -1.0f);
			//cuck_mean_count_reduced[i] = 1.0f/cuck_mean_count[i];
		}

		cuck_enc_initialised = 1;
	}

#pragma omp parallel for
	for(i = 0; i < 20*30; i++)
		cuck_encode_block(i, raw_buf + 8*8*i, img_buf + 8*8*i, cuck_buf + 2*i);
}
#endif

