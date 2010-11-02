; �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e
; $Id$


_TEXT_ASM	SEGMENT	page 'CODE'

; void x64_sse2_PredictLeftAndCount_align1(BYTE *pDst, const BYTE *pSrcBegin, const BYTE *pSrcEnd, DWORD *pCountTable)
public	x64_sse2_PredictLeftAndCount_align1
x64_sse2_PredictLeftAndCount_align1	proc

	sub			rsp, 8
	mov			[rsp + 16 +  0], rcx
	mov			[rsp + 16 +  8], rdx
	mov			[rsp + 16 + 16], r8
	mov			[rsp + 16 + 24], r9
	push		rbx
	push		rbp
	push		rsi
	push		rdi
	push		r12
	push		r13
	push		r14
	push		r15
	movdqa		[rsp -  16], xmm6
	movdqa		[rsp -  32], xmm7
	movdqa		[rsp -  48], xmm8
	movdqa		[rsp -  64], xmm9
	movdqa		[rsp -  80], xmm10
	movdqa		[rsp -  96], xmm11
	movdqa		[rsp - 112], xmm12
	movdqa		[rsp - 128], xmm13
	movdqa		[rsp - 144], xmm14
	movdqa		[rsp - 160], xmm15

	mov			eax, 80h
	movd		xmm1, eax

	mov			rsi, qword ptr [rsp + 64 + 16 +  8]	; pSrcBegin
	mov			rdi, qword ptr [rsp + 64 + 16 +  0]	; pDst
	mov			rax, qword ptr [rsp + 64 + 16 + 16]	; pSrcEnd
	sub			rax, rsi
	and			rax, 0fffffffffffffff0h
	add			rax, rsi

	mov			rbx, qword ptr [rsp + 64 + 16 + 24]	; pCountTable

	align		64
label1:
	movdqu		xmm0, oword ptr [rsi]
	movdqa		xmm2, xmm0
	pslldq		xmm2, 1
	por			xmm2, xmm1
	movdqa		xmm1, xmm0
	psrldq		xmm1, 15

	psubb		xmm0, xmm2
	movdqu		oword ptr [rdi], xmm0

	pextrw		ecx, xmm0, 0
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 1
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 2
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 3
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 4
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 5
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 6
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 7
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]

	add			rsi, 16
	add			rdi, 16
	cmp			rsi, rax
	jb			label1

	; �ŏ��̃��C����16�o�C�g�ɖ����Ȃ���������������B
	; �኱�̂͂ݏo���ǂݍ��݂���������B
	mov			rax, qword ptr [rsp + 64 + 16 + 16]	; pSrcEnd
	cmp			rsi, rax
	jae			label4

	movdqu		xmm0, oword ptr [rsi]
	movdqa		xmm2, xmm0
	pslldq		xmm2, 1
	por			xmm2, xmm1
	psubb		xmm0, xmm2

label3:
	movd		ecx, xmm0
	mov			byte ptr [rdi], cl
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	psrldq		xmm0, 1
	inc			rsi
	inc			rdi
	cmp			rsi, rax
	jb			label3

label4:

	movdqa		xmm15, [rsp - 160]
	movdqa		xmm14, [rsp - 144]
	movdqa		xmm13, [rsp - 128]
	movdqa		xmm12, [rsp - 112]
	movdqa		xmm11, [rsp -  96]
	movdqa		xmm10, [rsp -  80]
	movdqa		xmm9,  [rsp -  64]
	movdqa		xmm8,  [rsp -  48]
	movdqa		xmm7,  [rsp -  32]
	movdqa		xmm6,  [rsp -  16]
	pop			r15
	pop			r14
	pop			r13
	pop			r12
	pop			rdi
	pop			rsi
	pop			rbp
	pop			rbx
	add			rsp, 8
	ret

x64_sse2_PredictLeftAndCount_align1	endp


