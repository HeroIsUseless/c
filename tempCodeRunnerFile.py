#从abc到abc
#a进去3
#b进去3
#c进去2 c
#b进去2 bc
#a进去2 abc
#其实正反都一样的
#就是s2有没有出现错误就行
if __name__ == "__main__":
    s1 = list(input())
    s2 = list(input())
    s3 = []
    #s2.reverse()
    res = ''
    while len(s2) > 0:#当s2大于0的时候，这件事就没完
        a = s2.pop()
        if a in s1:#如果在s1队列中
            b=s1.pop()
            while a != b:#如果不是就添加到s3中
                s3.append(b)
                res = res + "1->3\n"
                b = s1.pop()
            else:#直到出现了这个值，添加进去
                res = res + "1->2\n"
        else:#那么就在s3队列中，而且一定是在最开始的
            b = s3.pop()
            if a == b:
                res = res + "3->2\n"
            else:#就出错了
                break
    if len(s1) == 0:
        print(res)
    else:
        print('Are you kidding me?')

