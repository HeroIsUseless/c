a = int(input())
n = 0
while a != 1:
    n = n+1
    if a%2 == 0:
        a = a/2
    else:
        a = (3*a+1)/2
print(n)