section .text

extern GDTPtr

global flushGDT
flushGDT:
    lgdt [GDTPtr]

    mov ax, 0x30 ; Kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    pop rdi

    mov rax, 0x28 ; Kernel code segment
    push rax
    push rdi
    lretq ; Use `lretq` for far return in x86_64