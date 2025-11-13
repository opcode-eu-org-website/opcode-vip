# fragment kodu asemblerowego wygenerowanego poleceniem "gcc -S" z kodu C:
#    if (argc == 1)
#        puts("A");
#    else
#        puts("B");
#    puts("C");

# operacja porównania                                      --- warunek if
	cmpl	$1, -4(%rbp)
# skok jeżeli nie równe do bloku else
	jne	.L2
# odłożenie argumentu "A" na stos i wywołanie funkcji puts --- blok if
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
# skok bezwarunkowy za blok if - else
	jmp	.L3
.L2:
# odłożenie argumentu "B" na stos i wywołanie funkcji puts --- blok else
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
.L3:
# odłożenie argumentu "C" na stos i wywołanie funkcji puts --- kod po if-else
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
