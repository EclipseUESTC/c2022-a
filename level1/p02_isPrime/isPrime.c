#include <stdio.h>
int main(){
    int n,i;
    scanf("%d",&n);
    for (i=2;i*i<n;i++){
        if (n % i == 0){
            printf("%d is not a Prime.",n);
            return 0;
        }
    }
    printf("%d is a Prime.",n);
    return 0;
}