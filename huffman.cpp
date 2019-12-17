#include <iostream>
#include <vector>
using namespace std;

struct HuffTree{
    int length; // 编码长度
    int weight; // 权重
    int parent;
    int left;   // 左孩子
    int right;  // 右孩子
    HuffTree():length(0),weight(0),parent(-1),left(-1),right(-1){}
};

void init_HuffTree(HuffTree *huffTree){
    int lchild,rchild;
    double minL,minR;
    int n = 0;
    for(int i=256;i<2*256-1;i++){ // 对于之后的每一个中间节点
        minL = minR = 10000;
        lchild = rchild = -1;
        for(int j=0;j<i;j++){ // 在之前寻找最小的两个节点
            if(huffTree[j].parent == -1 && huffTree[j].weight!=0){ // 如果它无父节点而且权值经过赋值的
                if(huffTree[j].weight < minL){ // 它会捕获到根节点
                    minR = minL; // 左右最小交换一下
                    minL = huffTree[j].weight; // 最小值赋值
                    rchild = lchild; // 左右最小节点交换一下
                    lchild = j; // 最小节点赋值
                }else if(huffTree[j].weight < minR){ // 如果它比右最小小的话
                    minR = huffTree[j].weight; // 右最小转化一下
                    rchild = j;
                }
            }
        }
        if(minR == 10000) break; // 说明只有一个空余节点，那就是根节点，返回即可
        huffTree[lchild].parent = huffTree[rchild].parent = i; // 然后赋予父节点
        huffTree[i].weight = minL + minR; // 然后赋予权重
        huffTree[i].left = lchild; // 然后赋予左右孩子
        huffTree[i].right = rchild;
    }    
    // 然后开始获取长度
    for(int i=0; i<256; i++){
        if(huffTree[i].weight == 0) continue;
        int n=0, j=i;
        while(huffTree[j].parent != -1){
            n++;
            j = huffTree[j].parent;
        }
        huffTree[i].length = n;
    }
}

int main(){
    int n, m;
    while(true) {
        cin >> n >> m; // 获取m，n的值
        if(n==0 && m==0) break;
        int t;
        int *num = new int[n*m](); // 接收数据的数组
        int  num_count[256] = {0}; // 数字计数的数组
        for(int i=0; i<n; i++) {   // n为行
            for(int j=0; j<m; j++){// m为列
                cin >> t;
                num[i*m + j] = t;
                num_count[t]++;
            }
        }
        HuffTree huffTree[2*256 - 1]; // 不是采用链式存储，而是以数组方式存储，每个索引是像素值，它的值是编码长度
        for(int i=0; i<256; i++) huffTree[i].weight = num_count[i]; // 赋予权重
        init_HuffTree(huffTree); // 构建哈夫曼树
        int res = 0;
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                res += huffTree[num[i*m+j]].length; // 获取编码的总长度
        cout <<(float)(n*m*8)/res<< endl; // 在这里输出
        delete[] num; // 删除这个数组
    }
    return 0;
}
