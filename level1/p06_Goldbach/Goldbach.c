#include<stdio.h>
#include<stdbool.h>

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
    for (int i=6;i<=100;i++){
        bool flag2 = false;
        for (int j=0;j<cnt;j++){
            for (int k=j;k<cnt;k++){
                for (int l=k;l<cnt;l++){
                    if (prime[j] + prime[k] + prime[l] == i){
                        printf("%d + %d + %d = %d\n",prime[j],prime[k],prime[l],i);
                        flag2 = true;
                        break;
                    }
                }
                if (flag2) break;
            }
            if (flag2) break;
        }
        if (flag2) continue;
        else {
            printf("This isn't scientific!\n");
            return 0;
        }
    }
    return 0;
}