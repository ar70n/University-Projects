	.file	"simple2.c"
	.text
	.local	a
	.comm	a,16384,32
	.local	b
	.comm	b,16384,32
	.local	c
	.comm	c,8,8
	.section	.rodata
.LC1:
	.string	"gettimeofday"
.LC3:
	.string	"%lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -68(%rbp)
	movq	%rsi, -80(%rbp)
	vmovsd	.LC0(%rip), %xmm0
	vmovsd	%xmm0, -16(%rbp)
	leaq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday@PLT
	testl	%eax, %eax
	je	.L2
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L2:
	movl	$0, -4(%rbp)
	jmp	.L3
.L4:
	vcvtsi2sdl	-4(%rbp), %xmm0, %xmm0
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	b(%rip), %rax
	vmovsd	%xmm0, (%rdx,%rax)
	movl	-4(%rbp), %eax
	addl	$1, %eax
	vcvtsi2sdl	%eax, %xmm0, %xmm0
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	a(%rip), %rax
	vmovsd	%xmm0, (%rdx,%rax)
	addl	$1, -4(%rbp)
.L3:
	cmpl	$2047, -4(%rbp)
	jle	.L4
	movl	$0, -8(%rbp)
	jmp	.L5
.L8:
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	a(%rip), %rax
	vmovsd	(%rdx,%rax), %xmm0
	vmulsd	-16(%rbp), %xmm0, %xmm1
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	b(%rip), %rax
	vmovsd	(%rdx,%rax), %xmm0
	vaddsd	%xmm0, %xmm1, %xmm1
	vmovsd	c(%rip), %xmm0
	vaddsd	%xmm0, %xmm1, %xmm0
	vmovsd	%xmm0, c(%rip)
	addl	$1, -4(%rbp)
.L6:
	cmpl	$2047, -4(%rbp)
	jle	.L7
	addl	$1, -8(%rbp)
.L5:
	cmpl	$999999, -8(%rbp)
	jle	.L8
	leaq	-64(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday@PLT
	testl	%eax, %eax
	je	.L9
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L9:
	movq	-64(%rbp), %rdx
	movq	-48(%rbp), %rax
	subq	%rax, %rdx
	vcvtsi2sdq	%rdx, %xmm1, %xmm1
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	subq	%rax, %rdx
	vcvtsi2sdq	%rdx, %xmm0, %xmm0
	vmovsd	.LC2(%rip), %xmm2
	vdivsd	%xmm2, %xmm0, %xmm0
	vaddsd	%xmm0, %xmm1, %xmm0
	vmovsd	%xmm0, -24(%rbp)
	movq	-24(%rbp), %rax
	vmovq	%rax, %xmm0
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	-611603343
	.long	1072693352
	.align 8
.LC2:
	.long	0
	.long	1093567616
	.ident	"GCC: (Debian 14.2.0-6) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
