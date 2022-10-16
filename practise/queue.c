#include<stdio.h>
#include<stdbool.h>
#define SIZE 100
int q[SIZE + 5],h=0,t=0,len=0;
void push(int temp){
    if (t+1<=SIZE){
        len++;
        q[t++] = temp;
    }else printf("The tail is too long!\n");
    return ;
}
void pop(){
    if (h+1<=t){
        len--;
        h++;
    }else printf("The queue is too short!\n");
    return ;
}
int main(){
    bool flag = true;
    /*
    scanf("%d",&t);
    for (int i=h;i<t;i++){
        scanf("%d",&q[i]);
    }
    */
    while(1){
        int command,temp;
        printf("Please input your command:(1:pop;2:push;else:exit)");
        scanf("%d",&command);
        switch (command){
            case 1:
                pop();
                for (int i=h;i<t;i++){
                    printf("%d ",q[i]);
                }
                break;
            case 2:
                printf("Please enter a number:");
                scanf("%d",&temp);
                push(temp);
                for (int i=h;i<t;i++){
                    printf("%d ",q[i]);
                }
                break;
            default:
                flag = false;
                break;
        }
        if (!flag) return 0;
    }
}