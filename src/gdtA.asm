section .text

extern GDTPtr

global flushGDT
flushGDT:
    cli
    lgdt [GDTPtr]
    mov ax, 0x10
    mov ax, ds
    mov ax, es
    mov ax, fs
    mov ax, gs
    mov ax, ss
    
    pop rdi
    push 0x8
    push rdi
    lretq