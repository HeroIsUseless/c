#include "algorithm"
#include "iostream"
#include "queue"
using namespace std;

typedef struct BSNode{
    int Key;
    BSNode *Left, *Right;
    int Height;
} *BSTree;
void LevlOrdTravers(BSTree cBST){
    if(!cBST) return;//容错处理当为空时不能执行
    cout << cBST->Key;
    std::queue<BSTree> q;
    q.push(cBST);
    while(!q.empty()){
        BSTree tBST;
        tBST = q.front();
        if(tBST!=cBST) cout << " " << tBST->Key;
        q.pop();
        if(tBST->Left)  q.push(tBST->Left );
        if(tBST->Right) q.push(tBST->Right);
    }
}
BSTree InsertBST(BSTree cT, int cKey){
    BSTree bst = new BSNode;
    bst->Key = cKey; 
    bst->Left = bst->Right = NULL;
    if(cT == NULL) cT = bst;
    BSTree tBST = cT; //进行遍历然后插入
    while (true) {
        if (cKey < tBST->Key) {
            if (tBST->Left != NULL) 
                tBST = tBST->Left;
            else { 
                tBST->Left = bst; 
                break; 
            }
        }else if (cKey > tBST->Key) {
            if (tBST->Right != NULL) 
                tBST = tBST->Right;
            else {
                tBST->Right = bst; 
                break; 
            }
        }else if(cKey == tBST->Key)  break;
    }
    return cT;
}
//返回的是节点指针的指针，
///那么赋值null操作就是*tBST=NULL就可以成功
BSTree* GetBSNode(BSTree cT, int cKey){//感觉还行
    BSTree *tBST = NULL;
    if(cT->Key == cKey) {
        tBST = &cT;
        return tBST;
    }
    if(cT->Left){
        if(cT->Left->Key == cKey){
            tBST = &(cT->Left);
            return tBST;
        }else{
            if(!tBST) tBST = GetBSNode(cT->Left, cKey);
        }
    }
    if(cT->Right){
        if(cT->Right->Key == cKey){
            tBST = &(cT->Right);
            return tBST;
        }else{
            if(!tBST) tBST = GetBSNode(cT->Right, cKey);
        }
    }
    return tBST;
}
//判断在其子树中是否存在这个节点
bool IsExistKey(BSTree cT, int cKey){
    if(!cT) return false;
}
//删除这个节点，有一个问题就是必须按照引用父节点的子节点来表示才行
void Dele(BSTree &cT){

}
//这个函数的作用是递归找到将要删除的节点，并删除之
//由于要删除父节点的子节点，所以应该那么做
void DelBST(BSTree cT, int cKey){
    if(!cT) return;
    if(cT->Key == cKey) Dele(cT);//根节点就是问题节点，删除
    else{
        if(cT->Left && cT->Left->Key==cKey){
            Dele(cT->Left);
        }else if(cT->Right && cT->Right->Key==cKey){
            Dele(cT->Right);
        }else{
            DelBST(cT->Left, cKey);
            DelBST(cT->Right, cKey);
        }
    }
}
//插入数据，然后删除一些数据，然后层序遍历
int main(int argc, char const *argv[])
{
    int n; cin >> n;
    BSTree root=NULL;
    vector<int> v;
    for(int i=0; i<n; i++) {
        int tKey; cin >> tKey;
        root = InsertBST(root, tKey);
    }   
    //LevlOrdTravers(root); cout << endl;
    int delN; cin >> delN;
    for(int i=0; i<delN; i++) {
        int tKey; cin >> tKey;
        //LevlOrdTravers(root); cout << endl;
        root = DelBST(root, tKey);
    }
    LevlOrdTravers(root); cout << endl;
    v.~vector();
    return 0;
}

