#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include "cuckvid.c"

uint8_t raw_buf[240*160*4];
uint8_t cuck_buf[30*20*2];

void cuck_gen_palette(void)
{
	int i;

}

void cuck_clean(uint8_t *cuckframe)
{
	
}

void cuck_decode()
{

}

int main(int argc, char *argv[])
{
	int i;

	for(;;)
	{
		for(i = 0; i < 240*160*4; i++)
		{
			int c = fgetc(stdin);

			if(c == -1)
				break;

			in_buf[i] = c;
		}

		if(i < 240*160*4)
			break;

		cuck_encode(raw_buf, cuck_buf);
	}

	return 0;
}

