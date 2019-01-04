#include "iostream"
#include "map"
using namespace std;

int main(){
    int n; cin >> n;
    map<long long, int> m;
    long long phoNum1, phonum2;
    int i; for(i=0; i<n; i++){
        cin >> phoNum1 >> phonum2;
        m[phoNum1]++;m[phonum2]++;
    }
    //输入完毕
    int max=-1; long long phoNum;//进行查找
    int cont=1;//狂人的人数
    for(auto iter=m.begin(); iter!=m.end(); iter++){
        if(max < iter->second){
            max = iter->second;
            phoNum = iter->first;
            cont = 1;
        }else if(max == iter->second){
            if(phoNum > iter->first)
                phoNum = iter->first;
            cont++;
        }
    } 
    cout << phoNum <<" "<< max;
    if(cont != 1) cout <<" "<< cont;
    return 0;
}