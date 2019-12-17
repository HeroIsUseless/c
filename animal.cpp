#include <iostream>

using namespace std;
class Animal{
public:
    virtual void show()=0;
};
class Dog: public Animal{
    int age;
    double weight;
public:
    Dog(int age, double weight):age(age),weight(weight){}
    void show(){
        cout<<this->age<<" "<<this->weight<<endl;
    }
};
class Cat: public Animal{
    int age;
    double weight;
public:
    Cat(int age, double weight):age(age),weight(weight){}
    void show(){
        cout<<this->age<<" "<<this->weight<<endl;
    }
};

int main(){
    Dog dog(10, 20);
    dog.show();
    Cat cat(5, 10);
    cat.show();
    return 0;
}