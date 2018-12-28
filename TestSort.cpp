#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

int main()
{
    std::vector<int> v;
    int n; cin >> n;
    for(int i=0; i<n; i++){
        int t; cin >> t;
        v.push_back(t);
    }
    sort(v.begin(), v.end());
    for(int i=0; i<n-1; i++){
        cout << v[i] << " ";
    }
    cout << v[n-1];
    return 0;
}
