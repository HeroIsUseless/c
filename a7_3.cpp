#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

class Queue {
private:
    Node *head, *rear;
    int size;
public:
    Queue(){
        size = 0;
        head = rear = nullptr;
    }
    ~Queue(){
        while(head){
            Node *pnode = head;
            head = head->next;
            free(pnode);
        }
    }
    void enqueue(int i){
        size++;
        Node *node = new Node();
        if(rear == nullptr){
            head = rear = node;
        }
        else
        {
            node->data = i;
            node->next = nullptr;
            rear->next = node;
            rear = rear->next;
        }
    }
    void dequeue(){
        size--;
        if (head->next == nullptr)
        {
            free(head);
            head = rear = nullptr;
        }
        else{
            Node *pnode = head;
            head = head->next;
            free(pnode);
        }
    }
    int front(){
        if(size == 0){
            return 0;
        }
        return head->data;
    }
};

const int N = 20;
// Use Queue to solve the Josephus problem (Q.6 of assignment 3).
int main() {
    Queue q;
    int cur;
    for (int i = 0; i < N; ++i)
        q.enqueue(i);
    for (int i = 0; i < N - 1; ++i) {
        cur = q.front();
        q.dequeue();
        q.enqueue(cur);
        cur = q.front();
        q.dequeue();
        q.enqueue(cur);
        cout << q.front() << ' ';
        q.dequeue();
    }
    cout << endl;
    return 0;
}
