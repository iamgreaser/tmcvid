#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include <SDL.h>

#define CUCK_ENCODER
#include "cuckvid.c"

uint8_t tc_buf[240*160*4];
uint8_t raw_buf[240*160];
uint8_t img_buf[240*160];
uint8_t cuck_buf[30*20*2];
//uint8_t cuck_buf[240*160];

void on_alarm(int sig)
{
	// do nothing
	// cannot use SIG_IGN as otherwise usleep() won't be interrupted
}

int main(int argc, char *argv[])
{
	int i;
	FILE *fp = fopen(argv[1], "wb");

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT,  SIG_DFL);
	signal(SIGALRM, on_alarm);

	SDL_Surface *screen = SDL_SetVideoMode(240, 160, 0, 0);
	cuck_clear_raw(img_buf);

	struct itimerval it;
	it.it_interval.tv_sec = it.it_value.tv_sec = 0;
	it.it_interval.tv_usec = it.it_value.tv_usec = 1000000/24;
	//setitimer(ITIMER_REAL, &it, NULL);

	int draw_frame_counter = 1;
	int draw_frame_counter_max = 1;
	
	for(;;)
	{
		for(i = 0; i < 240*160*4; i++)
		{
			int c = fgetc(stdin);

			if(c == -1)
				break;

			tc_buf[i] = c;
		}

		if(i < 240*160*4)
			break;

		cuck_tc_to_pal(raw_buf, tc_buf);
		cuck_encode(raw_buf, img_buf, cuck_buf);
		fwrite(cuck_buf, 30*20*2, 1, fp);
		fflush(fp);
		cuck_pal_to_tc(img_buf, tc_buf);

		draw_frame_counter--;
		if(draw_frame_counter <= 0)
		{
			SDL_LockSurface(screen);
			memcpy(screen->pixels, tc_buf, 240*160*4);
			SDL_UnlockSurface(screen);
			SDL_Flip(screen);
			draw_frame_counter = draw_frame_counter_max;
		}
		//usleep(100000);
	}

	return 0;
}

