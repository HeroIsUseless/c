#include "iostream"
#include "set"
#include "stack"
using namespace std;
//超级优化的算法
//原理是因为要顺序输出，所以自动排列就好了。。。
int main(){
    int num, n;
    set<int> s;
    int max=0;
    for(int i=0; i<n; i++){//完全看不懂。。。
    //甚至都不是顺序输出
        cin >> num;
        if(s.upper_bound(num) != s.end()){
            //这个也仅仅是二分法插入而已
            s.erase(s.upper_bound(num));
        }
        s.insert(num);
    }
    cout << s.size();
    return 0;
}