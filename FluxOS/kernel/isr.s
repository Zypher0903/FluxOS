global isr_stub_table
extern isr_handler

%macro ISR_NOERR 1
global isr%1
isr%1:
    push 0
    push %1
    jmp common_stub
%endmacro

%macro ISR_ERR 1
global isr%1
isr%1:
    push %1
    jmp common_stub
%endmacro

ISR_NOERR 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
ISR_NOERR 32  ; PIT
ISR_NOERR 33  ; KB
ISR_NOERR 44  ; Mouse

common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call isr_handler
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    iret

isr_stub_table:
%assign i 0
%rep 32
    dd isr%+i
%assign i i+1
%endrep
    dd isr32
    dd isr33
    dd isr44
