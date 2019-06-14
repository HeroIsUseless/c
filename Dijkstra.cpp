#include "iostream"
#include "vector"
#define INF 100000
using namespace std;
// 迪杰斯特拉算法
// 输入数据是二维矩阵，且全连通
// 输出是一个一维矩阵，里面放着点到点的最小值
// 采用遍历最小的方法
int p[9][9] = {
    {0,3,INF,3,INF,INF,INF,INF,INF}, // 1
    {3,0,3,INF,2,INF,INF,INF,INF}, // 2
    {INF,3,0,INF,INF,4,INF,INF,INF}, // 3
    {1,INF,INF,0,3,INF,3,INF,INF}, // 4
    {INF,2,INF,3,0,3,INF,3,INF}, // 5
    {INF,INF,4,INF,3,0,INF,INF,5}, // 6
    {INF,INF,INF,3,INF,INF,0,4,INF}, // 7
    {INF,INF,INF,INF,5,INF,4,0,2}, // 8
    {INF,INF,INF,INF,INF,6,INF,2,0}, // 9
};

bool f[9] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
int r[9] = {0, INF, INF, INF, INF, INF, INF, INF, INF};
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