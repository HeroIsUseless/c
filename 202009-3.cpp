#include <iostream>

using namespace std;
// 可能是电路通路，AOV类型
// 算了不做了，根本就是阅读题
int main(){
    int Q; // Q个问题
    cin >> Q;
    for (int i = 0; i < Q; i++){
        int M, // 电路的输入
            N; // 器件的数量
        cin >> M >> N;
        for (int j = 0; j < N; j++){
            int FUNC, // 具体的逻辑功能
                k;    // 输入的数量
            cin >> FUNC >> k;
            int *L = new int[k];
            // 实际上就是链表的数组表达
            for (int z = 0; z < k; z++){
                int l;
                cin >> l;
                L[z] = l;
            }
            int S;
            cin >> S;
            for (int j = 0; j < S; j++){
                int M;
                cin >> M;
                int *I = new int[M]; // 一组输入
                for (k = 0; k < M; k++){
                    int t;
                    cin >> t;
                    I[k] = t;
                }
            }
        }
    }
        return 0;
}