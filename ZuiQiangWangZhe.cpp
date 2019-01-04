#include "iostream"
using namespace std;

int main(){
    int n, m; cin >> n >> m;
    int ar[100000];
    for(int i=1; i<=n; i++){
        cin >> ar[i];
    }
    int x, l, r;
    for(int i=0; i<m; i++){
        cin >> x >> l >>r;
        if(x == 1){
            int index, max = 0;
            for(int j=l; j<=r; j++){
                if(max < ar[j]){
                    max = ar[j];
                    index = j;
                } 
            }
            cout << index <<" "<< max <<endl;            
        }
        if(x == 0){
            ar[l] = r;
        }
    }
    return 0;
}