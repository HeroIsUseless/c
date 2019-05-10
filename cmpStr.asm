str1 db "123456"
str1_len db $-str1
str2 db "123456"
str2_len db $-str2
yes db "match$"
no db "no match$"

 mov al, str1_len
    mov bl, str2_len
    cmp al, bl
    jnz print_no
    
    mov cl, str1_len
    lea si, str1
    lea di, str2
    flag:        
        mov al, [si]
        cmp al,byte ptr[di]
        jnz print_no
        inc si
        inc di
    loop flag
    
    print_yes:
        lea dx, yes
        jmp fun_end
    print_no:
        lea dx, no
    fun_end:
        mov ah, 9
        int 21h       
