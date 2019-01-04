import re
#输出被多条微博提到的话题，所以是存话题，用map
#里面的int村的是提到的次数
sr = r'!@#$%^&*()+-={}[];:,.<>?/'
n = int(input())
topic = {}
p = r"#.+#"#什么正则表达式
pattern = re.compile(p)
for i in range(n):
    s = input()
    word = pattern.findall(s)[0].split("# #")#格式化
    for j in range(len(word)):
        for k in sr:
            word[j] = word[j].replace(k,'')#去掉所有符号
        word[j] = word[j].lower()#转换成小写
        word[j] = word[j].capitalize()#转换成首字母大写
    word = list(set(word))#去重
    for w in word:
        if w in topic:
            topic[w] = topic[w]+1
        else:
            topic[w] = 1
#第一行输出被最多条微博提到的话题，因此遍历找
# 第二行输出其被提到的微博条数。打印值
# 如果这样的话题不唯一，则输出按字母序最小的话题，进行比较和加1
# 并在第三行输出And k more ...，
# 其中k是另外几条热门话题的条数。输入保证至少存在一条话题。
s = ''
max = 0
count = 1
for key,val in topic.items():
    if max < val:
        max = val
        s = key
        cout = 1
    elif max == val:
        if key < s:
            s = key
        cout = cout + 1
print(s)
print(max)
if cout != 1:
    print("And %d more..." % (count))
