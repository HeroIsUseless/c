#include "iostream"
#include "stack"
using namespace std;

int main(){
    int m, n, k;//栈最大容量，数的长度，数列的数量
    cin >> m >> n >> k;
    int ar[1000];
    std::stack<int> s;
    for(int i=0; i<k; i++){
        for(int j=0; i<n; j++){
            cin >> ar[i];
        }//输入完毕
        int now = 0;//代表每次检查弹出的数据
        int idx = 1;//代表初始队列，既然是顺序排列，那么就简化了
        bool res = true;//结果
        for(int i=0; i<n; i++){
            int t = ar[now];
            if(s.empty()||s.top()!=t){//说明没有在栈里
                //没有在栈里那么就直到压入栈为止
                //一定要在栈里才行
                while(idx<=n && t!=idx){
                    s.push(idx++);
                    if(s.size()>m){//大于堆栈长度，溢出
                        res = false;
                        break;
                    }
                }
                if(idx==n+1){//说明全压进去了但是还是
                    //没有成功，说明是被掩盖了
                    res = false;
                    break;
                }
                s.push(idx++);//那么现在就在了
            }
            s.pop();
            now++;
        }
        if(res) cout <<"YES"<<endl;
        else cout <<"NO"<<endl;
    }
    return 0;
}