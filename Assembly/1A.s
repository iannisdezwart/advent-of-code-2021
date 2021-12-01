.data
scan_str:
	.string "%u"

print_str:
	.string "%u\n"

.text
.global _main
_main:
	subq $8, %rsp

	movl $-1, %r15d                # old = MAX
	movl $0, %r14d                 # count = 0

.L_scan_loop:
	# scanf("%u", &n)

	leaq scan_str(%rip), %rdi      # arg1 = "%u"
	movq %rsp, %rsi                # arg2 = &n
	xorl %eax, %eax
	call _scanf

	cmpl $-1, %eax                 # if scanf hits EOF, break
	je .L_scan_done

	movl (%rsp), %edx              # load n
	cmpl %r15d, %edx               # n <= old
	jbe .L_scan_loop_skip

	addl $1, %r14d                 # count++

.L_scan_loop_skip:
	movl %edx, %r15d               # old = n
	jmp .L_scan_loop

.L_scan_done:
	# printf("%u\n", count)

	leaq print_str(%rip), %rdi     # arg1 = "%u\n"
	movl %r14d, %esi               # arg2 = count
	xorl %eax, %eax
	call _printf

	addq $8, %rsp
	movl $0, %eax                  # EXIT_SUCCESS
	ret