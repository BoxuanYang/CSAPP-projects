
c05.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	c7 47 04 39 37 66 61 	movl   $0x61663739,0x4(%rdi)
   7:	c7 07 35 39 62 39    	movl   $0x39623935,(%rdi)
   d:	c6 47 08 00          	movb   $0x0,0x8(%rdi)
  11:	48 89 07             	mov    %rax,(%rdi)
  14:	68 fa 18 40 00       	pushq  $0x4018fa
  19:	48 c1 e0 02          	shl    $0x2,%rax
  1d:	c3                   	retq   
