#include "iostream"
#include "set"
using namespace std;
int main(){
    int n, p; cin >> n >> p;
    std::set<int> s;
    for(int i=0; i<n; i++){
        int t; cin >> t;
        s.insert(t);//假设它们都是无重复的
    }
    int max, min;
    int subN;//储存值
    auto it1 = s.begin();
    auto it2 = --s.end();
    for(auto it2=--s.end();it2!=s.begin();it2--){
        for(auto it1=s.begin(); it1!=it2; it1++){
            //but get the max one is a probm.
            //have poison...
            int tmax = s.max()
        }


    }
    return 0;
}