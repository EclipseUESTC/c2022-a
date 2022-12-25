#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node *next;
}ListNode;
ListNode *initList(){
    //def the head;
    ListNode *L = (ListNode *) malloc(sizeof(ListNode));
    if (!L){
        printf("Malloc failed!\n");
        exit(0);
    }
    L->next = NULL;
    return L;
}
ListNode *createNode(int data){
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode -> data = data;
    newNode -> next = NULL;
    return newNode;
}
void output(ListNode *headNode){
    ListNode *p = headNode->next;
    while (p->next != NULL){
        printf("%d -> ",p->data);
        p = p->next;
    }
    printf("%d\n",p->data);
}
void insertNodeByHead(ListNode *lastNode,int data){
    ListNode *nowNode = createNode(data);
    nowNode->next = lastNode -> next;
    lastNode->next = nowNode;
}
void deleteNodeByHead(ListNode *headNode,int posData){
    if (headNode->next == NULL){
        printf("error:emptyList\n");
        return;
    }
    ListNode *posNode = headNode->next;
    ListNode *lastNode = headNode;
    while (posNode->data != posData){
        if (headNode->next != NULL){
            lastNode = posNode;
            posNode = posNode->next;
        }
        else printf("error:dataNotFound\n");
    }
    lastNode-> next = posNode ->next;
    free(posNode);
}
int main(){
    ListNode *list = initList();
    for (int i=0;i<5;i++){
        insertNodeByHead(list,i);
    }
    output(list);
    deleteNodeByHead(list,3);
    output(list);
    return 0;
}