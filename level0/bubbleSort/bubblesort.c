#include<stdio.h>
#include<stdbool.h>
int a[105];
int main(){
    int n,i,j;
    scanf("%d",&n);
    for (i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for (i=0;i<n;i++){
        bool swapped = false;
        for (j=1;j<n;j++){
            if (a[j]<a[j-1]){
                int temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    for (i=0;i<n;i++)
    printf("%d ",a[i]);
    return 0;
}