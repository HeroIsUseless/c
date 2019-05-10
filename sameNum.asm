arr1 db 1,2,3,4,5,6,7,8,9 ; 保证没有重复
arr2 db 2,4,6,8,0 ; 如果有重复怎么办？
; 两个的重复是不一样处理的，外层重复基本无解
res db 20 dup(0)

lea si, arr1 ; 初始化
lea bx, res

lp1:
    lea di, arr2 ; 内层初始化，对di进行遍历
    lp2:
        cmp [si],[di]
        je if ; 相等则填充
        jmp else
        if:
            mov [bx],[si]
            inc bx
            inc si
            jmp endif
        else:
            inc si
            inc di
        endif:
    lea dx, res
    cmp di, dx
    jb lp2
lea dx, arr2
cmp si, dx
jb lp1
