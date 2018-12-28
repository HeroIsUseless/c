#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

int main(){
    std::vector<int> v;
    int n; cin >> n;
    for (int i = 0; i < 2*n; i++)
    {
        int t; cin >> t;
        if(find(v.begin(), v.end(), t)==v.end()){
            v.push_back(t);
        }
    }
    sort(v.begin(), v.end());
    cout<< v[v.size()/2-1];
    return 0;
}