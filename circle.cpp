class Circle{
    double r;
public:
    Circle(double r):r(r){}
    double Area(){return 3.14*r*r;}
};

class Column:public Circle{
    Circle c;
    double h;
public:
    Column(double r, double h):c(r),h(h){}
    double Volume(){return 3.14*r*r;}
    void show(){cout<<Volume()<<endl;}
}

int main(){
    Column column(5, 10);
    column.show();
    return 0;
}