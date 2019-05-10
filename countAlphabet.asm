; multi-segment executable file template.

data segment
    str db "1234abcd1234abcd$"
    str_len = $-str
    pkey db "press any key...$"
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
;-----------------------------------------
    mov cx, str_len
    lea si, str
    mov bx, 0
    tag:
        mov al, [si]
        cmp al, '0'
        jb isAlphabet
        cmp al, '9'
        ja isAlphabet
        jmp noAlphabet
        isAlphabet: inc bx
        noAlphabet: inc si
    loop tag



;-----------------------------------------
    
            
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
