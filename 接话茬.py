ps = input();cs = input();xs = input()
nextc=[];nextx=[]
nextc.append(-1);i=1; j=0
while i < len(cs):
    if ps[i]==ps[j] or j==-1:
        i+=1;j+=1
        nextc.append(j)
    else:
        j = nextc[j]
nextx.append(-1);i=1; j=0
while i < len(xs):
    if ps[i]==ps[j] or j==-1:
        i+=1;j+=1
        nextx.append(j)
    else:
        j = nextx[j]
i=0; j=0
if len(ps) > len(cs): i = len(ps)-len(cs)
while i < len(ps):
    if ps[i]==cs[j]:
        i+=1;j+=1;
    elif ps[i]!=cs[j] and j==0:
        i+=1
    else:#如果不相等时，判断
        j = nextc[j]
print(j,end=' ')
i=0; j=0
if len(ps) > len(xs): i = len(ps)-len(xs)
while i < len(ps):
    if ps[i]==xs[j]:
        i+=1;j+=1;
    elif ps[i]!=xs[j] and j==0:
        i+=1
    else:
        j = nextx[j]
print(j)








