#include <iostream>
#include "cstdio"
#include "vector"
#include "map"
#include "set"
using namespace std;

int main(){
    int n, m; cin >> n >> m;
    std::map<int, std::set<int>> mp;
    for(int i=0; i<m; i++) {
        int p1, p2; cin >> p1 >> p2;
        mp[p1].insert(p2); mp[p2].insert(p1);
    }
    //新建一个set，不断遍历插入，就是这样
    for(int i=1; i<=n; i++){//每个节点的遍历操作
        //下面是单个节点的操作//循环六层，看最后有多少个数
        std::set<int> s;
        s.insert(i);
        for(int j=0; j<6; j++){//循环6层
            //对set里的每一个元素进行遍历
            std::set<int> s_copy(s);
            for(set<int>::iterator iter=s_copy.begin(); iter!=s_copy.end(); iter++){
                //对每一个元素，找到它的关联点，插入到set中
                for(auto var : mp[*iter]){
                    s.insert(var);//中途发生改变，变得越来越长了
                }
            }
        }
        cout << i <<": ";
        printf("%.2f%%\n", ((double)(s.size())/(double)n)*100);
    } 
    return 0;
}