ENG DB 'ABCDEFGSUNHIKGSUNJMNOP'
ENG_LEN DB $-ENG
SUN DB 'SUN'

; 从第一个字符开始，进行查找，匹配进入深层循环？
MOV CX, ENG_LEN
MOV BX, 0
LEA SI, ENG
FLAG:
    MOV AL, [SI]
    CMP AL, 'S'
    JE CMP_U
    JMP NO
    CMP_U:
        INC SI
        MOV AL, [SI]
        CMP AL, 'U'
        JE CMP_N
    JMP NO
    CMP_N:
        INC SI
        MOV AL, [SI]
        CMP AL, 'N'
        JE YES
    JMP NO
    YES: INC BX
    NO: INC SI
LOOP FLAG