#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 1000000
typedef int ElemType;
void GetNext(char cstr[], int cnext[]){
    int i=0, cnext[0]=-1, j=-1;
    while(i < strlen(cstr)){
        if(j==-1 || cstr[i]==cstr[j]){
            i++; j++;
            if(cstr[i] != cstr[j]) cnext[i] = j;
            else                   cnext[i] = cnext[j];//���������ͬ�Ļ�����ôi��j��ȫ���Կ�����ȣ���ô����ȫ���Ը�ֵ
        }else j = cnext[j];
    }
}
int main()
{
    int i=0, j=0;
    int next[MAXSIZE];
    char str1[MAXSIZE], char str2[MAXSIZE];
    GetNext(str2, next);
    while(i<strlen(str1) && j<strlen(str2)){
        if(j==0 || s[i]==S[j]){
            i++; j++;
        }else j = next[j];
    }
    if(j >= strlen(str2)) return 1;
    else return 0;
    return 0;
}



