; multi-segment executable file template.

data segment
    str db "1234abcd1234ab56789c0d$"
    str_len = $-str
    num db "0123456789"
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
    mov cl, str_len
    lea si, str

    tag1: ; 外层循环
        mov al, [si] 
        mov ch, 10 ; 内层循环设置部分
        lea di, num
        tag2: 
            mov bl, [di]
            cmp al, bl
            jz setZero
            jmp notSetZero
            setZero: mov [di], 0
            notSetZero:
                inc di
                dec ch
        jnz tag2
        inc si
        dec cl
    jnz tag1
    ; 下面进行判断
    lea si, num
    mov cx, 10
    mov bx, 0
    tag:
        or bx, [si]
        inc si
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
