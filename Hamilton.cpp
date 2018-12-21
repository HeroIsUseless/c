#include "iostream"
#include "map"
#include "vector"
#include "algorithm"
#include "set"
using namespace std;
//输入原始数据，然后判断每一条回路
int main(){
    int n, m; cin >> n >> m;
    std::map<int, std::set<int>> mp;
    for(int i=0; i<m; i++) {
        int p1, p2; cin >> p1 >> p2;
        mp[p1].insert(p2);
        mp[p2].insert(p1);
    }
    int k; cin >>k;
    int res = true;
    for(int i=0; i<k; i++) {
        int kn; cin >> kn;
        std::vector<int> v;
        for(int i=0; i<kn; i++) {//进行录入
            int t; cin >> t;
            v.push_back(t);
        }
        if(kn != n+1){//如果点数不对不行
            cout << "NO" <<endl;
            continue;
        }
        if(v.front() != v.back()){//头尾节点不相同不行
            cout << "NO" <<endl;
            continue;
        }
        int res = true;
        for(auto var : v){//有重复点不行
            if(count(v.begin(), v.end()-1, var) > 1){
                cout << var <<" "<< count(v.begin(), v.end(), var) <<endl;
                res = false;
                break;
            }
        }
        for(int i=1; i<v.size()-1; i++){//不连通不行
            if(mp[v[i]].count(v[i+1]) == 0){
                res = false;
                break;
            }
        }
        //有顶点不在内不行
        if(res) cout << "YES" <<endl;
        else cout << "NO" <<endl;
    }
    return 0;
}