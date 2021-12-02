.data
scan_str:
	.string "%s%d"

print_str:
	.string "%d\n"

.text
.global _main
_main:
	subq $24, %rsp

	# int n     @ 0(%rbp)
	# char s[8] @ 8(%rbp)

	xorl %r15d, %r15d              # dep = 0
	xorl %r14d, %r14d              # hor = 0
	xorl %r13d, %r13d              # aim = 0

.L_loop:
	# scanf("%s%d", s, &n)

	leaq scan_str(%rip), %rdi      # arg1 = "%s%d"
	leaq 8(%rbp), %rsi             # arg2 = s
	movq %rbp, %rdx                # arg3 = n
	xorl %eax, %eax
	call _scanf

	cmpl $-1, %eax                 # if scanf hits EOF, break
	je .L_loop_done

	movl (%rbp), %ecx              # load n
	movb 8(%rbp), %dl              # load s[0]

	cmpb $'f', %dl                # if s[0] == 'f', go forward
	je .L_loop_fwd
	cmpb $'u', %dl                # if s[0] == 'u', go up
	je .L_loop_up
	                              # otherwise, go down

	addl %ecx, %r13d 	      # aim += n
	jmp .L_loop

.L_loop_fwd:
	addl %ecx, %r14d              # hor += n
	movl %r13d, %edx              # load aim
	imull %ecx, %edx              # compute aim * n
	addl %edx, %r15d              # dep += aim * n
	jmp .L_loop

.L_loop_up:
	subl %ecx, %r13d              # aim -= n
	jmp .L_loop

.L_loop_done:
	# printf("%d\n", hor * dep)

	leaq print_str(%rip), %rdi     # arg1 = "%d\n"
	movl %r14d, %esi               # arg2 = hor
	imull %r15d, %esi              # arg2 *= dep
	xorl %eax, %eax
	call _printf

	addq $24, %rsp
	ret