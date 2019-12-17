#include <string>
using namespace std;
class People
{
private:
public:
	string  name;              // 人名
	string  ID;               // 身份证号
	People();
	People(string newName, string newID);
	People(People& source);
};
People::People(string newName, string newID):name(newName), ID(newID){}
People::People(People& source){
    this->name = source.name;
    this->ID = source.ID;
}
class Student : public People
{
private:
	long int studentID;         // 学号
public:
	Student(string newName, string newID, long int newStuID);
	Student(People& thePeople, long int newStuID);
};
Student::Student(string newName, string newID, long int newStuID):name(newName),ID(newID),studentID(newStuID){}
Student::Student(People& thePeople, long int newStuID){
    this->name = thePeople.name;
    this->ID = thePeople.ID;
    this->studentID = newStuID;
}