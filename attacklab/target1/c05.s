movl $0x61663739, 0x4(%rdi)
movl $0x39623935, (%rdi)
movb $0x0, 0x8(%rdi)

mov %rax, (%rdi)
push $0x4018fa
shl $0x2, %rax
retq