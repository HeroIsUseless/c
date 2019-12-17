#include <iostream>
using namespace std;
class Point{
    double x;
    double y;
public:
    Point(double x, double y):x(x),y(y){}
    Point(Point *p){
        this->x = p.x;
        this->y = p.y;
    }
    void Disp(){
        cout <<x << " " <<y<<endl;
    }
};

int main(){
    Point point(1,2);
    point.Disp();
    return 0;
}