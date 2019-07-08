class People:
    win = 0
    equal = 0
    lose = 0
    B = 0
    C = 0
    J = 0


lA = People()
lB = People()

def theBiggestOne(people):
    dic = {}
    dic['B'] = people.B
    dic['C'] = people.C
    dic['J'] = people.J
    sorted(dic.items(), key=lambda x:x[0], reverse = False)
    sorted(dic.items(), key=lambda x:x[1], reverse = True)
    return list(dic.items())[0][0]


def Fight(A, B):
    if A == "B":
        if B == "B":
            lA.equal += 1
            lB.equal += 1
        if B == "J":
            lA.lose += 1
            lB.win += 1
            lB.J += 1
        if B == "C":
            lA.win += 1
            lB.lose += 1
            lA.B += 1
    if A == "J":
        if B == "B":
            lA.win += 1
            lB.lose += 1
            lA.J += 1
        if B == "J":
            lA.equal += 1
            lB.equal += 1
        if B == "C":
            lA.lose += 1
            lB.win += 1
            lB.C += 1
    if A == "C":
        if B == "B":
            lA.lose += 1
            lB.win += 1
            lB.B += 1
        if B == "J":
            lA.win += 1
            lB.lose += 1
            lA.C += 1
        if B == "C":
            lA.equal += 1
            lB.equal += 1

N = int(input())
while N > 0:
    a, b = map(str, input().split(" "))
    Fight(a, b)
    N -= 1
print("%d %d %d" % (lA.win, lA.equal, lA.lose))
print("%d %d %d" % (lB.win, lB.equal, lB.lose))
print("%s %s\n" % (theBiggestOne(lA), theBiggestOne(lB)))