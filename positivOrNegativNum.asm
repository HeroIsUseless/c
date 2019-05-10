data segment
    M db 1, -2,3,-4,5,-6,7,8,9,10,11,12,13,14,15,16
    posi db 16 dup(0)
    posi_count db $
    negt db 16 dup(0)
    negt_count db $
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

    ; add your code here 
    mov bx, offset M
    mov cx, 16
    lea si, posi ; 正数的个数
    lea di, negt ; 负数的个数
    flag:
        mov al, [bx] 
        cmp al, 0
        jl lo
            mov [si], al
            inc si
            jmp end_if
        lo:
            mov [di], al
            inc di
        end_if:
        inc bx
        dec cx
    loop flag        
    mov al, posi_count
    sub si, ax
    mov posi_count, si
    sub di, negt_count
    mov negt_count, di    
         
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
