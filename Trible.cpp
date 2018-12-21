#include "iostream"
#include "set"
#include "map"
#define MAXSIZE 10000
int pre[MAXSIZE], p[MAXSIZE];
using namespace std;
int find(int x){//找到根节点
    if(pre[x] == x)
        return x;
    else
        return x = find(x);
}
int mix(int a, int b){
    int fa = pre[a];
    int fb = pre[b];
    if(fa != fb)
        pre[fb] = fa;
    return fa;
}
int main(){
    std::set<int> people;
    std::map<int, int> trible;
    int n; cin >> n;
    for(int i=0; i<n; i++){
        int tn; cin >> tn;
        int trb = i;
        for(int j=0; j<tn; j++){
            int t; cin >> t;
            if(!people.count(t)){
                people.insert(t);
                trible[t] = trb;
            }else{
                for(map<int,int>::iterator iter=trible.begin();
                        iter!=trible.end(); iter++){
                    if(iter->second == trb)
                       iter->second = trible[t];
                }
                trb = trible[t];
            }
        }
    }
    cout << people.size() <<" "<< trible.size() <<endl;

    int dn; cin >> dn;
    for(int i=0; i<dn; i++){
        int a, b; cin >> a >> b;
        if(trible[a] == trible[b])
            cout << "Y" <<endl;
        else 
            cout << "N" <<endl;
    }
    return 0;
}







































































