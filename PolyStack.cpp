#include "iostream"
using namespace std;
template <typename T>
class PolyStack{
    T *s;
    int n;
    public:
        PolyStack(){s = new T(100); n=0;}
        T pop(){return s[n--];}   
        void push(T t){s[++n] = t;}
        T top(){return s[n];}
        void clear(){n = 0;}
        bool isEmpty(){return n;}
        ~PolyStack(){delete[] s;}
};

int main(){
    PolyStack<int> ps;
    ps.push(1); ps.push(2); ps.push(3);
    cout << ps.top() << endl;
    cout<<ps.pop()<<" "<<ps.pop()<<" "<<ps.pop()<<endl;
    cout<<ps.isEmpty()<<endl;

    
    PolyStack<double> ps2;
    ps2.push(1.0); ps2.push(2.0); ps2.push(3.0);
    cout << ps2.top() << endl;
    cout<<ps2.pop()<<" "<<ps2.pop()<<" "<<ps2.pop()<<endl;
    cout<<ps2.isEmpty()<<endl;

    return 0;
}