; void x64_sse2_PredictMedianAndCount_align16(BYTE *pDst, const BYTE *pSrcBegin, const BYTE *pSrcEnd, DWORD dwStride, DWORD *pCountTable)
public	x64_sse2_PredictMedianAndCount_align16
x64_sse2_PredictMedianAndCount_align16	proc

	sub			rsp, 8
	mov			[rsp + 16 +  0], rcx
	mov			[rsp + 16 +  8], rdx
	mov			[rsp + 16 + 16], r8
	mov			[rsp + 16 + 24], r9
	push		rbx
	push		rbp
	push		rsi
	push		rdi
	push		r12
	push		r13
	push		r14
	push		r15
	movdqa		[rsp -  16], xmm6
	movdqa		[rsp -  32], xmm7
	movdqa		[rsp -  48], xmm8
	movdqa		[rsp -  64], xmm9
	movdqa		[rsp -  80], xmm10
	movdqa		[rsp -  96], xmm11
	movdqa		[rsp - 112], xmm12
	movdqa		[rsp - 128], xmm13
	movdqa		[rsp - 144], xmm14
	movdqa		[rsp - 160], xmm15

	mov			eax, 80h
	movd		xmm1, eax

	mov			rsi, qword ptr [rsp + 64 + 16 +  8]	; pSrcBegin
	mov			rdi, qword ptr [rsp + 64 + 16 +  0]	; pDst
	mov			rax, rsi
	mov			rdx, qword ptr [rsp + 64 + 16 + 24]	; dwStride
	add			rax, rdx
	neg			rdx
	mov			rbx, qword ptr [rsp + 64 + 16 + 32]	; pCountTable

	align		64
label1:
	movdqa		xmm0, oword ptr [rsi]
	movdqa		xmm2, xmm0
	pslldq		xmm2, 1
	por			xmm2, xmm1
	movdqa		xmm1, xmm0
	psrldq		xmm1, 15

	psubb		xmm0, xmm2
	movdqa		oword ptr [rdi], xmm0

	pextrw		ecx, xmm0, 0
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 1
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 2
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 3
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 4
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 5
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 6
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 7
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]

	add			rsi, 16
	add			rdi, 16
	cmp			rsi, rax
	jb			label1

	mov			rax, qword ptr [rsp + 64 + 16 + 16]	; pSrcEnd

	pxor		xmm1, xmm1
	pxor		xmm5, xmm5

	align		64
label2:
	movdqa		xmm0, oword ptr [rsi]
	movdqa		xmm2, xmm0
	pslldq		xmm2, 1
	por			xmm2, xmm1
	movdqa		xmm1, xmm0
	psrldq		xmm1, 15

	movdqa		xmm4, oword ptr [rsi+rdx]
	movdqa		xmm6, xmm4
	pslldq		xmm6, 1
	por			xmm6, xmm5
	movdqa		xmm5, xmm4
	psrldq		xmm5, 15

	movdqa		xmm7, xmm2
	paddb		xmm7, xmm4
	psubb		xmm7, xmm6

	movdqa		xmm3, xmm2
	pminub		xmm2, xmm4
	pmaxub		xmm3, xmm4
	pmaxub		xmm7, xmm2
	pminub		xmm7, xmm3	; predicted = min(max(min(left, above), grad), max(left, above))

	psubb		xmm0, xmm7
	movdqa		oword ptr [rdi], xmm0

	pextrw		ecx, xmm0, 0
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 1
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 2
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 3
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 4
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 5
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 6
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 7
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]

	add			rsi, 16
	add			rdi, 16
	cmp			rsi, rax
	jb			label2

	movdqa		xmm15, [rsp - 160]
	movdqa		xmm14, [rsp - 144]
	movdqa		xmm13, [rsp - 128]
	movdqa		xmm12, [rsp - 112]
	movdqa		xmm11, [rsp -  96]
	movdqa		xmm10, [rsp -  80]
	movdqa		xmm9,  [rsp -  64]
	movdqa		xmm8,  [rsp -  48]
	movdqa		xmm7,  [rsp -  32]
	movdqa		xmm6,  [rsp -  16]
	pop			r15
	pop			r14
	pop			r13
	pop			r12
	pop			rdi
	pop			rsi
	pop			rbp
	pop			rbx
	add			rsp, 8
	ret

x64_sse2_PredictMedianAndCount_align16	endp


