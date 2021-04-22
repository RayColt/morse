#include <cstdlib>

/*
* Midnight Commander for Windows
* Nice C++ executable to put in System32, to run mc system wide like in Linux!!
*/
int main()
{ 
    system("\"\"C:\\Program Files (x86)\\\Midnight Commander\\\mc.exe\"");
}


        .file   "mc.c"
        .text
        .section        .rodata
        .align 8
.LC0:
        .string "\"\"C:\\Program Files (x86)\\Midnight Commander\\mc.exe\""
        .text
        .globl  main
        .type   main, @function
main:
.LFB15:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        movq    %rsp, %rbp
        .cfi_def_cfa_register 6
        leaq    .LC0(%rip), %rdi
        call    system@PLT
        movl    $0, %eax
        popq    %rbp
        .cfi_def_cfa 7, 8
        ret
        .cfi_endproc
.LFE15:
        .size   main, .-main
        .ident  "GCC: (Debian 10.2.0-16) 10.2.0"
        .section        .note.GNU-stack,"",@progbits
