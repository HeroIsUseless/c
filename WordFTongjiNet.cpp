#include <stdio.h> 
#include<iostream> 
#include<string> 
#include<algorithm> 
#include<vector> 
using namespace std; 
struct node{ 
    string s; 
    int n; 
}; 
vector<node > q; 
bool cmp(node s1,node s2) { 
    if(s1.n ==s2.n ) 
        return s1.s <s2.s ; 
    else 
        return s1.n >s2.n;  
} 
int main() { 
    char n; 
    string s; 
    while(scanf("%c",&n)) { //每次读取一个字符，就是这样
        if(n>='A'&&n<='Z'||n>='a'&&n<='z'||
            n>='0'&&n<='9'||n=='_') { 
            if(n>='A'&&n<='Z') 
                n=n+32;
            s += n; //嗯，这里是组建单词的
        } else if(n=='#'||s.size()>0) { //第二种代表是空格
            string ss; 
            if(s.size()>0) { //这样的话压入数组中
                int g=0; 
                for(int i=0;i<15&&i<s.size();i++) { 
                    ss+=s[i]; 
                } //进行裁剪
                for(int i=0;i<q.size();i++) { 
                    if(q[i].s==ss) 
                        q[i].n++; g=1; 
                } //获得长度
                if(g==0) { //g是一个标志
                    node cc ; 
                    cc.n = 1; 
                    cc.s = ss; 
                    q.push_back(cc); //添加进去ok
                } 
            } 
            s.clear(); //清除一下比较好
            if(n=='#') { //判断结束ok
                break; 
            } 
        } 
    } 
    printf("%d\n",q.size()); 
    sort(q.begin(),q.end(),cmp); 
    for(int i=0;i<q.size()/10;i++) 
        printf("%d:",q[i].n),
        cout<<q[i].s,printf("\n"); 
}