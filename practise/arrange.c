#include<stdio.h>
int a[20];
void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int arrange(int num){
    for (int i=0;i<num;i++){
        swap
    }
}
int main(){
    int n,all = 0;
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        all *= 10;
        all += i;
        a[n-i-1] = i;
    }
    arrange(all);
    return 0;
}