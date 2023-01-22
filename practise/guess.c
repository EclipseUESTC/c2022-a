#include<stdio.h>
int main(){
    int x = 36,a = -1,cnt = 0;
    while(a != x){
        cnt ++;
        printf("Guess Number:(1~100)\n");
        scanf("%d",&a);
        if (a > x){
            printf("TOO BIG!\n");
        }
        if (a < x){
            printf("TOO SMALL!\n");
        }
    }
    printf("You are right!The number is %d! You have tried %d times.\n",x,cnt);
    return 0;
}