; void x64_sse2_PredictMedianAndCount_align1(BYTE *pDst, const BYTE *pSrcBegin, const BYTE *pSrcEnd, DWORD dwStride, DWORD *pCountTable)
public	x64_sse2_PredictMedianAndCount_align1
x64_sse2_PredictMedianAndCount_align1	proc

	sub			rsp, 8
	mov			[rsp + 16 +  0], rcx
	mov			[rsp + 16 +  8], rdx
	mov			[rsp + 16 + 16], r8
	mov			[rsp + 16 + 24], r9
	push		rbx
	push		rbp
	push		rsi
	push		rdi
	push		r12
	push		r13
	push		r14
	push		r15
	movdqa		[rsp -  16], xmm6
	movdqa		[rsp -  32], xmm7
	movdqa		[rsp -  48], xmm8
	movdqa		[rsp -  64], xmm9
	movdqa		[rsp -  80], xmm10
	movdqa		[rsp -  96], xmm11
	movdqa		[rsp - 112], xmm12
	movdqa		[rsp - 128], xmm13
	movdqa		[rsp - 144], xmm14
	movdqa		[rsp - 160], xmm15

	mov			eax, 80h
	movd		xmm1, eax

	mov			rsi, qword ptr [rsp + 64 + 16 +  8]	; pSrcBegin
	mov			rdi, qword ptr [rsp + 64 + 16 +  0]	; pDst
	mov			rax, rsi
	mov			rdx, qword ptr [rsp + 64 + 16 + 24]	; dwStride
	and			rdx, 0fffffffffffffff0h
	add			rax, rdx
	mov			rbx, qword ptr [rsp + 64 + 16 + 32]	; pCountTable

	; �ŏ��̃��C����16�o�C�g����������B
	align		64
label1:
	movdqu		xmm0, oword ptr [rsi]
	movdqa		xmm2, xmm0
	pslldq		xmm2, 1
	por			xmm2, xmm1
	movdqa		xmm1, xmm0
	psrldq		xmm1, 15

	psubb		xmm0, xmm2
	movdqu		oword ptr [rdi], xmm0

	pextrw		ecx, xmm0, 0
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 1
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 2
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 3
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 4
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 5
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 6
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 7
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]

	add			rsi, 16
	add			rdi, 16
	cmp			rsi, rax
	jb			label1

	; �ŏ��̃��C����16�o�C�g�ɖ����Ȃ���������������B
	; �኱�̂͂ݏo���ǂݍ��݂���������B
	mov			rax, qword ptr [rsp + 64 + 16 +  8]	; pSrcBegin
	add			rax, qword ptr [rsp + 64 + 16 + 24]	; dwStride
	cmp			rsi, rax
	jae			label4

	movdqu		xmm0, oword ptr [rsi]
	movdqa		xmm2, xmm0
	pslldq		xmm2, 1
	por			xmm2, xmm1
	psubb		xmm0, xmm2

label3:
	movd		ecx, xmm0
	mov			byte ptr [rdi], cl
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	psrldq		xmm0, 1
	inc			rsi
	inc			rdi
	cmp			rsi, rax
	jb			label3

	; �c��̃��C����16�o�C�g����������B
label4:
	mov			rdx, qword ptr [rsp + 64 + 16 + 24]	; dwStride
	neg			rdx
	mov			rax, qword ptr [rsp + 64 + 16 + 16]	; pSrcEnd
	sub			rax, rsi
	and			rax, 0fffffffffffffff0h
	add			rax, rsi

	pxor		xmm1, xmm1
	pxor		xmm5, xmm5

	align		64
label2:
	movdqu		xmm0, oword ptr [rsi]
	movdqa		xmm2, xmm0
	pslldq		xmm2, 1
	por			xmm2, xmm1
	movdqa		xmm1, xmm0
	psrldq		xmm1, 15

	movdqu		xmm4, oword ptr [rsi+rdx]
	movdqa		xmm6, xmm4
	pslldq		xmm6, 1
	por			xmm6, xmm5
	movdqa		xmm5, xmm4
	psrldq		xmm5, 15

	movdqa		xmm7, xmm2
	paddb		xmm7, xmm4
	psubb		xmm7, xmm6

	movdqa		xmm3, xmm2
	pminub		xmm2, xmm4
	pmaxub		xmm3, xmm4
	pmaxub		xmm7, xmm2
	pminub		xmm7, xmm3	; predicted = min(max(min(left, above), grad), max(left, above))

	psubb		xmm0, xmm7
	movdqu		oword ptr [rdi], xmm0

	pextrw		ecx, xmm0, 0
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 1
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 2
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 3
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 4
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 5
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 6
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]
	pextrw		ecx, xmm0, 7
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	movzx		ebp, ch
	inc			dword ptr [rbx+rbp*4]

	add			rsi, 16
	add			rdi, 16
	cmp			rsi, rax
	jb			label2

	; �c��̃��C����16�o�C�g�ɖ����Ȃ���������������B
	; �኱�̂͂ݏo���ǂݍ��݂���������B
	mov			rax, qword ptr [rsp + 64 + 16 + 16]	; pSrcEnd
	cmp			rsi, rax
	jae			label6

	movdqu		xmm0, oword ptr [rsi]
	movdqa		xmm2, xmm0
	pslldq		xmm2, 1
	por			xmm2, xmm1

	movdqu		xmm4, oword ptr [rsi+rdx]
	movdqa		xmm6, xmm4
	pslldq		xmm6, 1
	por			xmm6, xmm5

	movdqa		xmm7, xmm2
	paddb		xmm7, xmm4
	psubb		xmm7, xmm6

	movdqa		xmm3, xmm2
	pminub		xmm2, xmm4
	pmaxub		xmm3, xmm4
	pmaxub		xmm7, xmm2
	pminub		xmm7, xmm3	; predicted = min(max(min(left, above), grad), max(left, above))

	psubb		xmm0, xmm7

