//课本上的也不是二叉树，只是一个数组，现在关心的是如何取得它的编码和取得树的最小带权路径长度
//获得某一个叶子节点的编码只是向上回溯，不管是树还是数组，都这样，但是用0，1表示，
//不不最小路径长度就是权值乘以len，感觉可以了
//要在回溯的过程中进行叠加，然后在循环节点叠加，或者用另一种方式，用最小堆的方式，首先
//进行排序，然后进行pop就可以了
//获得树的最小带权路径长度是所有路径长度之和
//对于这道题来说，用sort好了

//最小堆实际上是一棵元素逐层增大的完全二叉树，注意是完全二叉树，因为一定可以组成完全二叉树
//因此可以层序存入数组，它的一半是
//根节点为元素最小值，实际上可以用数组储存，
//确切的说是用vector进行储存
//每一个新结点插入时，将当前index（注意不包含新加入结点）的父节点（index/2），
//但根节点必须为1才行
//将0位置的元素设置为一个信号点，设为0算了，当循环的时候就会用这个进行判断截至
//与插入元素的元素值进行大小比较，
//从后往前依次循环比较，
//若当前结点比其父节点小，则交换位置，直到根节点位置。
//这里有个小技巧是在vector的第一个元素设置哨兵（元素值为min），
//方便后期进行循环。

#include "iostream"
#include "algorithm"
#include "vector"
#include "string"
#include "set"
using namespace std;
//加上后面两个，删除掉，剩下最后一个就可以了
int GetHumMinPath(vector<int> cf){
    int res = 0;
    while(cf.size() != 1){
        int a = *cf.begin(); cf.erase(cf.begin());
        int b = *cf.begin(); cf.erase(cf.begin());
        res += a+b;
    }
    return res;
}
//首先判断是否为最小的带权路径长度 //然后判断前缀码是否包含其他叶节点的编码
bool IsHufmCode(vector<string> cc, vector<int> cf, vector<string> ca){//字母，权值，编码
    bool result = true;
    //首先判断树的最小带权路径长度
    vector<int> f(cf);
    int res = 0;
    sort(cf.begin(), cf.end(), greater<int>());
    while(cf.size() > 1){
        int a = cf.back(); cf.pop_back();
        int b = cf.back(); cf.pop_back();
        res += a+b;
        cf.push_back(a+b);
        sort(cf.begin(), cf.end(), greater<int>());
    }
    int pRes = 0;
    for(int i=0; i<f.size(); i++){
        pRes += f[i]*ca[i].size();
    }
    if(res != pRes) result = false;
    //下面判断是否有前缀重合的现象产生
    for(auto iter=ca.begin(); iter!=ca.end(); iter++){
        for(auto iter2=ca.begin(); iter2!=ca.end(); iter2++){
            if(iter != iter2)
                if((*iter2).find(*iter) == 0){
                    result = false;
            }
        }
    }
    return result;
}
//先输入字母和权值
//然后依次输入字母和对应的哈夫曼编码
//判断此代码是不是最优代码，然后输出答案
int main(){
    int n; cin>> n;
    std::vector<string> c; 
    std::vector<int> f; //权值
    for(int i=0; i<n; i++) {
        string tstr; int tf;
        cin>> tstr >> tf;
        c.push_back(tstr); f.push_back(tf);
    }
    int stuN; cin>> stuN;
    for(int i=0; i<stuN; i++){
        std::vector<string> stuC, stuA;
        for(int j=0; j<n; j++) {
            string tstr, ta;
            cin>> tstr >> ta;
            stuC.push_back(tstr); stuA.push_back(ta);
        }       
        bool res = IsHufmCode(stuC, f, stuA);
        if(res) cout<< "Yes" <<endl;
        else    cout<< "No"  <<endl;
    }
    return 0;
}