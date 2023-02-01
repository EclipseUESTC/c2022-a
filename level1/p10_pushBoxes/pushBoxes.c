#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#include<string.h>
#define W 0
#define S 1
#define A 2
#define D 3
char map[255][255];
char name[255];
int length,width,boxes,boxes_in_place,des,x,y,person,step;
int direction[4][2]={{-1,0}/*w*/,{1,0}/*s*/,{0,-1}/*a*/,{0,1}/*d*/};//1:WASD(direction);2:x,y decisive expression
bool withinBorder(int x,int y);
void prtmap();
void readmap();
void createMap();
bool ifMapOK();
int movable(int dir,int step);
void swap(char *a,char *b);
void aMove2b(char *pos,char *destination);
void move(int dir);
bool judge();
int main(){
//    freopen("map.in","r",stdin);
    readmap();
    createMap();
    if (!ifMapOK()){
        printf("error:illegalMap\n");
        _getch();
        return 0;
    }
    prtmap();
    while(1){
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
                printf("\nAre you sure to reset?\nPress 'y' to commit:");
                if (getch() == 'y'){
                    createMap();
                    step = 0;
                    printf("Map has been reset!\n");
                }
                break;
        }
        prtmap();
        if (judge()){
            prtmap();
            printf("You win! Steps:%d\nPress any key to exit...\n",step);
            _getch();
            return 0;
        }
    }
}
bool withinBorder(int x, int y)
{
    return (x>=0 && x<length && y >= 0 && y< width);
}
void prtmap(){
    system("cls");
    printf("pos:X:%d Y:%d step = %d\nwasd to move(others to reset)\n",x+1,y+1,step);
    for (int j=0;j<width;j++){
        for (int i=0;i<length;i++){
            printf("%c",map[j][i]);
        }
        printf("\n");
    }
    printf("' ' = way\n# = wall\n* = your position\n$ = box\n@ = destination\n%% = box in des\n& = you in des\n");
}
void readmap(){
    printf("Please enter the name of the map:");
    scanf("%s",name);
    strcat(name,".txt");
}
void createMap(){
    FILE *fp = fopen(name,"r");
    if (fp == NULL) {
        printf("error:Failed2LoadMap\n");
        return;
    }
    fscanf(fp,"%d %d\n",&length,&width);
    printf("length:%d width:%d\n",length,width);
    for (int j=0;j<width;j++){
        for (int i=0;i<length;i++){
            char temp = fgetc(fp);
            printf("Read[%d %d]:%c\n",j,i,temp);
            map[j][i] = temp;
            switch (temp){
            case '*':
                x = i;
                y = j;
                person++;
                break;
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
        fgetc(fp);
    }
    fclose(fp);
}

bool ifMapOK(){
    return (person == 1 || boxes + boxes_in_place == des);
}
int movable(int dir,int step){
    int moveX = x + step * direction[dir][1], moveY = y + step * direction[dir][0];
    if (!withinBorder(moveX,moveY)) {
        printf("move:outofBorder\n");
        return 0;
    }
    switch (map[moveY][moveX]){
        case '#':
            printf("movable:false-wall\n");
            return 0;
        case '$':
        case '%':
            return movable(dir,step+1);
        default:
            return step;
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
            *pos = '@';
            *destination = '*';
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
    printf("I am moving in MOVE now!,dir = %d\n",dir);
    int tstep = movable(dir,1);
    if (tstep){
        step++;
        printf("Move:step=%d\n",tstep);
        for (;tstep>0;tstep--)
            aMove2b(&map[y+(tstep-1)*direction[dir][0]][x+(tstep-1)*direction[dir][1]],&map[y+tstep*direction[dir][0]][x+tstep*direction[dir][1]]);
        y += direction[dir][0];
        x += direction[dir][1]; 
    }else{
        printf("error:illegalMove(void move)\n");
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