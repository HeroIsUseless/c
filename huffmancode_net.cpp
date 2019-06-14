#include "iostream"
using namespace std;

struct Node{
    char c;
    int w;
    Node *lchild;
    Node *rchild;
    Node(){}
    Node(char cc, int cw){
        c = cc; w = cw;
        lchild = rchild = NULL;
    }
    Node(Node *pn1, Node *pn2){
        c=0; w = pn1->w + pn2->w;
        lchild=pn1;
        rchild=pn2;

    }
};
// 递归从头节点进行打印
void print(Node *cn){
    cout << cn->c << " " << cn->w <<endl;
    if(cn->lchild){
        print(cn->lchild);
    }
    if(cn->rchild){
        print(cn->rchild);
    }
}
// 编码函数，用了比较复杂的递归方式
// 参数：哈夫曼树头节点指针，一个字符，编码数组，编码数组长度
void encode(Node *node, char c, int arr[], int n){
    if(node->c == c){
        for(int i=0; i<n; i++) cout << arr[i];
        cout<<endl;
        return;
    }
    else if(node->c == 0){
        if(node->lchild!=NULL){
            arr[n++] = 0;
            encode(node->lchild, c, arr, n);
            n--;
        }
        if(node->rchild!=NULL){
            arr[n++] = 1;
            encode(node->rchild, c, arr, n);
            n--;
        }
    }
    else return;
}
// 解码函数
// 参数：哈夫曼树头节点指针，字符串，字符串长度
void decode(Node *head, char *s, int n){
    Node *pnode = head;
    for(int i=0; i<n+1; i++){
        if(pnode->c != 0){
            cout << pnode->c;
            pnode = head;
        }
        if(s[i] == '0'){
            pnode = pnode->lchild;
        }
        else if(s[i] == '1'){
            pnode = pnode->rchild;
        }
    }
}
int main(){
    cout << "Huffman Code" <<endl;
    cout << "[1]init Huffman code"<<endl;
    cout << "[2]huffman encode"<<endl;
    cout << "[3]huffman decode"<<endl;
    cout << "[information]this can only allow 27 alphabets and please replace space by *" <<endl;
    cout << "Please input number:";

    Node *ar_nod[27];
    char c; int w;    
    Node *head;
    while(1){
        int num;
        cin >> num;
        if(num == 1){
            cout << "init" <<endl;
            for(int i=0; i<27; i++){
                cin >> c >> w;
                Node *node = new Node(c, w);
                ar_nod[i] = node;
            }int len = 27;
            while(len != 1){
                int tw=1000, tpos1, tpos2;
                for(int i=0; i<27; i++){ // 提取第一个最小值
                    if(ar_nod[i]!=NULL && ar_nod[i]->w < tw){
                        tw = ar_nod[i]->w; tpos1 = i;
                    }
                }
                tw=1000;
                for(int i=0; i<27; i++){ // 提取第二个最小值
                    if(ar_nod[i]!=NULL && ar_nod[i]->w < tw && i!=tpos1){
                        tw = ar_nod[i]->w; tpos2 = i;
                    }
                }
                //cout << "node2:" << ar_nod[tpos2]->c << " " <<ar_nod[tpos2]->w<<endl;
                Node *tnode = new Node(ar_nod[tpos1], ar_nod[tpos2]);
                ar_nod[tpos1] = tnode;
                ar_nod[tpos2] = NULL;
                //cout << "node3:" << ar_nod[tpos1]->c << " " <<ar_nod[tpos1]->w<<" ";
                //cout << ar_nod[tpos1]->lchild->w << " " <<ar_nod[tpos1]->rchild->w<<endl;
                len--;
            }
            for(int i=0; i<27; i++){
                if(ar_nod[i]!=NULL) head = ar_nod[i];
            }
            cout << "Please input number:";
        }
        if(num == 2){
            cout << "encode" <<endl;
            char s[1000]={0};
            cin >> s;
            int len_s=0;
            while(s[len_s])len_s++;
            for(int i=0; i<len_s; i++){
                int arr[50], n=0;
                encode(head, s[i], arr, n);
            }
            cout << "Please input number:";
        }
        if(num == 3){
            cout << "decode" <<endl;
            char s[1000]={0};
            cin >> s;
            int len_s=0;
            while(s[len_s])len_s++;
            decode(head, s, len_s);
            cout << "\nPlease input number:";
        }
    }
    return 0;
}
//[encode]test code:
/*
* 1
a 2
b 3
c 4
d 5
e 6
f 7
g 8
h 9
i 10
g 11
k 12
l 13
m 14
n 15
o 16
p 17
q 18
r 19
s 20
t 21
u 22
v 23
w 24
x 25
y 26
z 27
 */

//[decode]test code:
//00011001100001