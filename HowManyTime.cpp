#include <iostream>
#include "queue"
#include "cstring"
using namespace std;
int n, m;
int l[100][100];
int indeg[100];
int rout[100];
void go(int a){
    for(int i=0; i<n; i++){
        if(l[a][i] != -1){
            indeg[i]--;
            if(rout[a]+l[a][i] > rout[i])
                rout[i] = rout[a] + l[a][i];
            l[a][i] = -1;
            if(indeg[i] == 0)
                go(i);
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        indeg[i]=0; rout[i]=0;
        for(int j=0; j<n; j++)
            l[i][j]=-1;
    }
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        cin >> l[a][b];
        indeg[b]++;
    }
    for(int i=0; i<n; i++){
        if(indeg[i] == 0)
            go(i);
    }
    int maxRout=0;
    int i;
    for(i=0; i<n; i++){
        if(indeg[i] != 0) break;
        if(rout[i] > maxRout) 
            maxRout = rout[i];
    }
    if(i == n) cout << maxRout;
    else cout <<"Impossible";
    return 0;
}   