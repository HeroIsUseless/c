#include<iostream>
using namespace std;
class PopOnEmpty{

};
class PushOnFull{

};
class Stack
{
	int *data; // 数据数组
	int top; // 栈顶指针
	int capacity; // 容量
public:
	Stack();
	Stack(int size);
	void Push(int d);
	int Pop();
	int GetTop();
	int IsFull();
	int IsEmpty();
	void Clear();
	~Stack();
};

Stack::Stack()
{
	capacity = 100; // 默认初始化为100
	data = new int[100];
	top =0;
}

Stack::Stack(int size)
{
	capacity = size;
	data = new int[capacity];
	top =0;
}

void Stack::Push(int d)
{
    if(top >= capacity){
        PushOnFull pof;
        throw pof;
    } 
	data[top] = d;
	top ++; 
}

int Stack::Pop()
{
    if(top <= 0){
        PopOnEmpty poe;
        throw poe;
    }
	top --;
	return data[top];
}

int Stack::GetTop()
{
	return data[top-1];
}

int Stack::IsEmpty()
{
	if(top <= 0) return 1;
	else return 0;
}

int Stack::IsFull()
{
	if(top >= capacity)
		return 1;
	else
		return 0;
}

void Stack::Clear()
{
	top = 0;
}

Stack::~Stack()
{
	delete []data;
}

// 设计两个异常类PopOnEmpty 和PushOnFull。
// 改写Stack类，为Stack类的Push操作和Pop操作增加相应的异常抛出。
// 写一个主程序，测试异常的捕获堆栈类。
int main(){
    Stack s;
    try{
        for(int i=0; i<105; i++){
            s.Push(i);
        }
    }
    catch(PushOnFull pof){
        cout <<"[error]:PushOnFull"<<endl;
    }
    try{
        for(int i=0; i<105; i++){
            s.Pop();
        }        
    }
    catch(PopOnEmpty poe){
        cout <<"[error]:PopOnEmpty"<<endl;
    }

    return 0;
}