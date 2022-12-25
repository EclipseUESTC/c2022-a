#include<stdio.h>
#include<malloc.h>
#define SIZE 100
int head;
int stack[SIZE+5];
int pop(int arr[]){
    if (head>0){
        return stack[head--];
    }
    return -1;
}
void push(int arr[], int x){
    arr[++head] = x;
    return;
}
int main(){
    printf("Pay attenion:Please enter all figures(>=0) to push; Entering numbers < 0 ends pushing\n");
    while(1){
        int command = -1;
        printf("(1 to push; 2 to pop; else to quit)==>");
        scanf("%d",&command);
        switch (command){
        case 1:{
            while(1){
                int temp = 0;
                scanf("%d",&temp);
                if (temp>=0)
                push(stack,temp);
                else break;
            }
            break;
        }    
        case 2:{
            printf("%d ",pop(stack));
            break;
        }

        default:{
            for (int i=head;i>=0;i--){
                int t = pop(stack);
                if (t!=-1)
                printf("%d ",t);
            }
            return 0;
            break;
        }
        }
    }
}