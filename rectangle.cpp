#include <iostream>
using namespace std;
class Rectangle{
    double w;
    double l;
public:
    Rectangle(){};
    Rectangle(double w, double l):w(w), l(l){}
    void show(){cout << w << " " <<l<<endl;}
    Rectangle& operator++(){
        this->l++;
        this->w++;
        return *this;
    }
    Rectangle operator*(int n){
        Rectangle rect(this->w, this->l);
        rect.l *= n;
        rect.w *= n;
        return rect;
    }
};

int main(){
    Rectangle rect(3, 4);
    rect.show();
    ++rect;
    rect.show();
    Rectangle rect2(rect*2);
    rect2.show();
    return 0;
}