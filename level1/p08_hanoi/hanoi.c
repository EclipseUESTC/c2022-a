#include<stdio.h>
void hanoi(int n,char pos,char temp,char des){
    if (n > 1){
        hanoi(n-1,pos,des,temp);
        printf("%c -> %c\n",pos,des);
        hanoi(n-1,temp,pos,des);
    }
    else printf("%c -> %c\n",pos,des);
}
int main(){
    int n;
    scanf("%d",&n);
    hanoi(n,'A','B','C');
    return 0;
}