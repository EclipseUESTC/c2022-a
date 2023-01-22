#include<stdio.h>
#include<stdlib.h>
char map[105][105];
int length,width,x,y;
void prtmap(){
    for (int i=0;i<length;i++){
        for (int j=0;j<width;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
}

int main(){
//    freopen("map.txt","r",stdin);
    printf("enter your map size:(i*j)");
    scanf("%d%d",&length,&width);
    printf("ENTER YOUR MAP:(without borders)\n. = way\n# = wall\n* = your position\n$ = exit:\n");
    for (int i=0;i<length;i++){
        getchar();
        for (int j=0;j<width;j++){
            scanf("%c",&map[i][j]);
            printf("[%d][%d] = '%c'\n",i,j,map[i][j]);
            if (map[i][j] == '*'){
                x = j;
                y = i;
            }
        }
    }
    do
    {
        char command;
        prtmap();
        printf("Now your position is (%d,%d)",x,y);
        printf("\nYour command:(wsad)\n");
        getchar();
        scanf("\n%c",&command);
        switch (command)
        {
        case 119:// 'w'
            if (y>0 && map[y-1][x] != '#' && map[y-1][x] != '$'){
                map[y][x] = '.';
                y --;
                map[y][x] = '*';
            }else if (map[y-1][x] == '#'){
                printf("invalid operation:hitwall\n");
            }else if (!y){
                printf("invalid operation:outofborder\n");
            }else{
                printf("You've win!\n");
                return 0;
            }
            break;
        case 115:// 's'
            if (y<width-1 && map[y+1][x] != '#' && map[y+1][x] != '$'){
                map[y][x] = '.';
                y ++;
                map[y][x] = '*';
            }else if (map[y+1][x] == '#'){
                printf("invalid operation:hitwall\n");
            }else if (y == width-1){
                printf("invalid operation:outofborder\n");
            }else{
                printf("You've win!\n");
                return 0;
            }
            break;
        case 97:// 'a'
            if (x>0 && map[y][x-1] != '#' && map[y][x-1] != '$'){
                map[y][x] = '.';
                x --;
                map[y][x] = '*';
            }else if (map[x-1][y] == '#'){
                printf("invalid operation:hitwall\n");
            }else if (!x){
                printf("invalid operation:outofborder\n");
            }else{
                printf("You've win!\n");
                return 0;
            }
            break;
        case 100:// 'd'
            if (x<length-1 && map[y][x+1] != '#' && map[y][x+1] != '$'){
                map[y][x] = '.';
                x ++;
                map[y][x] = '*';
            }else if (map[y][x+1] == '#'){
                printf("invalid operation:hitwall\n");
            }else if (x == length-1){
                printf("invalid operation:outofborder\n");
            }else{
                printf("You've win!\n");
                return 0;
            }
            break;
        default:
            printf("invalid operation:enteragain\n");
            break;
        }
    } while (1);
    return 0;
}