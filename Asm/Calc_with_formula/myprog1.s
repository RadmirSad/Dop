	.arch armv8-a
//	signed res = ((a+b)^2-(c-d)^2)/(a + e^3 - c)   =  24475/5 = 4895
	.data
	.align	3
res:
	.skip	8
a:
	.word	150
b:
	.word	100
c:
	.word	200
d:
	.short	5
e:
	.short	-5
	.text
	.align	2
	.global _start
	.type	_start, %function
_start:
	adr x0,	a
	ldrsw	x1, [x0] // load a
	adr x0,	b
	ldrsw	x2, [x0] // load b
	adr	x0, c
	ldrsw	x3, [x0] // load c
	adr	x0, d
	ldrsh	w4, [x0] // load d
	adr	x0, e
	ldrsh	x5, [x0] // load e
	add x2, x1, x2, sxtw // a + b
	sub x4, x3, w4, sxtw // c - d
	mul x6, x2, x2 // (a + b)^2
	smulh x7, x2, x2
	cbnz x7, Z0 // overflow check
	mul x7, x4, x4 // (c - d)^2
	smulh x8, x4, x4
	cbnz x8, Z0	// overflow check
	sub x8, x6, x7 // (a + b)^2 - (c - d)^2
	mul x6, x5, x5 // e*e
	mul x5, x6, x5 // e^3
	add x5, x5, x1 // a + e^3
	sub x5, x5, x3 // a + e^3 - c
	cbz x5, Z0 // divide on zero
	sdiv x8, x8, x5
	b EX
Z0:
	mov x8, #0
	b EX
EX:
	adr x0, res
	str x8, [x0]
	mov x0, #0
	mov x8, #93
	svc #0
	.size _start, .-_start
