#include <iostream>
using namespace std;

class Polynomial {
    private:
        int deg;
        double coeff[100];
    public:
        Polynomial& plus(Polynomial &poly){
            if(deg < poly.deg){
                for (int i = deg+1; i <= poly.deg; i++){
                    coeff[i] = 0;
                }
                deg = poly.deg;
            }
            for(int i=0; i<=deg; i++){
                coeff[i] = coeff[i] + poly.coeff[i];
            }
            return *this;
        }
        Polynomial& mult(Polynomial &poly){
            for (int i = deg + 1; i <= 99; i++)
                coeff[i] = 0;
            int end_deg = deg + poly.deg;
            double end_coeff[99] = {0};
            for (int i = 0; i <= end_deg; i++)
            {
                double res = 0;
                for (int p = 0; p <= deg; p++){
                    for (int q = 0; q <= poly.deg; q++){
                        if(p+q == i){
                            res += coeff[p] + poly.coeff[q];
                        }
                    }
                }
                res /= 2;
                end_coeff[i] = res;
            }
            deg = end_deg;
            for (int i = 0; i <= end_deg; i++){
                coeff[i] = end_coeff[i];
            }
            return *this;
        }
        double eval(double r){
            double t = 1;
            double res = 0;
            for (int i = 0; i <= deg; i++){
                res += coeff[i] * t;
                t = t * r;
            }
            return res;
        }
        Polynomial& derivative(){
            deg--;
            for (int i = 0; i <= deg; i++){
                coeff[i] = coeff[i + 1] * (i + 1);
            }
            return *this;
        }
        void read(){
            int d;
            cin >> d;
            deg = d;
            for (int i = 0; i <= d; i++)
            {
                int t;
                cin >> t;
                coeff[i] = t;
            }
        }
        void print(){
            for (int i = 0; i <= deg; i++){
                if(i == 0){
                    cout << coeff[i];
                }
                else{
                    if(coeff[i]>0){
                        cout << "+" << coeff[i] << "x^" << i;
                    }
                    else if(coeff[i]<0)
                    {
                        cout << coeff[i] << "x^" << i;
                    }
                }
            }
        }
};

int main() {
    Polynomial p, q;
    cout << "Input the first polynomial (The degree d, followed by d + 1 coefficients c_0, c_1, ..., c_d):" << endl;
    p.read();
    p.print();
    double r;
    cout << "d/dx ("; p.print(); cout << ") = "; p.derivative().print(); cout << " ." << endl;
    p.print(); cout << " evaluated at x = 1.5 equals " << p.eval(1.5) << " ." << endl;
    cout << "Input the second polynomial:" << endl;
    q.read();
    cout << "("; p.print(); cout << ") + ("; q.print(); cout << ") = "; p.plus(q).print(); cout << endl;
    cout << "("; p.print(); cout << ") * ("; q.print(); cout << ") = "; p.mult(q).print(); cout << endl;
    return 0;
}
