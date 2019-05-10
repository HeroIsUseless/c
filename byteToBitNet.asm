data segment
    res db 4 dup(0)
ends

mov ax, 1234h
mov cl, 4
mov ch, 4
mov si, 0
tag:
    mov dl, al
    and dl, 0fh
    mov byte ptr res[si], dl
    inc si
    shr ax, cl
    dec ch
jnz tag
mov dl, res[0]
mov cl, res[1]
mov bl, res[2]
mov al, res[3]

