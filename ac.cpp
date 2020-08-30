#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
struct Node{
    char c;
    bool end;
    vector<Node*> child;
    Node(char c) : c(c) { this->end = false; }
};
class Trie{
    Node *root;

public:
    Trie(){
        root = new Node('\0');
    }
    void insert(string s){
        Node *p = root;
        for(char c : s){
            int i, n=p->child.size();
            for (i = 0; i < n; i++){
                if (c == p->child[i]->c)
                    break;
            }
            if(i == n){
                p->child.push_back(new Node(c));
            }
            else{
                p = p->child[i];
            }
        }
    }
    void printAll(){
        print(this->root);
    }
    void print(Node *root){
        for(auto node : root->child){
            cout << node->c;
            if(node->child.size() == 0)
                cout << endl;
            else
                print(node);
        }
    }
    ~Trie(){
        delete root;
    }
};
// Trie树构建呢，是针对每一个单词插入比较方便
int main(){
    vector<string> v = {"say", "she", "shr", "he", "her"};
    Trie t;
    for(string s : v){
        t.insert(s);
    }
    t.printAll();
    return 0;
}