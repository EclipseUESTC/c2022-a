#include<stdio.h>
int main(){
    int x = 36,a;
    printf("Please enter a number:(1~100)\n");
    scanf("%d",&a);
    int n = 1;
    while (a != x){
        if (a > x){
            printf("TOO BIG!Please enter another:\n");
            scanf("%d",&a);
        }
        if (a < x){
            printf("TOO SMALL!Please enter another:\n");
            scanf("%d",&a);
        }
        n = n + 1;
    }
    printf("You are right! The number is %d, you've tried %d times.\n",x,n);
    return 0;
}