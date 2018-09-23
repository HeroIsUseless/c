#include <stdio.h>
//最长对称子串
//用从中心向外扩散的方法，单核溜一遍双核溜一遍
char c[2000]={0};
int ln=0;//字符串长度
int isHuiWen(int ci)
{
    int i, j;
    int n;
    int m = 1;
    //单核
    i=ci; j=ci;
    n = 1;
    while(c[i] == c[j])
    {
        n+=2;
        i--; j++;

        if(i < 0 || j > ln-1)
        {
            break;
        }
    }
    n-=2;//用于弥补第一次的两个恒定误差
    if(m < n) m = n;
    //双核
    i=ci; j=ci+1;
    n = 0;
    while(c[i] == c[j])
    {
        n+=2;
        i--; j++;
        if(i < 0 || j > ln-1) break;
    }
    if(m < n) m = n;
    return m;
}
int main()
{
    int i,j;
    int m = 1;//最大长度
    int t;
    gets(c);
    while(c[ln] != 0)
    {
        ln++;
    }
    for(i=0; i<ln-1; i++)
    {
        t = isHuiWen(i);
        if(m < t)
            m = t;
    }
    printf("%d", m);
    return 0;
}
