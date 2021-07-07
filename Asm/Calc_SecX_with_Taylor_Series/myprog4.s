	.arch armv8-a
	.data
	.align 2
BTab:
	.float	1.0
	.fill	1020				// 256 numbers, on k position B(2k)
Tfact:
	.float	1.0
	.fill	2044				// 512 numbers
halfpi:
	.float	1.57079
erroffile:
	.string "\n Usage: %s file\n"
errofval:
	.string "\n Incorrect value (-pi/2 < x < pi/2)\n"
mesinp:
	.string "\n Input x\n"
mesout:
	.string "\n sec (%.7g) = %.7g\n"
mesmyout:
	.string "\n mysec (%.7g) = %.7g\n"
mode:
	.string "w"
forminp:
	.string "%f"
forfile:
	.string "%i = %.7g\n"
	.text
	.align	2
	.global	mysec
	.type	mysec, %function
	.equ	x_20, 16
	.equ	s_8, 24
	.equ	x, 28
	.equ	file, 32
	.equ	q, 40
mysec:
	stp x29, x30, [sp, #-48]!
	mov x29, sp
	str x20, [x29, x_20]
	str s8, [x29, s_8]			// save x20 and s8
	str s0, [x29, x]
	str x0, [x29, file]
	str s1, [x29, q]
	mov x20, #0					// int k(x20) = 0
	fmov s8, wzr				// float sum (s8) = 0
	fmov s16, wzr				// dop (x16) = 0
0:								// x0 - k, s0 - x
	fmov s8, s16				// sum (s8) = dop (s16)
	mov x0, x20					// x0 = k(x20)
	ldr s0, [x29, x]
	bl findelem
	str s0, [sp, #-4]!			// save elem
	fcvt d0, s0
	ldr x0, [x29, file]			// write s0 in file
	mov x2, x20
	adr x1, forfile
	bl fprintf
	add x20, x20, #1			// ++k
	ldr s0, [sp], #4
	ldr s1, [x29, q]
	fadd s16, s0, s8
	fcmp s0, s1					// compare new elem with eps
	bgt 0b						// if sum didn't change load
	fmov s0, s16				// return sum in s0
	ldr s8, [x29, s_8]
	ldr x20, [x29, x_20]
	ldp x29, x30, [sp]
	add sp, sp, #48
	ret
	.size	mysec, .-mysec

	.type	findelem, %function
	.equ	k, 16
	.equ	s_9, 24
findelem:						// s0 - x, return res in s0
	sub sp, sp, #28				// x29 8 + x30 8 + x0 (k) 8 + s9 () 4
	stp x29, x30, [sp]
	mov x29, sp
	str x0, [x29, k]
	str s9, [x29, s_9]				// save s9
	scvtf s1, x0						// get k in s1
	fmov s16, #2.0						// s16 = 2
	fmul s1, s1, s16					// s1 = 2k
	bl powf								// s0 = x^2k
	fmov s9, s0							// elem in s9 = x^2k
	fmov s0, #-1.0						// s0 (-1)
	ldr x0, [x29, k]					// load k in x0
	add x0, x0, #1						// x0 = k + 1
	scvtf s1, x0						// convert k (x0) in s1 for get pow
	bl powf								// (-1)^k+1
	fmul s9, s9, s0						// elem = (-1)^k * x^2k
	fmov s0, #4.0						// s0 = 4
	ldr x1, [x29, k]					// x1 = k
	mov x2, #2
	mov x3, #1							// x3 = 1, x2 = 2
	madd x0, x1, x2, x3					// x0 = 2 * k + 1 (x1*x2 + x3)
	str x0, [sp, #-8]!					// save 2k+1 in sp
	scvtf s1, x0						// convert 2k+1 from x0 to s1
	bl powf								// get 4^(2k + 1)
	fmul s9, s9, s0						// elem (s9) = (-1)^(k+1) * 4^(2k + 1)
	ldr x0, [sp], #8					// load 2k+1 in x0
	bl getE								// x0 - index 2k+1
	fmul s0, s9, s0						// elem = (-1)^k * 4^(2k + 1) * x^2k * E
	ldr s9, [x29, s_9]
	ldp x29, x30, [sp]
	add sp, sp, #28
	ret
	.size	findelem, .-findelem

	.type	getE, %function
	.equ	N, 16
	.equ	s_8s_9, 24
getE:									// x0 - index N		E = sum {[B(N - i)*(0.25)^i] / [(N - i)! * i!]}
	stp x29, x30, [sp, #-32]!			// save x29, x30, x0
	mov x29, sp
	str x0, [x29, N]
	stp s8, s9, [x29, s_8s_9]			// save s8, s9
	fmov s8, wzr						// s8 - sum = 0
	fmov s9, wzr						// s9 - dop = 0
	mov x1, #0							// i (x1) = 0
0:
	ldr x0, [x29, N]
	cmp x1, x0							// compare i with N
	bgt exitE
	sub x0, x0, x1						// x0 = N - i
	str x1, [sp, #-8]!
	bl getB								// get B(N - i)
	ldr x1, [sp], #8
	fmov s18, wzr
	fcmp s0, s18							// if B(N - i) == 0 ++i and back on 0
	bne 1f
	add x1, x1, #1
	b 0b
1:
	fmov s9, s0							// dop = B(N - i)
	fmov s1, #1.0
	fmov s2, #4.0
	fdiv s0, s1, s2						// s0 = -0.25
	scvtf s1, x1						// convert x1 to s1
	str x1, [sp, #-8]!
	bl powf
	ldr x1, [sp], #8
	fmul s9, s9, s0						// dop = B(N - i)*(-0.25)^i
	mov x0, x1							// x0 = x1 (i)
	str x1, [sp, #-8]!
	bl getfact
	ldr x1, [sp], #8
	fdiv s9, s9, s0						// dop = B(N - i)*(-0.25)^i/(i!)
	ldr x0, [x29, N]
	sub x0, x0, x1						// x0 = N - i
	str x1, [sp, #-8]!
	bl getfact
	ldr x1, [sp], #8
	fdiv s9, s9, s0						// dop = [B(N - i)*(-0.25)^i]/[(N - i)! * i!]
	fadd s8, s8, s9
	add x1, x1, #1
	b 0b
exitE:
	fmov s0, s8							// s0 = s8 (sum)
	ldp s8, s9, [x29, s_8s_9]
	ldp x29, x30, [sp], #32
	ret
	.size	getE, .-getE

	.type	getB, %function
getB:									// x0 - z, return B(z)
	str x30, [sp, #-8]!
	cmp x0, #1							// if x0 = 1
	bne 9f
	fmov s19, #-1.0
	fmov s20, #2.0
	fdiv s0, s19, s20					// res s0 = -0.5
	b endB
9:
	mov x2, #2
	mov x1, x0
	sdiv x3, x1, x2						// parity check
	mul x3, x3, x2						// x3 = x1 / 2
	sub x1, x1, x3						// x3 = x1/2  * 2
	fmov s0, wzr
	cbnz x1, endB
	adr x1, BTab						// get adr of table in x1
	mov x2, #2
	sdiv x3, x0, x2						// x3 = k
	ldr s0, [x1, x3, lsl #2]			// try to find B(2k) in table
	fmov s16, wzr						// s16 = 0
	fcmp s0, s16
	bne endB							// compare val in s0 with 0
	str x3, [sp, #-8]!					// save k in sp, now it's x
0:										// else we will find first non-zero elem
	sub x3, x3, #1						// --x
	ldr s0, [x1, x3, lsl #2]			// load BTab[x - i]
	fcmp s0, s17						// comp with 0
	beq 0b								// if s0 == 0 return to 0
1:
	add x3, x3, #1						// ++x
	mul x3, x3, x2						// 2x
	fmov s17, wzr						// s17 = 0 - sum (B(2x))
	mov x4, #1							// n (x4) = 1
2:
	fmov s18, wzr						// s18 = 0 - for 1 elem from sum
	sub x5, x3, x4						// x5 = 2x - n
	cmp x5, #1
	beq firB
	sdiv x6, x5, x2						// x6 = x5/2 - integer
	mul x8, x6, x2						// x8 = x5/2  * 2
	sub x7, x5, x8						// parity check
	cbnz x7, 3f							// if 2x-n is odd B = 0
	ldr s18, [x1, x6, lsl #2]			// 2x - n is even, we can load it from table B[x - n/2]
	b dop
firB:									// if 2x - n = 1 [B(1)]
	fmov s19, #-1.0
	fmov s20, #2.0
	fdiv s18, s19, s20					// B(1) = -0.5
dop:
	stp x1, x2, [sp, #-16]!				// save x1 - x6
	stp x3, x4, [sp, #-16]!
	stp x5, x6, [sp, #-16]!
	stp s16, s17, [sp, #-8]!			// save s16 - s19
	stp s18, s19, [sp, #-8]!
	mov x0, x5
	bl getfact							// return (2x - n)!
	str s0, [sp, #4]					// save (2x - n)! in s19
	ldr x0, [sp, #40]					// load n (x4)
	add x0, x0, #1
	bl getfact							// (n + 1)! in s0
	ldp s18, s19, [sp], #8
	ldp s16, s17, [sp], #8
	ldp x5, x6, [sp], #16
	ldp x3, x4, [sp], #16
	ldp x1, x2, [sp], #16				// restore sp
	fdiv s18, s18, s0					// B(2x - n)/(n + 1)!
	fdiv s18, s18, s19					// s18 = B(2x - n)/[(n + 1)! * (2x - n)!]
3:
	fadd s17, s17, s18
	add x4, x4, #1						// ++n
	cmp x4, x3							// comp n (x4) with 2x (x3)
	ble 2b								// if n <= 2x return to 2b
	mov x0, x3							// we know sum, mult our sum on -1*(2x)!
	stp x2, x3, [sp, #-16]!				// save x2, x3
	str s17, [sp, #-4]!
	bl getfact							// x0 - 2x, return s0 - (2x)!
	ldr s17, [sp], #4					// load sum
	ldp x2, x3, [sp], #16				// load x2, x3
	fmov s19, #-1.0						// s19 = -1
	fmul s0, s19, s0					// s0 = -1 * (2x)!
	fmul s0, s0, s17					// B(2x) = -1 * (2x)! * sum from n = 1 to 2x
	sdiv x3, x3, x2						// 2x -> x
	adr x1, BTab
	str s0, [x1, x3, lsl #2]			// save B(2x)
	ldr x10, [sp]
	cmp x3, x10							// compare x with k
	bne 1b
	add sp, sp, #8						// restore sp
endB:									// return B(2k) in s0
	ldr x30, [sp], #8
	ret
	.size	getB, .-getB

	.type	getfact, %function
getfact:								// x0 - index n, return n! in s0
	adr x1, Tfact						// get adr of table with fact in x1
	ldr s0, [x1, x0, lsl #2]			// load value in Tfact[n]
	fmov s17, wzr						// s17 = 0
	fcmp s0, s17						// compare this value with 0
	bne exitF							// if != 0 return this value
	mov x10, x0							// copy n (x0) in x10
0:										// else we should find first pos value
	sub x0, x0, #1						// --n
	ldr s0, [x1, x0, lsl #2]			// load value
	fcmp s0, s17						// comp with 0
	beq 0b								// if s16 == 0 do it again
1:
	add x0, x0, #1						// ++n
	scvtf s18, x0						// convert n from x0 to s18
	fmul s0, s0, s18					// n * (n-1)!
	str s0, [x1, x0, lsl #2]			// save n! in n pos in table
	cmp x0, x10							// compare n' with n
	bne 1b								// if they don't equal return to 1
exitF:
	ret									// return n! in s0
	.size	getfact, .-getfact

	.global	main
	.type	main, %function
	.equ	progname, 16
	.equ	filename, 24
	.equ	filestr, 32
	.equ	x, 40
	.equ	res, 48
	.equ	q, 56
main:							// x29 8 + x30 8 + prog 8 + nfile 8 + struct 8 + x 8 + y 8 + q 4 = 56
	stp x29, x30, [sp, #-64]!	// save x29, x30
	mov x29, sp
	cmp w0, #3					// check number of parameters
	beq 0f
	ldr x2, [x1]
	adr x0, stderr
	ldr x0, [x0]
	adr x1, erroffile
	bl fprintf
	mov w0, #1
	b exit
0:
	ldr x0, [x1]
	str x0, [x29, progname]		// save progname
	ldr x0, [x1, #8]
	str x0, [x29, filename]		// save filename
	ldr s0, [x1, #16]
	str s0, [x29, q]
	adr x1, mode
	bl fopen					// trying to open file
	cbnz x0, 1f
	ldr x0, [x29, filename]
	bl perror
	mov w0, #1
	b exit
1:
	str x0, [x29, filestr]		// save file* in x29
	adr x0, mesinp
	bl printf					// print mes
	adr x0, forminp
	add x1, x29, x
	bl scanf					// read number
	ldr s0, [x29, x]			// check condition: |x| < pi/2
	fabs s1, s0					// s1 = |s0|
	adr x0, halfpi				// s0 = pi/2 1.57
	ldr s0, [x0]
	fcmp s1, s0
	blt 2f
	ldr x0, [x29, filestr]		// if |x| >= pi/2 close file and quit
	bl fclose
	adr x0, stderr
	ldr x0, [x0]
	adr x1, errofval
	bl fprintf
	mov w0, #1
	b exit
2:
	ldr s0, [x29, x]			// save x in x29
	bl cosf						// get cos x
	fmov s2, #1.0
	fdiv s1, s2, s0				// get sec x = 1/cos x
	str s1, [x29, res]			// save res in x29
	adr x0, mesout
	ldr s0, [x29, x]
	fcvt d0, s0
	ldr s1, [x29, res]
	fcvt d1, s1
	bl printf					// print sec x = res
	ldr x0, [x29, filestr]
	ldr s0, [x29, x]
	ldr s1, [x29, q]
	bl mysec					// x0 - filestr, s0 - x, return res in s0
	str s0, [x29, res]			// save res in x29
	adr x0, mesmyout
	ldr s0, [x29, x]
	fcvt d0, s0
	ldr s1, [x29, res]
	fcvt d1, s1
	bl printf
	ldr x0, [x29, filestr]
	bl fclose
	mov w0, #0
exit:
	ldp x29, x30, [sp]
	add sp, sp, #64
	ret
	.size	main, .-main
