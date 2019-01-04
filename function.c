#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***********************************************
//数学函数
************************************************/
int mul10(int _n);
int theHighestCommonFactor(int _a,int _b);//最大公约数
int isSingleNum(int _a);//判断是否为素数
int apartSingleNum(int _a,int _b[]);//拆素数从大到小排列，返回数字个数
int singleNum(int _a);//用于生成素数
char* from10ToX(int _a,int _b);//用来把十进制转换为X进制，返回字符串
int getanynum(int _a,int _n);
int getnumlength(int _a);
void fromArrayToNum(int _a[][1000],int _b[],int _c,int _d[]);
int fromStringToNum(char _ch[],int _a[]);
int fromStringToNumArray(char _ch[],int _a[][1000],int _b[]);
int fromStringToNumArrayNew(char _ch[],int _a[][1000],int _b[]);
int bubbleSort(int _a[],int _b);//用冒泡法，数字从小到大排列，返回最大值
int selectionSort(int _a[],int _b);//用选择法，数字从小到大排列，返回最大值
void hadd(char _a[],char _b[],char _c[]);//高精度加法
void hmul(char _a[],char _b[],char _c[]);//高精度乘法
void combination(int _n,int _m,int _b[],int M);
/***********************************************
//调试函数
**********************************************/
void pi(char _c,int _a);
void pc(char _c1,char _c2);
void pn();
void pok();
void ps(char _c,char *s);
/**********************************************
//字符串函数
************************************************/
void strLink(char _ch1[],char _ch2[]);//链接字符串
void strCopy(char _ch1[],char _ch2[]);//拷贝字符串
void strCopyByNum(char _ch1[],char _ch2[],int n);//高级拷贝字符串
int strCompare(char _ch1[],char _ch2[]);//比对字符串
int strLen(char _ch1[]);//求得字符串长度
void strToCaptal(char _ch[]);//转换为大写字母
void strToLetter(char _ch[]);//转换为小写字母
void overString(char *_ch);//颠倒字符串
int compareShortStr(char *_pch1,char *_pch2);//比较小字符串在大字符串任意位置之后出现的次数
void deleteShortStr(char _ch1[],char _ch2[]);//删除大字符串中的所有小字符串
void numToString(int _a[],int _b,char _ch[]);//数组转换为字符串
/************************test*************************************/
void quickSort(int _a[], int _b)
{
    int i, j, k=_a[0];
    for(i=0, j=_b-1; i!=j; i++,j--)
    {
        for(i)
    }

}
///////////////////////////////////////////////////////////////////
void swape(int *p1,int *p2){
    int temp;
    temp=*p1;
    *p1=*p2;
    *p2=temp;
}
void permutation(int _a[],int _b,int _c){//组合
    int i,j;
    if(_b==_c){
        for(i=0;i<_c;i++){
            printf("%d ",_a[i]);
        }
        printf("\n");
    }else{
        for(i=_b;i<_c;i++){
            swape(&_a[_b],&_a[i]);
            permutation(_a,_b+1,_c);
            swape(&_a[_b],&_a[i]);
        }
    }
}
/************************main*************************************/
int main()
{
    int i=0,j=0,m=0,n=0,a[100][1000]={{0}},b[1000]={0},c[1000]={0},d=0,e=0,f=0;
    int *p1=NULL,*p2=NULL,*pm=&m,*pn=&n;
    const int M=3;
    char ch[10000]={0},ch1[1000]={0},ch2[1000]={0},chx[100][1000]={{0}};
    char *pch=ch,*pch1=ch1,*pch2=ch2;

    for(n=0;n<4;n++){
        b[n]=n;
    }
    permutation(b,0,5);
    //pi('i',theLowestCommonMultiple(n,m));
    //pc('c',);
    //ps('s',);
    return 0;
}

