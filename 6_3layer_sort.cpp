#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

struct Student{
    string name;
    string id;
    int math;
    int chinese;
    int english;
    Student(string name,
            string id,
            int math,
            int chinese,
            int english) : name(name), id(id), math(math), chinese(chinese), english(english){}
    int total(){
        return chinese + math + english;
    }
};
// 先按照总成绩排名，如果总成绩相同，
// 则根据数学成绩排名，如果数学成绩也相同，
// 则按照语文成绩排名，如果数学、语文成绩也相同，则按照英语成绩排名。
int main(){
    int n;
    FILE *fin = fopen("score.in", "r");
    FILE *fout = fopen("score.out", "w");
    fscanf(fin, "%d", &n);
    vector<Student> students;
    for (int i = 0; i < n; i++){
        char name[20];
        char id[20];
        int math, chinese, english;
        fscanf(fin, "%s %s %d %d %d", name, id, &math, &chinese, &english);
        students.push_back(Student(name, id, math, chinese, english));
    }
    for (int i = 0; i < students.size(); i++)
    {
        for (int j = i + 1; j < students.size(); j++)
        {
            if (students[i].total() < students[j].total())
            {
                Student student = students[i];
                students[i] = students[j];
                students[j] = student;
            }
            else if (students[i].total() == students[j].total())
            {
                if (students[i].math < students[j].math)
                {
                    Student student = students[i];
                    students[i] = students[j];
                    students[j] = student;
                }
                else if (students[i].math == students[j].math)
                {
                    if (students[i].chinese < students[j].chinese)
                    {
                        Student student = students[i];
                        students[i] = students[j];
                        students[j] = student;
                        if (students[i].chinese == students[j].chinese)
                        {
                            if (students[i].english < students[j].english)
                            {
                                Student student = students[i];
                                students[i] = students[j];
                                students[j] = student;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(fout, "%s %s %d %d %d\n", students[i].name.c_str(), students[i].id.c_str(), students[i].math, students[i].chinese, students[i].english);
    }
    cout << "success!Please read score.out" << endl;
    fclose(fin);
    fclose(fout);
    return 0;
}
