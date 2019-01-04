n, p = map(int, input().split(" "))
l = list(map(int, input().split(" ")))
l.sort()
cont=0
for i in reversed(l):
    for j in l:
        if(p*j > i):
            if cont < l.index(i)-l.index(j)+1:
                cont = l.index(i)-l.index(j)+1
print(cont)