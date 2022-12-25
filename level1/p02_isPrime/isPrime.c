#include <stdio.h>
int main(){
    long long n,i;
    scanf("%d",&n);
    for (i=2;i*i<=n;i++){
        if (n % i == 0){
//            printf("%d is not a Prime.",n);
            printf("No, %d * %d = %d",i,n/i,n);
            return 0;
        }
    }
//    printf("%d is a Prime.",n);
    printf("yes");
    return 0;
}