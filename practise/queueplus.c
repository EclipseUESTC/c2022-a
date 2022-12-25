#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int *data;
    int h;
    int t;
    int size;
}Queue;
Queue *createQueue(int size){
    Queue *queue = (Queue *) malloc(sizeof(Queue)*size);
    queue->h = 0;
    queue->t = -1;
    queue->data = (int *) malloc(sizeof(int)*size);
    queue->size = size;
    return queue;
}
void push(int item,Queue *q){
    if (q->t<q->size)
    q->data[++q->t] = item;
    else printf("invalid operation:reached maximum %d\n",q->size+1);
}
int pop(Queue *q){
    if (q->t>=q->h){
        return q->data[q->h++];
    }else{
        printf("invalid operation:tail<head\n");
        return -1;
    }
}
int main(){
    int qsize;
    scanf("%d",&qsize);
    Queue *queue = createQueue(qsize);
    for (int i=0;i<queue->size;i++){
        int num;
        printf("enter a num:\n");
        scanf("%d",&num);
        if (num<0){
            break;
        }else {
           push(num,queue);
        }
    }
    while()
    return -1;
}