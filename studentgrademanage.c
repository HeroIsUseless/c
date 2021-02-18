#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, M;
    // 输入有多少个学生和多少个课程，用来开辟数组用
    printf("Please input students' count and courses' count:\n");
    scanf("%d %d", &N, &M);
    int n = 0;
    int *score = (int *)malloc(sizeof(int) * N * M); // 成绩们的数组
    int *stu = (int *)malloc(sizeof(int) * N); // 总成绩的数组
    int *ave = (int *)malloc(sizeof(int) * N); // 平均成绩的数组
    int *sort = (int *)malloc(sizeof(int) * N * M); // 排好序的数组
    while(1){
        printf("student grade manage:\n");
        printf("1: grade input\n");
        printf("2: grade search\n");
        printf("3: grade statistics\n");
        printf("4: grade sort\n");
        printf("please input number:\n");
        int command;
        scanf("%d", &command);
        int i,j,k,m;
        // 输入学生成绩
        if(command == 1){
            printf("Please input grades:\n");
            for (m = 0; m < M; m++){
                int t;
                scanf("%d", &t);
                score[n * M + m] = t;
            }
            n++;
            printf("grades input success!\n");
        }
        if(command == 2)
        {
            printf("Please input student id(0 <= id < N):\n");
            int id;
            scanf("%d", &id);
            if(id <0 || id>=n){
                printf("There is no such student\n");
                continue;
            }
            for (m = 0; m < M; m++){
                printf("%d ", score[id * M + m]);
            }
            printf("\n");
        }
        if(command == 3){
            for (i = 0; i < N; i++){
                int total = 0, average = 0;
                for (j = 0; j < M; j++){
                    total += score[i * M + j];
                }
                average = total / M;
                stu[i] = total;
                ave[i] = average;
            }
            printf("all students' total grade:\n");
            for (i = 0; i < n; i++)
            {
                printf("%d ", stu[i]);
            }
            printf("\n");
            printf("all students' average grade:\n");
            for (i = 0; i < n; i++)
            {
                printf("%d ", ave[i]);
            }
            printf("\n");
        }
        if(command == 4){
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < M; j++)
                {
                    sort[i * M + j] = score[i * M + j];
                }
            }
            for (i = 0; i < n; i++){
                for (j = i + 1; j < n; j++){
                    // 进行依次比较
                    int flag = 0;
                    for (k = 0; k < M; k++){
                        // 这里采取从大到小排列
                        if (sort[i * M + k] < sort[j * M + k])
                        {
                            flag = 1;
                        }
                        if (sort[i * M + k] > sort[j * M + k])
                        {
                            break;
                        }
                    }
                    if(flag){
                        for (k = 0; k < M;k++){
                            int t = sort[i * M + k];
                            sort[i * M + k] = sort[j * M + k];
                            sort[j * M + k] = t;
                        }
                    }
                }
            }
            // 整体打印一遍
            for (i = 0; i < n; i++){
                for (j = 0; j < M; j++){
                    printf("%d ", sort[i * M + j]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}