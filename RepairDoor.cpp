#include "iostream"
#include "set"
using namespace std;

int main(){
    int n; cin>> n;
    std::multiset<int> s;
    for(int i=0; i<n; i++){
        int t; cin>> t;
        s.insert(t);
    }
    int res = 0;
    while(s.size() > 1){
        int a = *s.begin(); s.erase(s.begin());
        int b = *s.begin(); s.erase(s.begin());
        res += a+b;
        s.insert(a+b);      
    }
    cout<< res;
    return 0;
}