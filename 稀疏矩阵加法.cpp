#include <iostream>
using namespace std;
typedef struct Array{
    int row, col;
    int val;
};
int main(){
    int i, j,k, an, bn, n=0, t;
    int row,col;
    struct Array a[1000], b[1000], c[1000];
    cin >> row >> col >> an;
    n = an;
    for(i=0; i<an; i++)
        cin >> a[i].row >> a[i].col >> a[i].val;
    cin >> bn;
    for(i=0; i<bn; i++)
        cin >> b[i].row >> b[i].col >> b[i].val;

    for(j=0; j<bn; j++){
        for(i=0; i<an; i++){
            if(a[i].row==b[j].row && a[i].col==b[j].col){
                a[i].val += b[j].val;
                if(a[i].val == 0) n--;
                break;
            }
        }
        if(i == an){//证明没有匹配上
            a[an].row = b[j].row; a[an].col = b[j].col;
            a[an].val = b[j].val;
            an++;
            n++;
        }
    }
//现在进行排序，排序？
    for(i=0; i<an; i++){
        for(j=i; j<an; j++){
            if(a[i].row > a[j].row){
                    t = a[i].row; a[i].row = a[j].row; a[j].row = t;
                    t = a[i].col; a[i].col = a[j].col; a[j].col = t;
                    t = a[i].val; a[i].val = a[j].val; a[j].val = t;
            }else if(a[i].row == a[j].row){
                if(a[i].col > a[j].col){
                    t = a[i].row; a[i].row = a[j].row; a[j].row = t;
                    t = a[i].col; a[i].col = a[j].col; a[j].col = t;
                    t = a[i].val; a[i].val = a[j].val; a[j].val = t;
                }
            }
        }
    }
     cout << n << endl;
     for(i=0; i<an; i++)
            if(a[i].val < -0.1 || a[i].val > 0.1)
                cout << a[i].row << " " << a[i].col << " " << a[i].val<< endl;
    return 0;
}










