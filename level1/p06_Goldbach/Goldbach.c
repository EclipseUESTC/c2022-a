#include<stdio.h>
#include<stdbool.h>
void judge(int num,int i);
int prime[100];
int main(){
    int cnt = 0;
    for (int i=2;i<100;i++){
        bool flag = true;
        for (int j=2;j*j<i;j++){
            if (i % j == 0){
                flag = false;
                break;
            }
        }
        if (flag) prime[cnt++] = i;
    }
 //   for (int i=0;i<cnt;i++) printf("%d ",prime[i]);
    for (int i=6;i<=100;i++) judge(cnt,i);
    return 0;
}
void judge(int num,int i){
    for (int j=0;j<num;j++){
        for (int k=j;k<num;k++){
            for (int l=k;l<num;l++){
                if (prime[j] + prime[k] + prime[l] == i){
                    printf("%d + %d + %d = %d\n",prime[j],prime[k],prime[l],i);
                    return;
                }
            }
        }
    }
}