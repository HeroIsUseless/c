#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
#define MAXSIZE 1000000
void GetNext(char cps[], int cpn[])
{
    int i=1, j=0, cpsn;
    cpn[0] = -1;
    cpsn = strlen(cps);
    while(i < cpsn)
    {
        if(cps[i]==cps[j] || j==-1)
        {
            i++;j++;
            cpn[i] = j;
        }
        else
        {
            j = cpn[j];
        }
    }

}
int GetResult(char* ps1, char* ps2, int* pn)
{
    int i=0, j=0;
    int ps1n, ps2n;
    ps1n = strlen(ps1);ps2n = strlen(ps2);
    if(ps1n > ps2n)
        i = ps1n-ps2n;
    while(i < ps1n)
    {
        if(ps1[i] == ps2[j])
            {i++;j++;}
        else if(ps1[i]!=ps2[j] && j==0)
            i++;
        else
            j = pn[j];
    }
    return j;
}
char ps[MAXSIZE],cs[MAXSIZE],xs[MAXSIZE];
int nextc[MAXSIZE],nextx[MAXSIZE];
int main()
{

    cin >> ps >> cs >> xs;
    GetNext(cs,nextc);
    GetNext(xs,nextx);
    int a, b;
    a = GetResult(ps, cs, nextc);
    b = GetResult(ps, xs, nextx);
    cout << a << " " << b << endl;
    return 0;
}



