#include "iostream"
#include "string"
using namespace std;

class Person{
    public:
    string idc;
    string name;
    bool sex;
    string brith;
    string address;
    public:
    Person(){};
    Person(const Person &cpersion){
        this->idc = cpersion.idc; this->name = cpersion.name;
        this->sex = cpersion.sex; this->brith = cpersion.brith;
        this->address = cpersion.address;
    }
    Person(string cidc, string cname, bool csex, string cbrith, string caddress)
        :idc(cidc), name(cname), sex(csex), brith(cbrith), address(caddress){}
    void print(){
        cout << "name:" << name <<endl;
        cout << "idc:" << idc <<endl;
        cout << "sex:" << (sex?"male":"female") <<endl;
        cout << "brith:" << brith <<endl;
        cout << "address:" << address <<endl;
        cout << "-----------------------"<<endl;
    }
};

int main(){
    Person person[10];
    for(int i=0; i<10; i++){
        person[i].name = "name" + to_string(i);
        person[i].idc = to_string(i);
        person[i].sex = i%2;
        person[i].brith = "1999/8/" + to_string(i);
        person[i].address = "address" + to_string(i);
    }
    int i=9; do{
        if(person[i].sex) person[i].print();
    }while(i --> 0);
    return 0;
}