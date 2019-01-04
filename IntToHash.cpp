#include "iostream"
#include "stdlib.h"
#include "cstring"
using namespace std;
//给定一系列整型关键字和素数P
//用线性探测法解决冲突。输出他们的位置
int main() {
    int n,p;
    cin >> n >> p;
    int a[10001] = {0};
    int flag[10001] = {0};
    for(int i=0; i<n; i++){
        int t; cin >> t;
        int m = t%p;
        for(int j=0; j<p; j++){
            if(flag[m] == 0){
                a[m] = t;
                flag[m] = 1;
                cout << m;
                break;
            }else{
                if(a[m] == t){//如果重复了
                    cout << m;
                    break;
                }else{
                    m = (t+j)%p;
                }
            }
        }
        if(i != n-1) cout << " ";
    }
    return 0;
}
