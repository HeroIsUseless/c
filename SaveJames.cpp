
#include<iostream>
#include "cmath"
using namespace std;
typedef struct Point{
    int x, y;
}Point;
Point p[1000];
bool IsJumped[1000] = {false};
int n, d;
bool IsSaved = false;
double Distance(Point a, Point b){
    return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}
bool JumpOut(Point cp){
    if(cp.x-d<-50 || cp.x+d>50 || cp.y-d<-50 || cp.y+d>50)
        return true;
    else
        return false;
}
void Jump(Point cp){//跳到b这个点上
    if(JumpOut(cp)){
        IsSaved = true;
    }
    for(int i=1; i<=n; i++){
        if(Distance(cp, p[i]) < d){
            if(IsJumped[i] == false){
                IsJumped[i] = true;
                Jump(p[i]);
            }
        }
    }
}
//判断他能否逃脱，找特解所以用深搜。
//因此做法就是把节点都放进来之后，一个从头到尾的递归来做
//判断的话，首先，跳过的节点就不应该再跳进去，否则可能会陷入循环
//如何判断跳到的这个点可以跳出来，用专门的函数来做就好了，如果能跳出来了，
//终止一切动作，直接回来
int main()
{
    cin >> n >> d;//鳄鱼数量和詹姆斯能跳的最大距离
    for(int i=1;i<=n;i++)
    {
        cin>>p[i].x>>p[i].y;
    }
    p[0].x=0; p[0].y=0;
    IsJumped[0] = true;
    for(int i=1;i<=n;i++)
    {
        if(Distance(p[0], p[i]) < d){
            IsJumped[i] = true;
            Jump(p[i]);
        }
    }
    if(IsSaved) cout << "Yes" <<endl;
    else cout << "No" <<endl;
}
