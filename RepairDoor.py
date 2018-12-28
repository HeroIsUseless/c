#问题相当于带权路径长度，即哈夫曼树
n = int(input())
l = list(map(int, input().split()))
l.sort(reverse = True)
res = 0
while len(l) > 1:
    a = l.pop()
    b = l.pop()
    res = res + a+b
    l.insert(0,a+b)
    l.sort(reverse = True)
print(res)
