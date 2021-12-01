.data
scan_str:
	.string "%lu"

print_str:
	.string "%lu\n"

.text
.global _main
_main:
	subq $8, %rsp

.L_scan_loop:
	# scanf("%u", &n)

	leaq scan_str(%rip), %rdi      # arg1 = "%u"
	movq %rsp, %rsi                # arg2 = &n
	xorl %eax, %eax
	call _scanf

	cmpl $-1, %eax                 # if scanf hits EOF, break
	je .L_scan_done

	subq $8, %rsp                  # save n on the stack
	jmp .L_scan_loop

.L_scan_done:
	xorl %r14d, %r14d              # count = 0
	leaq -8(%rbp), %r12            # ptr1 = &arr[-1]
	leaq -32(%rbp), %r13           # ptr2 = &arr[3]

.L_compute_loop:
	subq $8, %r12                  # ptr1++
	subq $8, %r13                  # ptr2++

	cmpq %r13, %rsp                # if ptr2 == arr end, break
	je .L_compute_done

	movq (%r12), %rax              # a = *ptr1
	cmpq %rax, (%r13)              # if *ptr2 > a, count++
	jbe .L_compute_loop

	addl $1, %r14d                 # count++
	jmp .L_compute_loop

.L_compute_done:

	# printf("%u\n", count)

	leaq print_str(%rip), %rdi     # arg1 = "%u\n"
	movl %r14d, %esi               # arg2 = count
	xorl %eax, %eax
	call _printf

	movq %rbp, %rsp
	subq $8, %rsp
	movl $0, %eax                  # EXIT_SUCCESS
	ret