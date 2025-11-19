[bits 16]
[org 0x7c00]

jmp start

%include "include/common.h"

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    ; VGA 320x200x256
    mov ax, 0x0013
    int 0x10

    ; Učitaj 60 sektora kernela na 0x100000 (1MB)
    mov ax, 0x1000
    mov es, ax
    xor bx, bx
    mov ah, 2
    mov al, 60
    mov ch, 0
    mov cl, 2
    mov dh, 0
    int 0x13

    cli
    lgdt [gdt_desc]

    mov eax, cr0
    or al, 1
    mov cr0, eax

    jmp 0x08:0x100000

[bits 32]
extern kernel_main
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
    call kernel_main
    cli
    hlt

gdt_start:
    dq 0
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_desc:
    dw 23
    dd gdt_start

times 510-($-$$) db 0
dw 0xAA55