/***************************************************数学函数******************************************/
int mul10(int _n){
    int i,a=1;
    for(i=0;i<_n;i++){
        a*=10;
    }
    return a;
}
int theHighestCommonFactor(int _a,int _b){
    int c;
    while(_a%_b!=0){
        c=_a%_b;
        _a=_b;
        _b=c;
    }
    return _b;
}
int theLowestCommonMultiple(int _a,int _b){
    int a=theHighestCommonFactor(_a,_b);
    return _a*_b/a;
}
int isSingleNum(int _a){
    int i;
    for(i=2;i<_a;i++){
        if(_a%i==0) break;
    }
    if(i==_a) return 1;
        else  return 0;
}
int apartSingleNum(int _a,int _b[]){
    int i,a,k=0;
    for(i=1;singleNum(i)<_a;i++){
        a=singleNum(i);
        while(_a%a==0){
            _a/=a;
            _b[k]=a;
            k++;
        }
    }
    return k;
}
int singleNum(int _a){
    int i=1,a=0;
    while(a!=_a){
        i++;
        if(isSingleNum(i)) a++;
    }
    return i;
}
void hadd(char _a[],char _b[],char _c[]){
    int i=0,a=0,b=0,c[1000]={0},d[1000]={0},e[1000]={0},f=0,g=0;
    char ch[1000];
    overString(_a);
    overString(_b);
    while(_a[a]!=0)
        a++;
    while(_b[b]!=0)
        b++;
    while(_b[b]!=0)
        b++;
    for(i=0;i<a;i++)
    {
        c[i]=_a[i]-48;
    }
    for(i=0;i<b;i++)
    {
        d[i]=_b[i]-48;
    }
    g=a>b?a:b;
    for(i=0;i<g;i++)
    {
        f=c[i]+d[i];
        if(f<10)
        {
            e[i]=f;
        }
        else
        {
            e[i]=f%10;
            if(i==f-1)
            {
                e[i+1]=f/10;
                g+=1;
            }
            else
            {
                d[i+1]+=f/10;
            }
        }
    }
    for(i=0;i<g;i++)
    {
        ch[i]=e[i]+48;
    }
    ch[i+1]=0;
    overString(ch);
    i=0;
    while(ch[i]!=0)
    {
        _c[i]=ch[i];
        i++;
    }
    _c[i]=0;
}
void hmul(char _a[],char _b[],char _c[]){
    int n=0,i=0,j=0,a[1000]={0},b[1000]={0},c=0,d=0,e[100][1000]={{0}},f[100]={0},g=0,h=0,x=0;
    char ch[1000]={0},ch2[1000]={0};
    overString(_a);
    overString(_b);
    c=strlen(_a);
    d=strlen(_b);
    for(i=0;i<c;i++)
    {
        a[i]=_a[i]-48;
    }
    for(i=0;i<d;i++)
    {
        b[i]=_b[i]-48;
    }

    for(j=0;j<d;j++)
    {
        h=0;
        x=0;
        for(i=0;i<c;i++)
        {
            g=a[i]*b[j]+h;
            if(g<10)
                e[j][i]=g;
            else
            {
                if(i==c-1)
                {
                    e[j][i]=g%10;
                    e[j][i+1]=g/10;
                    x=c+1;
                }
                else
                {
                    e[j][i]=g%10;
                    h=g/10;
                }
            }
        }
        if(x==0) f[j]=c; else f[j]=x;
    }
    for(i=0;i<d;i++)
    {
        for(j=0;j<f[i];j++)
        {
            if(i!=0)
            {
                e[i][f[i]-1-j+i]=e[i][f[i]-1-j];
                e[i][f[i]-1-j]=0;
            }
        }
        f[i]+=i;
    }

    numToString(e[0],f[0],ch);
    overString(ch);
    for(i=1;i<d;i++)
    {
        numToString(e[i],f[i],ch2);
        overString(ch2);
        hadd(ch,ch2,ch);
    }
    i=0;
    while(ch[i]!=0)
    {
        _c[i]=ch[i];
        i++;
    }
    _c[i]=0;
}
int getanynum(int _a,int _n){
    int i,a=0;
    if(_n>getnumlength(_a)) goto er;

    for(i=1;i<=_n;i++){
        a=_a%10;
        _a/=10;
    }
    er:;
    return a;
}
int getnumlength(int _a){
    int i=0;
    do{
        _a/=10;
        i++;
    }while(_a!=0);
    return i;
}
void fromArrayToNum(int _a[][1000],int _b[],int _c,int _d[]){
    int i,j;
    for(i=0;i<_c;i++){
            _d[i]=0;
        for(j=0;j<_b[i];j++){
            _d[i]+=_a[i][j]*mul10(_b[i]-1-j);
        }
    }
}
int fromStringToNum(char _ch[],int _a[]){
    int i=0,j=0,a=0,a1=0,a2=0,b=0;

    if(_ch[0]<48||_ch[0]>57){
        while(_ch[i+1]<48||_ch[i+1]>57){
            i++;
        }
    a1=i+1;
    a2=i+1;
    i++;
    }
    while(_ch[i]!=0){
        if(_ch[i]<48||_ch[i]>57){
            b=1;
            while((_ch[i+1]<48||_ch[i+1]>57)&&(_ch[i+1]!=0)){
                i++;
                b++;
            }
            a2=i-b;
            _a[a]=0;

            for(j=a1;j<=a2;j++){
                _a[a]+=(_ch[j]-48)*mul10(a2-j);
            }
            a1=i+1;
            a++;
        }
        i++;
    }
    if(_ch[i]==0&&(_ch[i-1]>=48&&_ch[i-1]<=57)){
        a2=i-1;
        _a[a]=0;
        for(j=a1;j<=a2;j++){
            _a[a]+=(_ch[j]-48)*mul10(a2-j);
        }
        a++;
    }
    return a;
}
int fromStringToNumArray(char _ch[],int _a[][1000],int _b[]){
    int i=0,j=0,a=0,a1=0,a2=0,b=0;
    if(_ch[0]<48||_ch[0]>57){
        while(_ch[i+1]<48||_ch[i+1]>57){
            i++;
        }
    a1=i+1;
    a2=i+1;
    i++;
    }
    while(_ch[i]!=0){
        if(_ch[i]<48||_ch[i]>57){
            b=1;
            while((_ch[i+1]<48||_ch[i+1]>57)&&(_ch[i+1]!=0)){
                i++;
                b++;
            }

            a2=i-b;
            _b[a]=0;
            for(j=a1;j<=a2;j++){
                _a[a][_b[a]++]=(_ch[j]-48);
            }
            a1=i+1;
            a++;
        }
        i++;
    }
    if(_ch[i]==0&&(_ch[i-1]>=48&&_ch[i-1]<=57)){
        a2=i-1;
        _b[a]=0;
        for(j=a1;j<=a2;j++){
            _a[a][_b[a]++]=(_ch[j]-48);
        }
        a++;
    }
    return a;
}
int fromStringToNumArrayNew(char _ch[],int _a[][1000],int _b[]){
    int count=0,isnumber=1;
    char *pch=_ch;
    _b[0]=0;
    while(*pch!=0){
        if(*pch!=32){
            if(isnumber==1){
                _a[count][_b[count]]=*pch-48;
                _b[count]++;
            }else{
                _b[++count]=0;
                _a[count][_b[count]++]=*pch-48;
            }
            isnumber=1;
        }else{
            isnumber=0;
        }
        pch++;
    }
    return ++count;
}
int bubbleSort(int _a[],int _b){
    int i,j;
    for(i=0;i<_b;i++){
        for(j=0;j<_b-i-1;j++){
            if(_a[j]>_a[j+1]){
                _a[j]+=_a[j+1];
                _a[j+1]=_a[j]-_a[j+1];
                _a[j]-=_a[j+1];
            }
        }
    }
    return _a[_b-1];
}
int selectionSort(int _a[],int _b){
    int i,j,k=0,l=0;
    for(i=0;i<_b-1;i++){
        k=i;
        for(j=i+1;j<_b;j++){
            if(_a[k]>_a[j])
                k=j;
        }
        l=_a[i];
        _a[i]=_a[k];
        _a[k]=l;
    }
    return _a[_b-1];
}
char* from10ToX(int _a,int _b){
    int i=0,a=0;
    char ch[10000];
    while(_a!=0)
    {
        a=_a%_b;
        _a/=_b;
        switch(a)
        {
            case 0:ch[i]='0';i++;break;
            case 1:ch[i]='1';i++;break;
            case 2:ch[i]='2';i++;break;
            case 3:ch[i]='3';i++;break;
            case 4:ch[i]='4';i++;break;
            case 5:ch[i]='5';i++;break;
            case 6:ch[i]='6';i++;break;
            case 7:ch[i]='7';i++;break;
            case 8:ch[i]='8';i++;break;
            case 9:ch[i]='9';i++;break;
            case 10:ch[i]='A';i++;break;
            case 11:ch[i]='B';i++;break;
            case 12:ch[i]='C';i++;break;
            case 13:ch[i]='D';i++;break;
            case 14:ch[i]='E';i++;break;
            case 15:ch[i]='F';i++;break;
            case 16:ch[i]='G';i++;break;
            default:ch[i]='Z';i++;
        }
    }
    ch[i]='\0';
    overString(ch);
    return ch;
}
void combination(int _n,int _m,int _b[],int M){
    int i,j;
    for(i=_n;i>=_m;i--){
        _b[_m]=i;
        if(_m==1){
            for(j=1;j<=M;j++){
                printf("%d ",_b[j]);
            }
            printf("\n");
        }else{
            combination(i-1,_m-1,_b,M);
        }
    }
}
/**************************************************调试函数********************************************/
void pi(char _c,int _a){
    printf("%c:%d\n",_c,_a);
}
void pc(char _c1,char _c2){
    printf("%c:%c\n",_c1,_c2);
}
void pn(){
    printf("\n");
}
void pok(){
    printf("ok");
}
void ps(char _c,char *s){
    printf("%c:%s\n",_c,s);
}
/**************************************************字符串函数*******************************************/
void strLink(char _ch1[],char _ch2[]){
    strcat(_ch1,_ch2);
}
void strCopy(char _ch1[],char _ch2[]){
    strcpy(_ch1,_ch2);
}
void strCopyByNum(char _ch1[],char _ch2[],int n){
    strncpy(_ch1,_ch2,n);
}
int strCompare(char _ch1[],char _ch2[]){
    return strcmp(_ch1,_ch2)?0:1;
}
int strLen(char _ch1[]){
    return strlen(_ch1);
}
void strToCaptal(char _ch[]){
    strupr(_ch);
}
void strToLetter(char _ch[]){
    strlwr(_ch);
}
void numToString(int _a[],int _b,char _ch[]){
    int i;
    for(i=0;i<_b;i++)
    {
        _ch[i]=_a[i]+48;
    }
    _ch[i+1]=0;
}
void overString(char *_ch){
    int i=0,a=0;
    char ch;
    while(*(_ch+a)!=0)
        a++;
    for(i=0;i<a/2;i++)
    {
        ch=*(_ch+i);
        *(_ch+i)=*(_ch+a-1-i);
        *(_ch+a-1-i)=ch;
    }
}
int compareShortStr(char *_pch1,char *_pch2){
    int i=0,j=0,a=0;
    while(*(_pch1+i)!=0){
        if(*(_pch1+i)==*_pch2){
            j=0;
            while(*(_pch2+j)!=0){
                if(*(_pch1+i)==*(_pch2+j)){
                    i++;
                    j++;
                }else{
                    break;
                }
            }
            if(j==strLen(_pch2)) a++;
        }
        i++;
    }
    return a;
}
void deleteShortStr(char _ch1[],char _ch2[]){
    int i=0,i1=0,j=0,k=0;
    char ch[10000];
    char *pch;

    while(_ch1[i]!=0){
        while(_ch1[i]!=_ch2[0]&&_ch1[i]!=0){
            ch[k]=_ch1[i];
            k++;
            i++;
        }
        if(_ch1[i]==_ch2[0]){
            j=0;
            while(_ch1[i+j]!=0&&_ch2[j]!=0){
                if(_ch1[i+j]!=_ch2[j]) break;
                j++;
            }
            if(j==strLen(_ch2)){
                i+=strLen(_ch2);
            }else{
                ch[k]=_ch1[i];
                k++;
                i++;
            }
        }
    }
    ch[k]=0;
    for(i=0;i<=k;i++){
        _ch1[i]=ch[i];
    }
}












