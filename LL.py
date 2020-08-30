# -*- coding:utf-8 -*-
grammar = {
    "S": ["XYX"],
    "X": ["0X", ""],
    "Y": ["1Y", ""]
}

new_grammar = {}

def get_empty_grammar():
    eg = []; ng = []
    for key in grammar:
        if "" in grammar[key]: eg.append(key)
        else: ng.append(key)
    return eg, ng
# 在长度为m的限制下，需要删除的
def combine(key, s, l, a, m):  # 递归解决，a为l的序号序列
    if len(a) == m:
        ts = ""
        for i in range(0, len(s)):
            if i in a: pass
            else: ts = ts + s[i]
        if key in new_grammar: new_grammar[key].append(ts)
        else: new_grammar[key] = [ts]
    else:
        if len(a) == 0: k = 0
        else: k = a[-1] + 1
        for i in range(k, len(l)):
            a.append(i)
            combine(key, s, l, a, m)
            a.pop()

# 从0到最大，产生这些表达式
def grammar_append(key, s, l): # l为其中空产生符号的序号
    for m in range(0, len(l)+1):
        combine(key, s, l, [], m)
    new_grammar[key] = list(set(new_grammar[key]))
    
if __name__=='__main__':
    eg, ng = get_empty_grammar()
    for key in ng:
        for s in grammar[key]:
            l = []
            for i, c in enumerate(s):
                if c in eg: l.append(i)
            grammar_append(key, s, l)
    for key in eg:
        for s in grammar[key]:
            ts = ""
            for c in s:
                if c == key: pass
                else: ts = ts + c
            if ts != "":
                if key in new_grammar: new_grammar[key].append(ts)
                else: new_grammar[key] = [ts]
    print(new_grammar)


