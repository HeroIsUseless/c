#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n ,m; // 1<n<20, 0<m<100
    while(true){
        cin >> n >> m;
        if(n==0 && m==0) break; // 如果遇到终止条件，退出
        int *arr = new int[n*n](); // 邻接表
        int t1, t2, t3;
        for(int i=0; i<m; i++){
            cin >> t1 >> t2 >> t3; // 进行接收
            arr[t1*n+t2] = t3;
            arr[t2*n+t1] = t3; // 填入邻接表
        }
        // 下面开始找出最小生成树
        int *V = new int[n](); // 表示已经纳入的点
        V[0] = true; // 挑选一个点进入V中
        // 下面挑选最小距离的未纳入点进行纳入
        int clock = 0;
        int res = 0; // 最后的总代价
        while(clock < 1000){
            clock++;
            int index=0, min=10000; // 记录最小值
            for(int i=0; i<n; i++){ // 对于每一个未纳入点
                if(V[i] == false){ // 的确没有纳入，求得它与纳入节点的最小值
                
                    int t_min=10000;
                    for(int j=0; j<n; j++){ // 找到这个节点距离纳入点的最小值
                        if(V[j]==true && arr[i*n+j]!=0){ // 纳入点并且不是无穷
                            if(arr[i*n+j]<t_min){ // 如果这段距离比较小的话
                                t_min = arr[i*n+j]; // 记录下这个最小值
                            }
                        }
                    }

                    if(t_min < min){ // 如果这个点的最小值比min小的话
                        min  = t_min;// 如果没有点满足，那么index恒为0，也没有错
                        index=i;
                    }
                }
            }
            V[index] = true; 
            if(min != 10000)
                res += min;
        }
        // 最后的检查部分
        bool flag=true;
        for(int i=0; i<n; i++){
            flag &= V[i];
        }
        // 最后输出部分
        if(flag) cout<<res<<endl; // 如果flag为true代表所有节点可以了
        else cout <<"error"<<endl;
    }
    return 0;
}
