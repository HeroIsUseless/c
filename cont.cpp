#include <iostream>
using namespace std;
class cont{
   public:
      // 纯虚函数
      virtual double vol() = 0;
      virtual void show() = 0;
};
class cube: public cont{
private:
    double len;
public:
    cube(double len):len(len){}
    double vol(){
        return len*len*len;
    }
    void show(){
        cout << len*len*len << endl;
    }
};
class sphere: public cont{
private:
    double r;
public:
    sphere(double r):r(r){}
    double vol(){
        return 4.0/3 * 3.14 *r*r*r;
    }
    void show(){
        cout << 4.0/3 * 3.14 *r*r*r << endl;
    }
};

int main(){
    cont *c;
    c = new cube(1);
    cout << c->vol() <<endl; 
    c->show();
    c = new sphere(1);
    cout << c->vol() <<endl; 
    c->show();
    return 0;
}