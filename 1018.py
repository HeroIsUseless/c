def Fight(A, B):
    if A == "B": 
        if B == "B":
            return 0
        if B == "J":
            return "yi"
        if B == "C":
            return "jia"
    if A == "J": 
        if B == "B":
            return "jia"
        if B == "J":
            return 0
        if B == "C":
            return "yi"
    if A == "C": 
        if B == "B":
            return "yi"
        if B == "J":
            return "jia"
        if B == "C":
            return 0


N = int(input())
win_jia = {'C':0, 'J':0, 'B':0}
win_yi = {'C':0, 'J':0, 'B':0}
for i in range(0, N):
    a, b = map(str, input().split(" "))
    win_t = Fight(a, b)
    if win_t == "jia":
        win_jia[a] += 1
    elif win_t == "yi":
        win_yi[b] += 1
    else:
        pass
        
win = win_jia['C']+win_jia['J']+win_jia['B']
los = win_yi['C']+win_yi['J']+win_yi['B']
equ = N-win-los
print("%d %d %d" % (win, los, equ))
print("%d %d %d" % (los, win, equ))
ges_jia = 'B'
if win_jia['B'] < win_jia['C']:
    ges_jia = 'C'
    if win_jia['C'] < win_jia['J']:
        ges_jia = 'J'
elif win_jia['B'] < win_jia['J']:
    ges_jia = 'J'

ges_yi = 'B'
if win_yi['B'] < win_yi['C']:
    ges_yi = 'C'
    if win_yi['C'] < win_yi['J']:
        ges_yi = 'J'
elif win_yi['B'] < win_yi['J']:
    ges_yi = 'J'

print("%s %s" % (ges_jia, ges_yi))