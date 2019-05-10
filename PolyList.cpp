#include "iostream"
#include "string.h"
using namespace std;
// 继承node，来存储数据
// 必须重载 ==, != 运算符
// 必须继承node类的print函数（不是必须）

class PolyList{
    public:
    Node *head;
    PolyList(){head = null;}
    void insert(Node &node);
    void remove(Node *node);
    void printAll();
    ~PolyList();
};
// 每次插到前面
// 之所以它拷贝构造，是因为之前的并不一定是new出来的，就不能delete
void PolyList::insert(Node &node){
    Node *pNode = new Node(node);
    pNode->next = head;
    head = pNode;
}
// 因为用户只有在遍历的时候才会找到这个node，判断已经判断完毕了
void PolyList::remove(Node *node){
    Node *pNode = head;
    while(pNode!=null && *pNode->next!=*node) pNode = pNode->next;
    if(pNode) pNode->next = node->next;
    delete node;
}

void PolyList::printAll(){
    Node *pNode = head;
    while(pNode != null){
        pNode->print();
        pNode = pNode->next;
    }
}

~PolyList(){
    Node *pNode;
    while(head != null){
        pNode = head;
        head = head->next;
        delete pNode;
    }
}

class Node{
    public:
    Node *next;
    Node(){next = null};
    virtual bool operator==(Node const &node)=0;
    virtual bool operator!=(Node const &node)=0;
    virtual void print()=0; // 它只能是纯虚函数，毕竟不知道 key和value的类型到底是什么
    ~Node();
}


int main(){

    return 0;
}