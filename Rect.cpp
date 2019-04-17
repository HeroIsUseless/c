#include "iostream"
using namespace std;
template<typename T>
class Rect{
    private:
    T l_x, l_y, r_x, r_y;

    public:
    Rect(T lx, T ly, T rx, T ry)
        :l_x(lx), l_y(ly), r_x(rx), r_y(ry){}

    T getPerimeter(){
        return 2*(r_x-l_x) + 2*(r_y-l_y);
    }

    T getArea(){
        return (r_x-l_x) * (r_y-l_y);
    }
};

int main(){
    float ar[] = {1.0, 2.0, 3.0, 4.0};
    Rect<float> rect(ar[0], ar[1], ar[2], ar[3]);
    cout << rect.getPerimeter() << endl;
    cout << rect.getArea() << endl;
    return 0;
}