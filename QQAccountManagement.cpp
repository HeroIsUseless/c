#include "iostream"
#include "string"
#include "map"
using namespace std;

int main(){
    int n; cin >> n;
    std::map<long long, string> m;
    char com; long long qqNum; string pwd;
    for(int i=0; i<n; i++){
        cin >> com; cin >> qqNum; cin >> pwd;
        if(com == 'R'){
            if(m.find(qqNum)!=m.end()){
                cout << "ERROR: Account Number Already Exists" <<endl;
            }else{
                cout << "Register Successful" <<endl;
                m[qqNum] = pwd;
            }
        }else{
            if(m.find(qqNum)!=m.end()){
                if(m[qqNum] == pwd){
                    cout << "Log in Successful" <<endl;
                }else{
                    cout << "ERROR: Wrong Password" <<endl;
                }
            }else{
                cout << "ERROR: Account Not Exist" <<endl;
            }
        }
    }
    return 0;
}