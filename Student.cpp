#include "iostream"
using namespace std;

class Student{
    char id[12];
    char name[12]; 
    char sex;
    int age;
    char address[12];
    public:
    Student(char *id, char *name, char sex, int age, char *address):sex(sex),age(age){
        for(int i=0; i<12; i++){
            this->id[i] = id[i];
            this->name[i] = name[i];
        }
        for(int i=0; i<64; i++)
            this->address[i] = address[i];

    }
    bool operator>(Student &stu){
        bool res = true;
        for(int i=0; i<12; i++){
            if(this->id[i] < stu.id[i])
                return false;
        }
        return true;
    }
    friend ostream operator<<(ostream &out, Student const &stu);
    friend istream operator>>(istream &in, Student const &stu);
}
ostream operator<<(ostream &out, Student const &stu){
    out << stu.id <<....
    return out;
}
istream operator>>(istream &in, Student const &stu){
    char id[12];
    char name[12]; 
    char sex;
    int age;
    char address[12];
    in >> ... ;
    return in;
}