	.arch armv8-a
	.data
incorparam:
	.string	"\n Incorrect number of parameters\n"
	.equ	incorparamlen, .-incorparam
nofile:
	.string	"\n File with this name doesn't exist\n"
	.equ	nofilelen, .-nofile
incoract:
	.string	"\n Incorrect type of action\n"
	.equ	incoractlen, .-incoract
inform:
	.string	"\n There should be 3 parameters\n 1 parameter - active file\n 2 parameter - passive file\n 3 parameter - type of action: 1 is compact, 2 is restore\n"
	.equ	informlen, .-inform
	.text
	.align	2
	.global _start
	.type	_start, %function
_start:
	ldr x0, [sp]
	cmp x0, #4	// check the number of parameters entered
	beq 0f		// if it's a match, get to work
	mov x0, #2	// else write error message
	adr x1, incorparam
	mov x2, incorparamlen
	mov x8, #64
	svc #0
	mov x0, #1
	b info
0:
	ldr x1, [sp, #16]	// load name of first file
	mov x0, #-100	// trying to open first file
	mov x2, #0		// open for read
	mov x8, #56
	svc #0			// get file descriptor
	cmp x0, #0		// check on error of opening
	bge 1f
	mov x0, #2
	adr x1, nofile	// write error message
	mov x2, nofilelen
	mov x8, #64
	svc #0
	b info
1:
	ldr x1, [sp, #24]	// open passive file
	mov x21, x0		// fd of active file in x0 -> x21
	mov x0, #-100
	mov x2, #0x201	// 0x200 + 1 to write and clear file
	mov x8, #56
	svc #0
	mov x1, x0		// fd of passive file in x0 -> x1
	mov x0, x21		// x21 -> x0
	ldr x2, [sp, #32]	// trying to define type of the transformation
	ldrb w2, [x2]
	mov w6, '1'
	cmp w2, w6
	beq 2f			// if 1 -> compact the string
	mov w6, '2'
	cmp w2, w6
	beq 3f			// if 2 -> restore the line
	bl close		// close files x0 - act file, x1 - pas file
	mov x0, #2		// write error
	adr x1, incoract
	mov x2, incoractlen
	mov x8, #64
	svc #0
	b info
2:
	bl dopcomp		// x0 - fd of act file, x1 - fd of pas file
	mov x0, #-100	// open pas file for check our result
	mov x2, #0		// open for read
	ldr x1, [sp, #24]	// load name of sec file
	mov x8, #56
	svc #0
	mov x29, x0
	bl printtext	// x0 - fd
	mov x0, x29		// close pas file
	mov x8, #57
	svc #0
	b exit
3:
	bl doprest
	mov x0, #-100
	mov x2, #0
	ldr x1, [sp, #24]
	mov x8, #56
	svc #0
	mov x16, #144	// 144 buf + 8 x29 + 8 fd
	sub sp, sp, x16
	str x29, [sp]
	mov x29, sp
	str x0, [x29, #8]	// save fd
print:
	ldr x0, [x29, #8]
	add x1, x29, #16	// x1 - buf
	mov x2, #128
	mov x8, #63
	svc #0
	cmp x0, #0
	beq endprint
	mov x2, x0
	mov x0, #1			// print x0 bytes from buf
	add x1, x29, #16
	mov x8, #64
	svc #0
	b print
endprint:
	ldr x0, [x29, #8]
	ldr x29, [sp]
	mov x16, #144
	add sp, sp, x16
	mov x8, #57			// close pas file
	svc #0
	b exit
info:
	mov x0, #0		// write information
	adr x1, inform
	mov x2, informlen
	mov x8, #64
	svc #0
	mov x0, #1
exit:
	mov x8, #93
	svc #0
	.size 	_start, .-_start
	.type	dopcomp, %function
	.data
frerr:
	.string "\n File read error\n"
	.equ	frerrlen, .-frerr
	.text
	.align 2
	.equ	fdact, 16
	.equ	fdpas, 24
	.equ	buf, 32
dopcomp:
	mov x16, #168		// 128 buf + 8 x29 + 8 x30 + 8 fdact + 8 fdpas
	sub sp, sp, x16		// highlight the stack frame
	stp x29, x30, [sp]	// save data from x29, x30 into sp
	mov x29, sp			// save our sp in x29
	str x0, [x29, fdact]	// save fd of act file
	str x1, [x29, fdpas]	// save fd of pas file
0:
	ldr x0, [x29, fdact]	// load fd of act file
	add x1, x29, buf		// trying to read smtg from act file
	mov x2, #128			// read on 128b
	mov x8, #63
	svc #0
	cmp x0, #0				// compare with 0   count (x0)
	beq 1f					// if number of read symbols = 0 -> close files
	bgt comp				// if number > 0 -> work with string
	mov x0, #2				// else write error
	adr x1, frerr
	mov x2, frerrlen
	mov x8, #64
	svc #0
	b closefiles
comp:						// print symbols from buf
	sub x0, x0, #1			// count = num of read symbols without \0
	str x0, [sp, #-8]!		// save num of read symbols
	mov x2, x0				// copy number of read symbols in x2
	mov x0, #1
	add x1, x29, buf
	mov x8, #64
	svc #0
	mov w2, '\n'
	strb w2, [sp, #-1]!
	mov x1, sp
	mov x0, #1
	mov x2, #1
	mov x8, #64
	svc #0
	ldrb w2, [sp], #1
	ldr x0, [sp], #8		// load count
	ldr x1, [x29, fdpas]	// load fd of pas file
	add x2, x29, buf		// get adr of buf
	bl compact				// let's compact our buf, x0 - numb of all symb, x1 - fd of pas file, x2 - adr of buf
	b	0b
1:
	ldr x0, [x29, fdpas]	// load fd pas
	mov x3, #0				// dopint = 0
	str x3, [sp, #-8]!		// get &dopint
	mov x1, sp				// fwrite(&dopint, 1,sizeof(int),pas)
	mov x2, #1
	mov x8, #64
	svc #0
	ldr x0, [x29, fdpas]	// fwrite(&dopint,1,sizeof(int),pas)
	svc #0
	ldr x3, [sp], #8		// load x3
	mov x8, #0			// symb = \0
	ldr x0, [x29, fdpas]	// load fd of pas file
	str x8, [sp, #-8]!		// save '\0'
	mov x1, sp				// fwrite(&symb, sizeof(char),1,pas)
	mov x2, #1
	mov x8, #64
	svc #0
	ldr x8, [sp], #8		// now let's close the files
closefiles:
	ldr x0, [x29, fdact]
	ldr x1, [x29, fdpas]
	bl close				// close files
endcomp:
	ldp x29, x30, [sp]
	mov x16, #168
	add sp, sp, x16
	ret
	.size	dopcomp, .-dopcomp
	.type	compact, %function
	.data
errwrite:
	.string "\n Error of writing symbol\n"
	.equ	errwritelen, .-errwrite
	.text
	.align 2
	.equ	count, 16
	.equ	fdps, 24
	.equ	buf, 32
compact:					// x0 - count, x1 - fd pas, x2 - buf
	stp x29, x30, [sp, #-48]!	// save x29, x30
	mov x29, sp
	str x0, [x29, count]	// save count
	str x1, [x29, fdps]		// save fd of pas file
	str x2, [x29, buf]		// save adr of buf
	mov x3, #0				// mainin (x3) = 0  
	mov x4, #0				// buf_ind (x4) = 0 index to pass through the characters further down the line  
	mov x19, #0				// flag end_of_buf (x19)
0:
	ldr x0, [x29, count]	// load count
	cmp x3, x0				// while (mainin < count)
	bge endcp				// {
	mov x5, #0				// offset (x5) = 0 offset value that will be written in file
	mov x6, #0				// max_length (x6) = 0 length that will be written in file
	mov x7, #0				// dop_ind (x7) = 0 additional index for traversing the previous characters
	ldr x2, [x29, buf]
1:							// while (dop_ind < mainin)	 compare dop_ind (x7) and mainin (x3)
	cmp x7, x3				// 
	bge 5f					// {
	mov x9, #0				// length (x9) = 0	temporal value of the length of the matching part of the string
	sub x10, x3, x7			// dop_off (x10)  = mainin (x3) - dop_ind (x7) additional value of the offset
	ldrb w8, [x2, x3]		// symb (w8) = buf[mainin]
	ldrb w11, [x2, x7]		// dict (w11) = buf[dop_ind (x7)]
	add x4, x3, x9			// buf_ind (x4) = mainin (x3) + length (x9)
2:
	ldr x0, [x29, count]
	cmp x4, x0				// while ((buf_ind < count) && (dict == symb))
	bge 3f
	cmp w11, w8
	bne 3f					// {
	add x9, x9, #1			// length++ (x9)
	add x4, x7, x9			// buf_ind (x4) = dop_ind (x7) + length (x9)
	ldrb w11, [x2, x4]		// dict (w11) = buf[buf_ind(x4)]
	add x4, x3, x9			// buf_ind = mainin + length
	ldrb w8, [x2, x4]		// symb = buf[buf_ind]
	b 2b					// }
3:
	cmp x9, x6				// if (length > max_length)
	ble 4f					// {
	mov x6, x9				// max_length (x6) = length (x9)
	mov x5, x10				// offset (x5) = dop_off (x10) }
4:							//
	add x7, x7, #1			// dop_ind++ (x7)
	b 1b					// }
5:
	ldr x0, [x29, fdps]		// load fd of pas file
	str x5, [sp, #-8]!		// save offset in sp
	mov x1, sp				// write offset in file
	mov x2, #1				// fwrite(&offset, sizeof(int), 1, pasfile)
	mov x8, #64
	svc #0
	ldr x5, [sp], #8		// load x5
	cmp x0, #1				// if symb hasn's been written write error
	bne err
	ldr x0, [x29, fdps]		// load fd
	str x6, [sp, #-8]!		// save max_length (x6)
	mov x1, sp				// write max_length in file
	mov x2, #1				// fwrite(&max_length, sizeof(inf), 1, pasfile)
	mov x8, #64
	svc #0
	ldr x6, [sp], #8		// load max_length (x6)
	cmp x0, #1
	bne err
	add x4, x3, x6			// buf_ind = mainin + max_length
	ldr x0, [x29, count]	// load count (x0)
	cmp x4, x0				// if (buf_ind >= count)
	blt 6f
	mov w8, '\n'			// symb (w8) = '\n'
	strb w8, [sp, #-1]!		// save symb in sp
	ldr x0, [x29, fdps]		// write symb in pas file
	mov x1, sp				// fwrite(&symb, sizeof(char), 1, pasfile)
	mov x2, #1
	mov x8, #64
	svc #0
	cmp x0, #1
	bne err
	ldrb w8, [sp], #1		// load symb from sp
	mov x19, #1				// flag end_of_buf (x19) = 1
	b 7f
6:							// else
	ldr x0, [x29, fdps]		// fwrite(buf + buf_ind, sizeof(char), 1, pasfile)
	ldr x2, [x29, buf]		// load buf in x2
	add x1, x2, x4			// x1 = buf + buf_ind
	mov x2, #1
	mov x8, #64
	svc #0
	cmp x0, #1
	bne err
7:
	add x6, x6, #1			// 
	mov x4, x6				// buf_ind = max_length + 1
	add x3, x3, x4			// mainin (x3) += buf_ind (x4)
	ldr x0, [x29, count]	// load count in x0
	cmp x3, x0				// if((mainin >= count) && (!eof))
	blt 0b
	cbnz x19, 0b
	str x19, [sp, #-8]!	// save eob in sp (eob = 0)
	ldr x0, [x29, fdps]		// load fd of pas file in x0
	mov x1, sp				// fwrite(&eob, sizeof(int), 1, pasfile)
	mov x2, #1
	mov x8, #64
	svc #0
	cmp x0, #1				// check on err of writing
	bne err
	ldr x0, [x29, fdps]		// fwrite(&eob, sizeof(int), 1, pasfile)
	mov x1, sp
	mov x2, #1
	mov x8, #64
	svc #0
	cmp x0, #1
	bne err
	ldr x19, [sp], #8
	mov w8, '\n'			// symb (w8) = '\n'
	strb w8, [sp, #-1]!		// save w8 in sp
	ldr x0, [x29, fdps]		// load fd
	mov x1, sp				// fwrite(&symb, sizeof(char), 1, pasfile)
	mov x2, #1
	mov x8, #64
	svc #0
	cmp x0, #1
	bne err
	ldrb w8, [sp], #1
	b 0b					// }
err:
	mov x0, #2
	adr x1, errwrite
	mov x2, errwritelen
	mov x8, #64
	svc #0
endcp:
	ldp x29, x30, [sp], #48
	ret
	.size	compact, .-compact
	.type	doprest, %function
	.data
frderr:
	.string "\n File read error\n"
	.equ	frderrlen, .-frderr
errrs:
	.string "\n Unknown error of restoring\n"
	.equ	errrslen, .-errrs
	.text
	.align 2
	.equ	fdact, 16
	.equ	fdpas, 24
	.equ	tsymb, 32
	.equ	buf, 40
	.equ	ssize, 3
doprest:
	mov x16, #168		// 128 buf + 8 x29 + 8 x30 + 8 fdact + 8 fdpas + 8 for 3 symb
	sub sp, sp, x16
	stp x29, x30, [sp]
	mov x29, sp
	str x0, [x29, fdact]
	str x1, [x29, fdpas]
	mov x10, #0			// index (x10) = 0
0:
	ldr x0, [x29, fdact]
	add x1, x29, tsymb	// x1 - symb[3]
	mov x2, ssize		// trying to read 3 symbols
	mov x8, #63
	svc #0
	cmp x0, #0
	blt errred			// if symbols weren't read go write error
	mov x5, #0			// int i (x5) = 0
	mov x6, x10			// int bind (x6) = index (x10)
	add x2, x29, tsymb	// x2 - tsymb[3]
	add x3, x29, buf	// x3 - buf[128]
	ldrb w8, [x2]		// offset (x8) = tsymb[0]
	mov x4, #0			// length (x4) = \0
	ldrb w4, [x2, #1]	// length (x4) = tsymb[1]
1:
	cmp x5, x4			// compare i and length
	bge 2f				// while (i < length)
	sub x7, x6, x8		// int dop (x7) = bind - offset + i
	add x7, x7, x5
	ldrb w9, [x3, x7]	// load dop_symbol (w9) = buf[dop]
	strb w9, [x3, x10]	// save symbol (w9) in buf[index] (buf[index] = buf[dop])
	add x10, x10, #1	// index++
	add x5, x5, #1		// i++
	b 1b
2:
	ldrb w5, [x2, #2]!	// load symbol (w5) = tsymb[2]
	strb w5, [x3, x10]	// buf[index] = symbol
	add x10, x10, #1	// index++
	cmp x10, #128		// 128 - character number
	blt 3f
	bne errrest
	ldr x0, [x29, fdpas]// fwrite(buf, sizeof(char), index, pasfile)
	mov x1, x3
	mov x2, #128
	mov x8, #64
	svc #0
	mov x10, #0			// index = 0
3:
	cbz w5, 4f
	b 0b
4:
	sub x2, x10, #1			// get index in x2
	ldr x0, [x29, fdpas]// fwrite(buf,sizeof(char), index, pasfile)
	add x1, x29, buf
	mov x8, #64
	svc #0
	b cl
errrest:				// write err and close files
	mov x0, #2
	adr x1, errrs
	mov x2, errrslen
	mov x8, #64
	svc #0
	b cl
errred:
	mov x0, #2			// write error and close files
	adr x1, frderr
	mov x2, frderrlen
	mov x8, #64
	svc #0
cl:
	ldr x0, [x29, fdact]
	ldr x1, [x29, fdpas]
	bl close
endrest:
	ldp x29, x30, [sp]
	mov x16, #168
	add sp, sp, x16
	ret
	.size	doprest, .-doprest
	.type	close, %function
	.text
	.align 2
	.equ	fdpas, 16
close:					// x0 - fd act file, x1 - fd pas file
	sub sp, sp, #32		// 8 x29 + 8 x30 + 8 fdpas + 8 for divide 16
	stp x29, x30, [sp]	// save x29 and x30
	mov x29, sp
	str x1, [x29, fdpas] // save fd pas in x28 <=> sp
	mov x8, #57			// close act file
	svc #0
	ldr x0, [x29, fdpas]// load fd pas from x28
	mov x8, #57			// close pas file
	svc #0
	ldp x29, x30, [sp]	// load x28, x30
	add sp, sp, #32
	ret
	.size	close, .-close
	.type	printtext, %function
	.text
	.align 2
	.equ	fd, 16
	.equ	symb, 24
printtext:
	sub sp, sp, #32		// make buf on 4 symb
	stp x29, x30, [sp]
	mov x29, sp
	str x0, [x29, fd]	// save fd in x29
0:
	ldr x0, [x29, fd]	// while 3 symb != '\0'
	add x1, x29, symb	// read from file 3 symbols in x1
	mov x2, #3
	mov x8, #63
	svc #0
	mov w7, ','
	add x1, x29, symb
	strb w7, [x1, #3]	// save symb , on 4th place
	mov x0, x1			// print 1 number
	bl printnumb
	mov x0, #2
	add x1, x29, #27	// print ','
	mov x2, #1
	mov x8, #64
	svc #0
	add x0, x29, #25		// print 2 number
	bl printnumb
	mov x0, #2
	add x1, x29, #27
	mov x2, #1
	mov x8, #64
	svc #0
	add x1, x29, #26		// print 3 symbol
	mov x0, #2
	mov x2, #1
	mov x8, #64
	svc #0
	mov w7, ' '
	strb w7, [x29, #27]		// save ' '
	add x1, x29, #27		// print forth symbol
	mov x0, #2
	mov x2, #1
	mov x8, #64
	svc #0
	add x1, x29, symb
	ldrb w7, [x1, #2]
	cbnz w7, 0b			// if symb 3 == \0
	ldp x29, x30, [sp]
	add sp, sp, #32
	ret
	.size	printtext, .-printtext
	.type	printnumb, %function
	.text
	.align 2
	.equ	num, 16
printnumb:				// x0 - adr of symb
	sub sp, sp, #24		// save x29, x30, x0
	stp x29, x30, [sp]
	mov x29, sp
	ldrb w1, [x0]		// load number
	strb w1, [x29, num]	// save number
	mov w4, #100
	udiv w1, w1, w4		// get first num and print it
	ldrb w2, [x29, num]
	mul w3, w1, w4
	sub w2, w2, w3
	strb w2, [x29, num]// save sec number
	add w1, w1, #48
	strb w1, [sp, #-1]!
	mov x1, sp
	mov x0, #2
	mov x2, #1
	mov x8, #64
	svc #0
	ldrb w1, [x29, num]
	mov w4, #10
	udiv w1, w1, w4		// get second number
	ldrb w2, [x29, num]
	mul w3, w1, w4
	sub w2, w2, w3
	strb w2, [x29, num]
	add w1, w1, #48
	strb w1, [sp]
	mov x1, sp
	mov x0, #2
	mov x2, #1
	mov x8, #64
	svc #0
	ldrb w1, [x29, num]	// get third number
	add w1, w1, #48
	strb w1, [sp]
	mov x1, sp
	mov x0, #2
	mov x2, #1
	mov x8, #64
	svc #0
	add sp, sp, #1
	ldp x29, x30, [sp]
	add sp, sp, #24
	ret
	.size	printnumb, .-printnumb
