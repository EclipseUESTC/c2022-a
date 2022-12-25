#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#define W 0
#define S 1
#define A 2
#define D 3
char map[5][6] = {
    {'#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ','#'},
    {' ',' ','*','$',' ','#'},
    {' ',' ',' ','@',' ','#'},
    {' ',' ',' ',' ',' ','#'},
};
int length=6,width=5,boxes=1,boxes_in_place=0,des=1,x=1,y=2,person;
int direction[4][2]={{-1,0}/*w*/,{1,0}/*s*/,{0,-1}/*a*/,{0,1}/*d*/};//1:WASD(direction);2:x,y decisive expression
bool withinBorder(int x,int y);
void prtmap();
void readmap();
void createMap(int length,int width);
bool ifMapOK();
bool movable(int dir,int step);
void swap(char *a,char *b);
void aMove2b(char *pos,char *destination);
void move(int dir);
bool judge();
int main(){
//    freopen("map.in","r",stdin);
//    readmap();
    if (!ifMapOK()){
        printf("error:illegalMap\n");
        return 0;
    }
//    createMap(length,width);
    while(1){
        prtmap();
        printf("Your command:");
        char command = getch();
        printf("%c",command);
        switch (command){
            case 'w':
                move(W);
                printf("move:up\n");
                break;
            case 's':
                move(S);
                printf("move:down\n");    
                break;
            case 'a':
                move(A);
                printf("move:left\n");
                break;
            case 'd':
                move(D);
                printf("move:right\n");    
                break;
            default:
                printf("invalidOperation\n");
                break;
        }
    }
}
bool withinBorder(int x,int y){
    return (x>=0 && x<length && y >= 0 && y< width);
}
void prtmap(){
//    system("cls");
    printf("pos:X:%d Y:%d\n",x+1,y+1);
    for (int j=0;j<width;j++){
        for (int i=0;i<length;i++){
            printf("%c",map[j][i]);
        }
        printf("\n");
    }
}
void readmap(){
    printf("enter your map size:(i*j)");
    scanf("%d%d",&length,&width);
    printf("ENTER YOUR MAP:(without borders)\n' ' = way\n# = wall\n* = your position\n$ = box\n@ = destination\n%% = box in des\n& = you in des:");
    for (int j=0;j<width;j++){
        getchar();
        for (int i=0;i<length;i++){
            scanf("%c",&map[j][i]);
            printf("[%d][%d] = '%c'\n",j,i,map[j][i]);
            switch (map[j][i]){
            case '*':
            case '&':
                x = i;
                y = j;
                person++;
                des++;
                break;
            case '$':
                boxes++;
                break;
            case '%':
                boxes_in_place++;
                break;
            case '@':
                des++;
                break;
            default:
                break;
            }
        }
    }
    system("pause");
}
void createMap(int length,int width){
    for (int i=0;i<width;i++){
        for (int j=0;j<length;j++){
            scanf("%c",&map[j][i]);
        }
        getchar();
    }
}
bool ifMapOK(){
    return (person == 1 || boxes + boxes_in_place == des);
}
bool movable(int dir,int step){
    int moveX = x + step * direction[dir][1], moveY = y + step * direction[dir][0];
    if (!withinBorder(moveX,moveY)) {
        printf("move:outofBorder\n");
        return false;
    }
    switch (map[moveY][moveX]){
        case '#':
            printf("movable:false-wall\n");
            return false;
        case '$':
        case '%':
            return movable(dir,step+1);
        default:
            return true;
    }
}
void swap(char *a,char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}
void aMove2b(char *pos,char *destination){
    switch (*pos){
    case '*':
        switch (*destination){
        case ' ':
            printf("move:personMove2Empty\n");
            swap(pos,destination);
            break;
        case '@':
            printf("move:personMove2Box\n");
            *pos = ' ';
            *destination = '&';
            break;
        default:
            printf("error:personFailedMove\n");
            system("pause");
            exit(-1);
        }
        break;
    case '$':
        switch (*destination){
        case ' ':
            printf("move:boxMove2Empty\n");
            swap(pos,destination);
            break;
        case '@':
            printf("move:boxMoveIntoDes\n");
            *pos = ' ';
            *destination = '%';
            break;
        default:
            printf("error:boxFailedMove\n");
            system("pause");
            exit(-1);
            break;
        }
        break;
    case '%':
        switch (*destination){
        case ' ':
            *pos = '@';
            *destination = '$';
            break;
        case '@':
            swap(pos,destination);
            break;
        default:
            printf("error:failedMove\n");
            system("pause");
            exit(-1);
            break;
        }
        break;
    case '&':
        switch (*destination){
        case ' ':
            *pos = ' ';
            *destination = '%';
            break;
        case '@':
            swap(pos,destination);
            break;
        default:
            printf("error:failedMove\n");
            system("pause");
            exit(-1);
            break;
        }
        break;
    default:
        break;
    }
}
void move(int dir){
    int step = 1;
    if (movable(dir,step)){
        int moveY = y+step*direction[dir][0],moveX = x+step*direction[dir][1];
        char pos = map[moveY][moveX];
        while(pos != ' ' && pos != '@'){
            step++;
        }
        printf("Move:step=%d\n",step);
        for (;step>0;step--){
            moveY = y+step*direction[dir][0];
            moveX = x+step*direction[dir][1];
            pos = map[moveY][moveX];
            aMove2b(&map[y+(step-1)*direction[dir][0]][x+(step-1)*direction[dir][1]],&pos);
        }
        y += direction[dir][0];
        x += direction[dir][1]; 
    }else{
        printf("error:illegalMove\n");
    }
}
bool judge(){
    boxes = 0;
    boxes_in_place = 0;
    for (int j=0;j<width;j++){
        for (int i=0;i<length;i++){
            switch (map[j][i]){
            case '%':
                boxes_in_place++;
                break;
            case '$':
                boxes++;
                break;
            default:
                break;
            }
        }
    }
    printf("Boxes:%d    ",boxes);
    printf("Boxes in place:%d\n",boxes_in_place);
    return !boxes;
}