/*
ID:22920179
LANG:C
TASK:
*/
#include <iostream>
#include <fstream>
using namespace std;

int main(void)
{
    int i;
    ifstream fin(".in");
    fin >> i;
    fin.close();
    ofstream fout(".out");
    fout << i;
    fout.close();
    return 0;
}

