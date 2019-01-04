#include <stdio.h>
#include <stdlib.h>

enum method{
    ASCII,
    BINARY
};
int main()
{
    printf("Hello world!\n");
    return 0;
}
FILE* createFile(char _path[]){

}
FILE*openFile(char _path[],method _method){
    FILE *file;
    if(_method==ASCII) file=fopen(_path,"r+");
    if(_method==BINARY) file=fopen(_path,"rb+");
    return file;
}
void closeFile(char _path[]){

}
int readFile(char _path,viod *_p){
    int a=0;


    return a;
}
void writeFile(char _path,viod *_p,int length,int _n){
    int a;
    FILE *file;
    file=fopen(_path,"ab+");
    a=sizeof(_p)
}
void copyFile(char _path1[],char _path2[]){
    FILE *pfile1,*pfile2;

    if((pfile1=fopen(_path1,"r"))==NULL){printf("error1!");exit(0);}
    if((pfile2=fopen(_path2,"w"))==NULL){printf("error2!");exit(0);}

    while(!feof(pfile1)){
        ch=fgetc(pfile1);
        fputc(ch,pfile2);
        putchar(ch);
    }
    putchar(10);

    fclose(pfile1);
    fclose(pfile2);
}



