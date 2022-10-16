#include<stdio.h>
#include<stdbool.h>
#include<time.h>
int main(){
    clock_t start,end;
    double total;
    start = clock();
    for (int i=2;i<1000;i++){
        bool flag = true;
        for (int j=2;j*j<i;j++){
            if (i % j == 0){
                flag = false;
 //               printf("%d is not a prime",i);
                break;
            }
        }
        if (flag) printf("%d ",i);
    }
    printf("\n");
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("execute_time = %.2f s",total);
    return 0;
}