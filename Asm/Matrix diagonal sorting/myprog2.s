	.arch armv8-a
	.data
	.align	3
n:
	.short	4
matr:
	.byte	11, 8, 18, 17
	.byte	5, 24, 19, 4
	.byte	22, 0, 15, 12
	.byte	21, 13, 23, 10
	.text
	.align 	2
	.global _start
	.type	_start, %function
_start:	
	adr x2, n		//
	ldrsh x0, [x2]	// x0 -- num of elems
	sub x2, x0, #1	// n - 1 --  num of elems without 1
	adr x1, matr 	// x1  --  adr of matrix
	mov x15, #0		// dop zero	x15 -- 0
FIRHALF:			// for  *(int i = n - 1;	x2 -- i
	cmp x2, x15		// 
	blt L0			// i >= 0;
	sub x3, x0, x2	// count = n - i	x3 -- count
	mov x4, #0		// for **(start = 0;	x4 -- start
STARTFIR:			//
	cmp x4, x3		// 
	bge ADDFIR		// start < count
	add x8, x4, x2	// start + i
	madd x8, x8, x0, x4	// (start + i) * n + start	x8 -- offset of minimum
	ldrsb x9, [x1, x8]	// x9 -- min elem
	mov x5, x4		// for ***(int j = start;	x5 -- j
FF:					//
	cmp x5, x3 		// 
	bge ADDSTART	// j < count;
	add x6, x2, x5	// i + j
	madd x6, x6, x0, x5	// (i + j) * n + j  --  offset
	ldrsb x7, [x1, x6]	// x7 -- elem
	cmp x7, x9		// 
	bge ADDFF		// elem < min elem
	strb w7, [x1, x8]	// x7 -> min elem
	strb w9, [x1, x6]	// x9 -> elem
	mov x9, x7		// elem := min elem  x9 := x7
ADDFF:				//
	add x5, x5, #1	// j++)***
	b FF			//
ADDSTART:			//
	add x4, x4, #1	// start++)**
	b STARTFIR		//
ADDFIR:				//
	sub x2, x2, #1	// i--)*
	b FIRHALF		//
L0:					// for *(int i = 1;
	add x2, x15, #1	// x2 -- i
SECHALF:			//
	cmp x2, x0		// 
	bge QUIT		// i < n;
	sub x3, x0, x2	// count = n - i	x3 -- count
	mov x4, #0		// for **(start = 0;	x4 -- start
STARTSEC:			//
	cmp x4, x3		//
	bge ADDSEC		// start < count
	add x8, x0, #1	// n + 1
	madd x9, x8, x4, x2	// (n + 1) * start + i	x9 -- offset of minimum
	ldrsb x11, [x1, x9]	// x11 -- min elem
	mov x5, x4		// for ***(int j = start;	x5 -- j
SS:					// 
	cmp x5, x3		//
	bge ADDSTSEC	// j < count
	madd x6, x8, x5, x2	// (n + 1) * j + i	x6 -- offset
	ldrsb x7, [x1, x6]	// x7 -- elem
	cmp x7, x11		// elem < min elem
	bge ADDSS		//
	strb w7, [x1, x9]	//  x7 -> min elem
	strb w11, [x1, x6]	// x11 -> elem
	mov x11, x7		// elem := min elem		x11 := x7
ADDSS:				//
	add x5, x5, #1	// j++)***
	b SS			//
ADDSTSEC:			//
	add x4, x4, #1	// start++)**
	b STARTSEC		//
ADDSEC:				//
	add x2, x2, #1	// i++)*
	b SECHALF		//
QUIT:				// 10 8 4 17 0 11 12 18
	mov x0, #0		// 
	mov x8, #93		// 13 5 15 19 21 22 23 24
	svc #0			//
	.size	_start, .-_start
