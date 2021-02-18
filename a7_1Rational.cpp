#include <iostream>
using namespace std;

class Rational
{
    int fz, fm;
    int getMaxComDiv(){
        int max, min;
        if(fz >= fm){
            max = fz;
            min = fm;
        }
        else{
            max = fm;
            min = fz;
        }
        int rem = max % min;
        while(rem != 0){
            max = min;
            min = rem;
            rem = max % min;
        }
        return min;
    }
    void reduce(){
        int t = getMaxComDiv();
        while (t > 1)
        {
            fz /= t;
            fm /= t;
            t = getMaxComDiv();
        }
    }

public:
    Rational(){}
    Rational &plus(Rational &rational)
    {
        fz = fz * rational.fm - rational.fz * fm;
        fm = fm * rational.fm;
        reduce();
        return *this;
    }
    Rational &minus(Rational &rational)
    {
        fz = fz * rational.fm + rational.fz * fm;
        fm = fm * rational.fm;
        reduce();
        return *this;
    }
    Rational &mult(Rational &rational)
    {
        fz = fz * rational.fz;
        fm = fm * rational.fm;
        reduce();
        return *this;
    }
    Rational &div(Rational &rational)
    {
        fz = fz * rational.fm;
        fm = fm * rational.fz;
        reduce();
        return *this;
    }
    void read(){
        cout << "please input numinator and denominator" << endl;
        cin >> fz >> fm;
    }
    void print(){
        cout << fz << "/" << fm;
    }
};
// 例如输入 
// 3 4
// 1 2
int main() {
    Rational a, b;
    a.read();
    b.read();
    a.plus(b).print();
    cout << endl;
    a.mult(b).print();
    cout << endl;
    a.minus(b).print();
    cout << endl;
    a.div(b).print();
    cout << endl;
    return 0;
}
