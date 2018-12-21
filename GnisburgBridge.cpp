#include "iostream"
using namespace std;
//判断欧拉回路
//1.所有点均连通
//2.所有点的度数均为偶数
//建立一个数组，不存在为0或者为奇数的，就这样
int main(){
    int n, m; cin >> n >> m;
    int point[1000] = {0};
    for(int i=0; i<m; i++){
        int p1, p2; cin >> p1 >> p2;
        point[p1]++; point[p2]++;
    }
    int res = true;
    for(int i=1; i<=n; i++){
        if(point[i]%2==1 || point[i]==0){
            res = false;
            break;
        }
    }
    if(res) cout << "1" <<endl;
    else cout << "0" <<endl;
    return 0;
}