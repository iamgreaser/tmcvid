#!/bin/sh
gcc -fopenmp -O3 -o cuckvid_enc cuckvid_enc.c -lm `sdl-config --cflags --libs` && ffmpeg -i badapple.webm -f rawvideo -pix_fmt bgr0 -s 240x160 -r 23.94 - | ./cuckvid_enc badapple-vid.bin

