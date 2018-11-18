#include <math.h>
int RetuLevel(int pos){//返回所在层数
  int i = 0;
  if(pos <= 1) return 1;
  while(!(pos>(int)pow(2,i) && pos<(int)pow(2,(i+2))))
    i++;
  return i+2;
}
int RetuParent(int pos){//返回父节点
  int i = 0;
  if(pos <= 1) return 0;
  i = RetuLevel(pos);
  return pow(2,i-1) + (pos-pow(2,i))/2;
}

int LCA( int T[],  int P1, int P2 ){
  int m, n;
  if(T[P1] == 0){
    printf("ERROR: T[%d] is NULL\n", P1);
    return 0;
  }
  if(T[P2] == 0){
    printf("ERROR: T[%d] is NULL\n", P2);
    return 0;
  }
  m = P1;
  n = P2;
  while(RetuLevel(m) != RetuLevel(n)){
    if(RetuLevel(m) > RetuLevel(n)) m = RetuParent(m);
    else                            n = RetuParent(n);
  }
  while(m != n){
    m = RetuParent(m);
    n = RetuParent(n);
  }
  return m;
}



