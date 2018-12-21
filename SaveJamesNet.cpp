
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<queue>
#include<algorithm>
#include<map>
#include<vector>
#include<cstring>
#include<math.h>
using namespace std;
 
int N,D;
struct node
{
    double x;
    double y;
}a[105];
int flag[105]={0};//这个flag是什么意思？全都初始化为0
double dist(node a,node b)//仅仅是求两个节点之间的距离
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int flg=0;//而且这个变量只有这一个全局变量
void dfs(int x)
{
    flag[x]=1;//这个flag为1了就，表明这个节点能跳
    if(flg)//如果这个flg成立了，倒返回了？
        return;
    if(a[x].x+D>=50 || a[x].y+D>=50 ||a[x].x-D<=-50 ||a[x].y-D<=-50 )
    {//表明这个节点能跳到对岸
        cout<<"Yes";//就可以输出了？
        flg=1;
        return;
    }
    for(int i=1;i<=N;i++)//这里又进行鳄鱼节点的循环
    {
        if(flag[i]==0 && dist(a[i],a[x])<=D)//如果是这样
        {//就进行递归，其实用递归是最正确的，只有递归才能很容易的
        //进行分支操作
            dfs(i);//这个是一个递归
        }
    }
}
//判断他能否逃脱，找特解所以用深搜。
//因此做法就是把节点都放进来之后，一个从头到尾的递归来做
//就这样
int main()
{
    cin>>N>>D;//鳄鱼数量和詹姆斯能跳的最大距离
    a[0].x=0;
    a[0].y=0;
    for(int i=1;i<=N;i++)
    {
        cin>>a[i].x>>a[i].y;
    }
 //吸收完所有坐标
    for(int i=1;i<=N;i++)//对以下每个鳄鱼节点
    {//用函数dist去运行一下
        if( dist(a[i],a[0]) <= 15+D && flag[i]==0 )
        {//距离比较小，还有一个flag为0，代表没有处理这个有用节点
        //就运行dfs函数
            dfs(i);
        }
    }
    if(!flg)//看来是进行判断的
        cout<<"No";
}
