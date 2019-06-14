#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;
// 状态 
struct status
{
    int shipSite=0;  //0 stand left, 1 stand right ,aim is right
    int missionary[2];
    int savage[2];
    int step;
};
int shipMax; // 船的最大载人数
vector<status> close; // 最后的close结果表
bool operator == (const status& obj1,const status& obj2) // 重载相等，讲究
{
    return  
        obj1.shipSite==obj2.shipSite&&
        obj1.missionary[0]==obj2.missionary[0]&&
        obj1.missionary[1]==obj2.missionary[1]&&
        obj1.savage[0]==obj2.savage[0]&&
        obj1.savage[1]==obj2.savage[1];
}
bool numberCheck(int &missionary,int &savage) // 状态检查，还懂
{
    if( savage>missionary &&missionary!=0 )
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool move(int missionary,int savage,status &nowStatus) // 这个应该是移动函数了，本质上还是遍历的问题
{ // 传教士，野人数量和现在状态的引用
    nowStatus.missionary[nowStatus.shipSite]-=missionary; // 嗯，真的不好懂了，就是船，岸上，是哪一边
    nowStatus.savage[nowStatus.shipSite]-=savage; // 但他为什么减呢？
    nowStatus.shipSite=1-nowStatus.shipSite; // 因为下面的要加了，状态转移
    nowStatus.missionary[nowStatus.shipSite]+=missionary;
    nowStatus.savage[nowStatus.shipSite]+=savage;
    nowStatus.step++; // 步数增加
    vector<status>::iterator iter; // 然后一个遍历，看看有没有
    iter=find(close.begin(),close.end(),nowStatus);
 
    bool result1=numberCheck(missionary,savage)&&
                numberCheck(nowStatus.missionary[0],nowStatus.savage[0])&&
                numberCheck(nowStatus.missionary[1],nowStatus.savage[1]); // 这个是状态检查
    bool result2=false; // 第二个是判断有没有的
    if(iter==close.end())
        result2=true; // 嗯~
    else if(iter!=close.end()&&iter->step>nowStatus.step) // 或者这样也行
    {
        iter->step=nowStatus.step;
        result2=true;
    }
    
    
    return result1&&result2;
}
 
int PruductionSystem(status nowStatus,vector<status> &stepv) // 直接一个产生式系统，嗯~
{// 大概率是一个递归~
    if(nowStatus.missionary[0]==0&&nowStatus.savage[0]==0) return nowStatus.step; // 现在是运完了，返回
    close.push_back(nowStatus); // 不然close表就push进去，不管三七二十一
    int minstep=99999; // 这个是什么意思？
    vector<status> bufferInsert; // 缓冲插入什么鬼？
    for(int k = 1; k <= shipMax; k++) // 从1开始，进行运输吗？
    {
        int shipSavage,shipMissionary; // 船上的传教士和野人
        for(shipSavage = 0; shipSavage <=k,shipSavage<=nowStatus.savage[nowStatus.shipSite]; shipSavage++)
        {// 船上的野人从0到k的增加
            shipMissionary=min(k-shipSavage,nowStatus.missionary[nowStatus.shipSite]);// 传教士取最小的那一个
            if(shipSavage==0&&shipMissionary==0) continue; // 如果都是0，则继续了
            status nextStatus=nowStatus; // 嗯，是这个    
            int reStep=minstep; // 作为最小步数
            vector<status> nextStepv; // 创建了多少个啊？
            if(move(shipMissionary,shipSavage,nextStatus)) //  如果move，这个是怎么回事？
            {
                nextStepv.push_back(nextStatus);
                reStep=PruductionSystem(nextStatus,nextStepv); // 这里是一个递归
            }
            if(reStep<minstep)
            {
                minstep=reStep;
                bufferInsert.clear();
                bufferInsert.insert(bufferInsert.begin(),nextStepv.begin(),nextStepv.end());
            }
        }
    }
    stepv.insert(stepv.end(),bufferInsert.begin(),bufferInsert.end());
    return minstep;
}
int main(int argc, char const *argv[]) // 主函数，好长啊
{
    int missionary,savage; // 传教士与野人的数量
    //cout<<"input missionary and savage number,ship number"<<endl;
    // cin>>missionary>>ship;
    // savage=missionary;
    missionary=3;savage=3;shipMax=2; // 3，3，2标准配置
    // if(2*missionary<=shipMax||shipMax<2)
    if( shipMax<2) cout<<"This input illegal"<<endl; 
    else
    {
        status start; // 开始状态
        start.shipSite=0;
        start.missionary[0]=missionary; // 0，1表示左右河岸
        start.missionary[1]=0;
        start.savage[0]=savage;
        start.savage[1]=0;
        start.step=0; // 步数，对，挺好懂
        vector<status> resultv; // 状态结果数组，是对状态的集合
        resultv.push_back(start); // 对，压进去
        int resStep=PruductionSystem(start,resultv); // 返回数量值，输入开始状态和结果数组
        int i=0; // 下面开始输出了，没有什么关系了
        for(vector<status>::iterator iter=resultv.begin();iter!=resultv.end();iter++)
        {
            cout<<"Step"<<i++<<"\t"<<" lm:"<<iter->missionary[0]<<" ls"<<iter->savage[0]
                              <<" rm:"<<iter->missionary[1]<<" rs"<<iter->savage[1]<<endl;
        }
        cout<<"final minstep"<<resStep<<endl;
    }
    return 0;
}