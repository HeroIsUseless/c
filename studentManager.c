#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN sizeof(struct St)
struct St{
    int id;char name[20];
    float score1;float score2;float score3;float avescore;
    int isUse;
};
int getStArrLen(struct St _st[]){
    int i;
    for(i=0;i<100;i++) if(_st[i].isUse==0) return i;
}
int main()
{
    int i,serial,n,nst=0;
    char name[20];
    struct St st[100],stTemp;
    FILE *pfile=NULL;
    for(i=0;i<100;i++) st[i].isUse=0;
    if((pfile=fopen("scores","rb"))==NULL) pfile=fopen("score","wb");fclose(pfile);
    printf("学生成绩管理系统\n");
    printf("--------------\n");
    printf(" ");printf("|");printf("输入数据");printf("|");printf("1");printf("|\n");
    printf(" ");printf("|");printf("显示数据");printf("|");printf("2");printf("|\n");
    printf(" ");printf("|");printf("查找数据");printf("|");printf("3");printf("|\n");
    printf(" ");printf("|");printf("数据排序");printf("|");printf("4");printf("|\n");
    printf(" ");printf("|");printf("插入数据");printf("|");printf("5");printf("|\n");
    printf(" ");printf("|");printf("数据存档");printf("|");printf("6");printf("|\n");
    printf("--------------\n");
    be:
    printf("\n\n请输入序号并回车：");
    scanf("%d",&serial);
    switch(serial){
        case 1:{//输入数据
            printf("\n请输入学生数量：");
            scanf("%d",&n);
            printf("请输入学生数据，依次为：\n");
            printf("学号 学生姓名 成绩1 成绩2 成绩3\n");
            pfile=fopen("scores","rb");fread(st,LEN,100,pfile);fclose(pfile);nst=getStArrLen(st);
            for(i=0;i<n;i++){
                scanf("%d %s %f %f %f",&st[nst+i].id,st[nst+i].name,
                      &st[nst+i].score1,&st[nst+i].score2,&st[nst+i].score3);
                st[nst+i].avescore=(st[nst+i].score1+st[nst+i].score2+st[nst+i].score3)/3;
                st[nst+i].isUse=1;
                nst++;
            }
            pfile=fopen("scores","wb");fwrite(st,LEN,100,pfile);fclose(pfile);
            printf("\n输入完成！\n");
            goto be;}
        case 2:{//显示数据
            printf("学号 学生姓名 成绩1 成绩2 成绩3 平均成绩\n");
            pfile=fopen("scores","rb");fread(st,LEN,100,pfile);fclose(pfile);nst=getStArrLen(st);
            for(i=0;i<nst;i++){
                printf("%d %s %.2f %.2f %.2f %.2f\n",st[i].id,st[i].name,
                      st[i].score1,st[i].score2,st[i].score3,st[i].avescore);
            }
            goto be;}
        case 3:{//查找功能
            printf("请输入名字：");
            scanf("%s",name);
            pfile=fopen("scores","rb");fread(st,LEN,100,pfile);fclose(pfile);nst=getStArrLen(st);
            for(i=0;i<nst;i++) if(strcmp(name,st[i].name)==0) printf("%d %s %.2f %.2f %.2f %.2f\n",st[i].id,st[i].name,
                                                                    st[i].score1,st[i].score2,st[i].score3,st[i].avescore);
            goto be;}
        case 4:{//排序功能
            pfile=fopen("scores","rb");fread(st,LEN,100,pfile);fclose(pfile);nst=getStArrLen(st);
            for(i=0;i<nst-1;i++){
                for(j=i;j<nst;j++){
                    if(st[i].avescore<st[j].avescore){
                        stTemp=st[i];
                        st[i]=st[j];
                        st[j]=stTemp;
                    }
                }
            }
            printf("\n排序成功！\n");
            goto be;}
        case 5:{//插入功能
            printf("请输入学生数据，依次为：\n");
            printf("学号 学生姓名 成绩1 成绩2 成绩3\n");
            pfile=fopen("scores","rb");fread(st,LEN,100,pfile);fclose(pfile);nst=getStArrLen(st);
            scanf("%d %s %f %f %f",&st[nst].id,st[nst].name,
                      &st[nst].score1,&st[nst].score2,&st[nst].score3);
            st[nst].avescore=(st[nst].score1+st[nst].score2+st[nst].score3)/3;
            st[nst+i].isUse=1;
            nst++;
            for(i=0;i<nst-1;i++){
                for(j=i;j<nst;j++){
                    if(st[i].avescore<st[j].avescore){
                        stTemp=st[i];
                        st[i]=st[j];
                        st[j]=stTemp;
                    }
                }
            }
            pfile=fopen("scores","wb");fwrite(st,LEN,100,pfile);fclose(pfile);
            printf("\n输入完成！\n");
            goto be;}
        case 6:{//存档功能
            printf("存储成功！");
            goto be;}
        default:{
            printf("执行失败，请重新输入：");
            goto be;
        }
    }
    return 0;
}
