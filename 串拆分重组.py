import random

s1 = []
n = random.randint(0,1000)
while n >=0 :
    s1.append(chr(random.randint(97,122)))
    n -= 1
s1 = "".join(s1)
print(s1)
s2 = []
n = random.randint(1,10)
s2.append(chr(random.randint(97,122)))
s2.append(' ')
while n >=0 :
    s2.append(chr(random.randint(97,122)))
    n -= 1
s2 = "".join(s2)
print(s2)
#s1 = input()
#s2 = input()#那个字符串从2开始
p = s2[0]

ls = []
pos=0
for i,c in enumerate(s1):
    if c == p:
        if i == 0:
            ls.append('')
            if len(s1) >=1: pos = 1
        elif i == len(s1)-1:
            ls.append(s1[pos:i])
            ls.append('')
        else:
            ls.append(s1[pos:i])
            pos = i+1
    elif c!=p and i==len(s1)-1:
        ls.append(s1[pos:i+1])
print('[',end='')
for i in ls:
    if i is ls[-1]:
        print('\"',end='')
        print(i,end='')
        print('\"',end='')
    else:
        print('\"',end='')
        print(i,end='')
        print('\", ',end='')
print(']')

for i in ls:
    if i is ls[-1]:
        print(i)
    else:
        print(i,end='')
        print(s2[2:],end='')




