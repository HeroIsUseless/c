#include "iostream"
#include "map"
#include "vector"
#include "algorithm"
#include "queue"
using namespace std;
std::vector<int> v;
std::vector<int> r;
std::map<int, map<int, int>> road;
//这里要检查一下是否已经被使用了
int GetMinRoad(int &a){
    int minRoad = 10000;
    int b;
    for(auto iter=road[a].begin(); iter!=road[a].end(); iter++){
        if(minRoad > iter->second){
            minRoad = iter->second;
            b = iter->first;
        }
    }
    a = b;
    return minRoad;
}
//输入数据，
//判断所有点是否能够连接，即保证每一个点至少
//有一个度
//找出最小路径，找出最低成本，进行删度就可以了
//从一个端点开始
int main()
{
    int n, m; cin >> n >> m;
    int degree[1000]={0};
    for(int i=1; i<=n; i++) v.push_back(i);
    for(int i=1; i<=m; i++){
        int a, b, c; cin >>a >>b >>c;
        road[a][b] = c;
        degree[a]++; degree[b]++;
    }
    for(int i=1; i<=m; i++){
        if(degree[i] == 0){
            cout << "-1";
            return 0;
        }
    }
    //遍历一个节点的路径，找到最短的那个路径
    //遍历它之前的所有节点，看看直接连通的路径是否有更短的，
    //比较连接
    int a = v[0]; v.erase(v.begin());
    r.push_back(a);
    while(!v.empty()){
        //获取这个最小长度
        int road1 = GetMinRoad(a);
        int b, road2 = 10000;
        //获取之前的那些最小长度
        for(auto var : r){
            for(auto iter=road[var].begin(); 
                iter!=road[var].end(); iter++){
                if(iter->first == a){
                    if(road2 > iter->second){
                        road2 = iter->second;
                        b = iter->first;
                    }
                }
            }
        }
        r.push_back(a); v.erase(find(v.begin(), v.end(), a));
        //往下存什么呢？感觉结构不太好
        if(road1 < road2){

        }else{

        }
    }
    return 0;
}
