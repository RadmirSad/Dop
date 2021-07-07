	.arch armv8-a
	.text
	.align	2
	.global RotAsm
	.type	RotAsm, %function
	.equ	res, 16
	.equ	test, 24
	.equ	width, 32
	.equ	height, 40
	.equ	newwid, 48
	.equ	chan, 56
	.equ	ang, 64
	.equ	x_cent, 72
	.equ	y_cent, 80
	.equ	oldsq, 88
	.equ	new_cent, 96
	.equ	ind, 104
RotAsm:
	sub sp, sp, #112
	stp x29, x30, [sp]
	mov x29, sp
	stp x0, x1, [x29, res]		// newim x0, oldim x1
	stp x2, x3, [x29, width]	// width x2, height x3
	stp x4, x5, [x29, newwid]	// newwidth x4, chan x5
	str d0, [x29, ang]			// double angle (d0)
	mov x12, #2
	sdiv x7, x2, x12			// x_cent = width / 2
	sdiv x8, x3, x12			// y_cent = height / 2
	stp x7, x8, [x29, x_cent]
	mul x9, x3, x2				// oldsq (x9) = width * height
	str x9, [x29, oldsq]
	sdiv x10, x4, x12			// new_cent (x10) = newwidth / 2
	mov x11, #0					// int i (x11) = 0
	stp x10, x11, [x29, new_cent]
0:
	ldr x9, [x29, oldsq]
	cmp x11, x9
	bge 4f
	ldr d0, [x29, ang]
	bl cos
	str d0, [sp, #-8]!			// sin a (d0)
	ldr d0, [x29, ang]			// cos a (d1)
	bl sin
	ldr d1, [sp], #8
	ldr x2, [x29, width]
	ldr x11, [x29, ind]
	sdiv x12, x11, x2			// x12 = i / width
	mul x13, x12, x2			// w13 = w12 * width
	sub x13, x11, x13			// i % width
	ldr x7, [x29, x_cent]
	sub x13, x13, x7			// int x (w13) = i % width - x_cent
	ldr x8, [x29, y_cent]
	sub x12, x12, x8			// int y (w12) = i / width - y_cent
	scvtf d2, x13				// x (d2)
	scvtf d3, x12				// y (d3)
	fmul d4, d2, d1				// x * cos a
	fmul d5, d3, d0				// y * sin a
	fsub d4, d4, d5				// new_x = xcos a - ysin a
	fmul d0, d2, d0				// d0 = x sin a
	fmul d1, d3, d1				// d1 = y cos a
	fadd d0, d0, d1				// y_new (d0) = xsin a + ycos b
	frinti d4, d4
	fcvtzs x4, d4				// x_new (x4)
	frinti d0, d0
	fcvtzs x5, d0				// y_new (x5)
	ldr x6, [x29, new_cent]
	add x4, x4, x6				// x_new = x_new + new_cent
	add x5, x5, x6				// y_new = y_new + new_cent
	mov x7, #0					// int j (x7) = 0
	ldr x8, [x29, chan]			// channels (x8)
	ldr x11, [x29, ind]			// i -- x11
	ldr x6, [x29, newwid]
	madd x1, x5, x6, x4			// x_new + y_new * newwidth
	mul x1, x1, x8				// chan * X1
1:
	cmp x7, x8
	bge 2f
	add x3, x1, x7				// X1 + j -- X1 index for new image
	madd x0, x8, x11, x7		// chan * i + j
	ldr x2, [x29, test]
	ldrb w4, [x2, x0]
	ldr x2, [x29, res]
	strb w4, [x2, x3]			//newim[x10] = im[x0]
	add x7, x7, #1
	b 1b
2:
	add x11, x11, #1			// ++i
	str x11, [x29, ind]
	b 0b
3:
	mov w0, #0
4:
	ldp x29, x30, [sp]
	add sp, sp, #112
	ret
	.size	RotAsm, .-RotAsm