label5:
	movd		ecx, xmm0
	mov			byte ptr [rdi], cl
	movzx		ebp, cl
	inc			dword ptr [rbx+rbp*4]
	psrldq		xmm0, 1
	inc			rsi
	inc			rdi
	cmp			rsi, rax
	jb			label5


label6:

	movdqa		xmm15, [rsp - 160]
	movdqa		xmm14, [rsp - 144]
	movdqa		xmm13, [rsp - 128]
	movdqa		xmm12, [rsp - 112]
	movdqa		xmm11, [rsp -  96]
	movdqa		xmm10, [rsp -  80]
	movdqa		xmm9,  [rsp -  64]
	movdqa		xmm8,  [rsp -  48]
	movdqa		xmm7,  [rsp -  32]
	movdqa		xmm6,  [rsp -  16]
	pop			r15
	pop			r14
	pop			r13
	pop			r12
	pop			rdi
	pop			rsi
	pop			rbp
	pop			rbx
	add			rsp, 8
	ret

x64_sse2_PredictMedianAndCount_align1	endp


; p{min,max}ub �� SSE1 �Œǉ����ꂽ MMX ���߁i������ MMX2 ���߁j�ł���B
; void x64_sse1mmx_RestoreMedian_align1(BYTE *pDst, const BYTE *pSrcBegin, const BYTE *pSrcEnd, DWORD dwStride)
x64_sse1mmx_RestoreMedian_align1	proc

	sub			rsp, 8
	mov			[rsp + 16 +  0], rcx
	mov			[rsp + 16 +  8], rdx
	mov			[rsp + 16 + 16], r8
	mov			[rsp + 16 + 24], r9
	push		rbx
	push		rbp
	push		rsi
	push		rdi
	push		r12
	push		r13
	push		r14
	push		r15

	mov			rsi, qword ptr [rsp + 64 + 16 +  8]	; pSrcBegin
	mov			rdi, qword ptr [rsp + 64 + 16 +  0]	; pDst
	mov			rax, rsi
	mov			rbp, qword ptr [rsp + 64 + 16 + 24]	; dwStride
	add			rax, rbp
	neg			rbp

	mov			edx, 80h

	align		64
label1:
	add			dl, byte ptr [rsi]
	mov			byte ptr [rdi], dl
	inc 		rsi
	inc			rdi
	cmp			rsi, rax
	jb			label1

	pxor		mm4, mm4
	pxor		mm2, mm2

	align		64
label2:
	movq		mm6, mm2
	movq		mm7, mm2
	psubb		mm6, mm4
	movd		mm4, dword ptr [rdi+rbp]	; mm4 = above
	paddb		mm6, mm4					; mm6 = grad

	pminub		mm2, mm6
	pmaxub		mm6, mm7
	pmaxub		mm2, mm4
	pminub		mm2, mm6					; mm2 = median

	paddb		mm2, qword ptr [rsi]		; �A���C�����g������Ă��Ă� xmm ���W�X�^�̏ꍇ�ƈ���Ĉ�ʕی��O�ɂ͂Ȃ�Ȃ�
	movd		eax, mm2
	mov			byte ptr [rdi], al

	inc			rsi
	inc			rdi
	cmp			rsi, qword ptr [rsp + 64 + 16 + 16]	; pSrcEnd
	jb			label2

	pop			r15
	pop			r14
	pop			r13
	pop			r12
	pop			rdi
	pop			rsi
	pop			rbp
	pop			rbx
	add			rsp, 8
	emms
	ret

x64_sse1mmx_RestoreMedian_align1	endp


end