#include<stdio.h>
#include<string.h>
char s[100005];
void convert(char str[],int len){
    for (int i=0;i<len;i++){
        int asc = (int)str[i];
        switch (asc/10)
        {
        case 6:case 7:case 8:
            asc -= 'A';
            asc = (asc + 15) % 26 + 'A';
            str[i] = char(asc);
            break;
        case 9:case 10:case 11:
            asc -= 'a';
            asc = (asc + 15) % 26 + 'A';
            str[i] = char(asc);
        default:
            break;
        }
    }
}
int main(){
    char c;
    int cnt=0;
    printf("enter a string that end with ' ':");
    do{
        scanf("%c",&c);
        if (c != ' ')
        s[cnt++] = c;
    } while (c!=' ');
    convert(s[105],cnt);
    for (int i=0;i<cnt;i++) printf("%c",s[i]);
    return 0;
}223+