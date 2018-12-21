#include "iostream"
#include "queue"
using namespace std;
typedef struct BSTree{
    int Key;
    BSTree *Left, *Right, *Parent;
    int Height;
} BSTree;
//二叉树插入操作，但左子树键值大，右子树键值小
BSTree* InsertBST(BSTree *cT, int cKey){
    BSTree *bst = (BSTree*)malloc(sizeof(BSTree));
    bst->Key = cKey; 
    bst->Left = bst->Right = bst->Parent = NULL;
    if(cT == NULL) cT = bst;
    BSTree *tBST = cT; //进行遍历然后插入
    while (true) {
        if (cKey > tBST->Key) {
            if (tBST->Left != NULL) 
                tBST = tBST->Left;
            else { 
                tBST->Left = bst; 
                bst->Parent = tBST;
                break; 
            }
        }else if (cKey < tBST->Key) {
            if (tBST->Right != NULL) 
                tBST = tBST->Right;
            else {
                tBST->Right = bst; 
                bst->Parent = tBST;
                break; 
            }
        }else if(cKey == tBST->Key)  break;
    }
    return cT;
}
//层序遍历二叉树，同时判断是否是完全二叉树
//当有节点是叶子节点或者仅有左子树存在时
//剩下的均为叶子节点
bool LevlOrdTravers(BSTree *cBST){
    bool res = true;
    bool tag = false;//判断是不是到了叶子节点与非叶子节点的交界处
    if(!cBST) return true;//容错处理，当为空时不能执行
    cout << cBST->Key;
    std::queue<BSTree*> q;
    q.push(cBST);
    while(!q.empty()){
        BSTree* tBST;
        tBST = q.front();
        if(tBST!=cBST) cout << " " << tBST->Key;
        q.pop();
        if(tBST->Left)  q.push(tBST->Left );
        if(tBST->Right) q.push(tBST->Right);
        //进行完全二叉树的判断
        if(tBST->Left==NULL && tBST->Right){
            res = false;
        }
        if(tBST->Left&&tBST->Right==NULL ||
            tBST->Left==NULL&&tBST->Right==NULL){
            tag = true;
        }
        if(tag){
            if(tBST->Left&&tBST->Right)
                res = false;
        }
    }
    return res;
}
//先创建BST，然后进行判断是否完全二叉树，层序输出即可
int main(){
    int n; cin >>n;
    BSTree *root = NULL;
    for(int i=0; i<n; i++){
        int tKey; cin >> tKey;
        root = InsertBST(root, tKey);
    }
    bool res = LevlOrdTravers(root);cout<<endl;
    if(res) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}