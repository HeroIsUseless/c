#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    int i, j, pos=0, n=0;
    char s1[1000000],s2[1000000];
    char ls[100][100] = {{0}};
    
    cin.get(s1, 1000);
    cin.get();
    cin.get(s2, 1000);
    char p = s2[0];
    char *s = &s2[2];
    for(i=0; i<strlen(s1); i++){
        if(s1[i] == p){
            if(i == 0){
                ls[n++][0] = 0;
                if(strlen(s1) >= 1) pos = 1;
            }else if(i == strlen(s1)-1){
                for(j=pos; j<i; j++)
                    ls[n][j-pos] = s1[j];
                n += 1;
                ls[n++][0] = 0;
            }else{
                for(j=pos; j<i; j++)
                    ls[n][j-pos] = s1[j];
                n += 1;
                pos = i+1;
            }
        }else if(s1[i]!=p && i==strlen(s1)-1){
                for(j=pos; j<=i; j++)
                    ls[n][j-pos] = s1[j];
                n += 1;
            }
    }
    cout << '[';
    for(i=0; i<n; i++){
        if(i == n-1)
            cout << '\"' << ls[i] << '\"';
        else
            cout << '\"' << ls[i] << "\", ";
    }
    cout << ']' << endl;
    for(i=0; i<n; i++){
        if(i == n-1)
            cout << ls[i];
        else
            cout << ls[i] << s;
    }
    return 0;
}
