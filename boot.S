	// simple GBA fastmem bootloader
	// GreaseMonkey, 2014-2015 - Public Domain
	.arm
	.section .text
	.global run_exe
	.extern init
	b _start_asm
	.incbin "nintendo.bin"
	.ascii "multibooter "
	.ascii "AAAE00"
	.byte 0x96, 0x00, 0x00
	.byte 0,0,0,0,0,0,0
	.byte 0x00
	.byte 0x13 // compliment check. here's a compliment: NINTENDO SUCKS.
	.hword 0x00
	b run_exe
	// data goes here
	.word vid01s, vid01s_end - vid01s
	.ascii "vid01s  "
	.word vid01v, vid01v_end - vid01v
	.ascii "vid01v  "
	.word 0

_start_asm:
	ldr r0, =init_beg
	ldr r1, =init_end
run_exe:
	/* Copy to WRAM */
	ldr r2, =0x03000000
	mov r3, r2
	_lp_copy_prog:
		ldmia r0!, {r4-r11}
		stmia r2!, {r4-r11}
		cmp r1, r0
		bhi _lp_copy_prog

	/* Jump */
	bx r3
	.pool

	.align 5
init_beg:
	.incbin "main.bin"
	.align 5
init_end:
vid01s:
	.incbin "tmc-adpcm.wav"
vid01s_end:
	.align 4
vid01v:
	.incbin "tmc-vid.bin"
vid01v_end:
	.align 4

