#include "iostream"
using namespace std;
//插入AVLTree，然后返回头节点即可
int main(){
    int n; cin >> n;
    AVLTree *root;
    for (size_t i = 0; i < n; i++) {
        int cKey; cin >> cKey;
        root = InsertAVL(root, cKey);
    }
    cout << root->Key << endl;
    return 0;
}