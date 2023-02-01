#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
int size;
typedef struct {
    int quan;
    char type[64]; 
    char name[128];
}Goods;
typedef struct {
    int sp;
    Goods *goods;
}Warehouse;
Warehouse *createHouse(int size){
    Warehouse *wtemp = (Warehouse *)malloc(sizeof(Warehouse));
    wtemp->sp = 0;
    wtemp->goods = (Goods *)malloc(sizeof(Goods)*size);
    return wtemp;
}
Warehouse *ware = createHouse(100);
Goods *createGoods(int q,char t[],char n[]){
    Goods *tgoods = (Goods *)malloc(sizeof(Goods));
    strcpy(tgoods->name,n);
    tgoods->quan = q;
    strcpy(tgoods->type,t);
    return tgoods;
}
void prtGoods(Goods good){
    printf("%-15s %-15s %-6d\n",good.name,good.type,good.quan);
}
void fprtGoods(Goods good,FILE *fp){
    fprintf(fp, "%-15s %-15s %-6d\n",good.name,good.type,good.quan);
}
void addList(Warehouse *ware,Goods tgoods){
    ware->goods[ware->sp++] = tgoods;
    prtGoods(tgoods);
    size++;
    printf(" %d\n",ware->sp);
    printf("Added successfully.\n");
}
void deleteList(Warehouse *ware,int ptr){
    printf("You choose to delete:");
    prtGoods(ware->goods[ptr-1]);
        size --;
        for (int i=ptr-1;i<size;i++)
            ware->goods[i] = ware->goods[1+i];
        printf("The pointer item deleted successfully.\n");
}
void showList(Warehouse *ware){
    printf("   NAME            TYPE            QUANTITY\n");
    for (int i=0;i<size;i++){
        printf("%d. ",i+1);
        prtGoods(ware->goods[i]);
    }
}    
void input(){//读取文件中仓库信息
    int quantity;
    char type[64];
    char name[128];
    FILE *fp = fopen("warehouse.txt","r+");
    if (fp == NULL) {
        printf("Warehouse doesn't exist. A new warehouse will create for you.\n");
        system("pause");
        return ;
    }
    printf("Opened warehouse successfully\n");
    while (fscanf(fp,"%s %s %d",name,type,&quantity) != EOF){
        Goods *goods_r = createGoods(quantity,type,name);
        addList(ware,*goods_r);       
    }
 
    
    //    else printf("Overloaded:The max volume is 100!\n.");
    
    fclose(fp);
}
void output(){//输出文件
    FILE *fp = fopen("warehouse.txt","w+");
    for (int i=0;i<size;i++){
        fprtGoods(ware->goods[i],fp);
    } 
}
int main(){   
//    printf("While input Please enter IN FORMAT:(ATTENTION: MAX = 100)\n[NUM: NAME TYPE QUAN]\n");
    input();
    while (1){
        int quantity,num,command;
        char name[128];
        char type[64];
        Goods *good;
        printf("Welcome to Warehouse system\nOperation:\n     1 - show list\n     2 - add list\n     3 - delete item\n     4 - exit execution.\nYour command:");
        scanf("%d",&command);
        switch (command)
        {
        case 1:
            showList(ware);
            break;
        case 2:
            printf("Enter in this way:\nNAME TYPE QUANTITY\n");
            scanf("%s %s %d",name,type,&quantity);
            good = createGoods(quantity,type,name);
            addList(ware,*good);
            break;
        case 3:
            printf("Enter NO. you want to delete:");
            scanf("%d",&num);
            if (num < 0 || num > size) {
                printf("Delete failed: Num given not in range.\n");
                break;
            }
            else {
                deleteList(ware,num);
                break;
            }
        default:
            output();
            system("pause");
            return 0;
        } 
    }
    return -1;
}