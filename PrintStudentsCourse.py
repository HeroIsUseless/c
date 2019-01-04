n, k = map(int, input().split(" "))
m = {}
for i in range(k):
    course, count = map(int, input().split(" "))
    if count != 0:
        n = input().split(" ")
        for name in n:
            if name in m:
                m[name].append(course)
            else:
                m[name] = []
                m[name].append(course)

n = map(str, input().split(" "))
for name in n:
    print(name, end=" ")
    print(len(m[name]), end=" ")
    m[name].sort()
    mn = [str(x) for x in m[name]]
    print(" ".join(mn))
