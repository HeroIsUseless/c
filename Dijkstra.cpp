#include "iostream"
#include "vector"
#define INF 100000
using namespace std;
// 迪杰斯特拉算法
// 输入数据是二维矩阵，且全连通
// 输出是一个一维矩阵，里面放着点到点的最小值
// 采用遍历最小的方法
int p[5][5] = {
    {0, 4, INF, 2, INF},
    {4, 0, 4, 1, INF},
    {INF, 4, 0, 1, 3},
    {2, 1, 1, 0, 7},
    {INF, INF, 3, 7, 0}
};
bool f[5] = {1, 0, 0, 0, 0};
int r[5] = {0, INF, INF, INF, INF};
// 判断有没有空
bool isEmpty(){
    bool res = true;
    for(int i=0; i<5; i++){
        if(f[i] == false) res = false;
    }
    return res;
}
// 从未划分数组中获得距离A点最近的那一项
int GetMin(){
    int res = 0, dis = INF;
    for(int i=1; i<5; i++){
        if(f[i]==false && p[0][i]<=dis){
            res = i; dis = p[0][i];
        }
    }
    return res;
}
// 进行插入，挨个比较获得最小值
void Insert(int ci){
    r[ci] = p[0][ci];
    for(int i=1; i<5; i++){
        if(f[i] && r[ci]>r[i]+p[i][ci]){
            r[ci] = r[i]+p[i][ci];
        }
    }
    f[ci] = true;
}

int main(){
    while(!isEmpty()){
        int i = GetMin();
        Insert(i);
    }
    for(int i=0; i<5; i++) cout << r[i] << " ";
    return 0;
}