#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int size;
typedef struct {
    int quan;
    char *type; 
    char *name;
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
Goods *createGoods(int q,char *t,char *n){
    Goods *tgoods = (Goods *)malloc(sizeof(Goods));
    tgoods->name = n;
    tgoods->quan = q;
    tgoods->type = t;
    return tgoods;
}
void addList(Warehouse *ware,Goods tgoods){
    ware->goods[ware->sp++] = tgoods;
}
void showList(Warehouse *ware){
    for (int i=0;i<size;i++)
    printf("%d: %s %s %d",i+1,ware->goods[i].name,ware->goods[i].type,ware->goods[i].quan);
}
void input(){//读取文件中仓库信息
    int quantity,sp;
    char *type;
    char *name;
    FILE *fp = fopen("warehouse.txt","r");
    if (fp == NULL) {
        printf("error:fileOpenFailed");
        return ;
    }
    while (fscanf(fp, "%d: %s %s %d",&sp,name,type,&quantity)){
        if (sp<100){
            Goods *goods_r = createGoods(quantity,type,name);
            addList(ware,*goods_r);    
        }
        else printf("Overloaded\n.");
    }
    fclose(fp);
}
void output(char *file){
    
}
int main(){
    
    input();
    printf("While input Please enter IN FORMAT:(ATTENTION: MAX = 100)\n");
    showList(ware);

    return 0;
}