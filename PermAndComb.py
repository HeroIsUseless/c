import re

def Perm(l, b, e):#列表，开始位置，长度
    if b == e:
        print(l)
        return
    for i in range(b, len(l)):
        l[b], l[i] = l[i], l[b]
        Perm(l, b+1, e)
        l[b], l[i] = l[i], l[b]

def PermCount(l):
    pass

if __name__ == "__main__":
    d = {1:'a', 2:'b', 3:'c'}
    l = d.items()
    print(l)