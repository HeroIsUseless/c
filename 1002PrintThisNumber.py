def TransNum(c):
    if c == '0': return 'ling'
    if c == '1': return 'yi'
    if c == '2': return 'er'
    if c == '3': return 'san'
    if c == '4': return 'si'
    if c == '5': return 'wu'
    if c == '6': return 'liu'
    if c == '7': return 'qi'
    if c == '8': return 'ba'
    if c == '9': return 'jiu'

s = input()
a = 0
for c in s:
    a = a+int(c)
s = str(a)
print(" ".join(TransNum(i) for i in s))

    