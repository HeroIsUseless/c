#include "iostream"
#include "stdio.h"
#include "string"
#include "map"
using namespace std;

int main(int argc, char const *argv[])
{
    int n; 
    cin >> n; cin.ignore();
    map<string, int> m; 
    map<string, int>::iterator mi;
    string str;
    for (int i=0; i<n; i++){
        getline(cin ,str);
        if(m.count(str)) m[str]++;
        else m.insert(pair<string, int>(str, 1));
    }
    for(auto it : m){
        float f = (float)it->second/(float)n; f *= 100;
        cout << it->first << " "; printf("%.4f", f); cout << "%" << endl;
    }
    return 0;
}