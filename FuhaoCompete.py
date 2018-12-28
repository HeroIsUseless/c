if __name__ == "__main__":
    l = list(input())
    s = []
    while l != ['.']:
        #下面是把左面的部分压入栈
        while '(' in l:
            s.append('(')
            l.remove('(')
        while '[' in l:
            s.append('[')
            l.remove('[')
        while '{' in l:
            s.append('{')
            l.remove('{')
        while '/' in l and '*' in l:
            s.append('/'); s.append('*')
            l.remove('/'); s.append('*')
        #下面是把右面的部分作为匹配
        while ')' in l:
            if '(' in s:
                s.remove('(')
                l.remove(')')
            else:#这里是代表没有左括号
                print('NO')
                print('(-?')
        while ']' in l:
            if '[' in s:
                s.remove('[')
                l.remove(']')
            else:
                print('NO')
                print('[-?')
        while '}' in l:
            if '{' in s:
                s.remove('{')
                l.remove('}')
            else:
                print('NO')
                print('{-?')
        l = list(input())
    #没有右括号只能最后处理