#include<stdio.h>
#include<string.h>
//'A' = 65 'Z' = 90 'a' = 97 'z' = 122
char s[100005];
void encode(char str[],int n){
    for (int i=0;i<strlen(str);i++){
        if (str[i]>=65 && str[i]<=90){
            str[i] -= 'A';
            str[i] = (str[i] + n) % 26 + 'A';
        }else if (str[i]>=97 && str[i]<=122){
            str[i] -= 'a';
            str[i] = (str[i] + n) % 26 + 'a';
        }
    }
}
void decode(char str[],int n){
    for (int i=0;i<strlen(str);i++){
        
        if (str[i]>=65 && str[i]<=90){
            str[i] -= 'A';
            int temp = str[i] - n;
            if (temp < 0)
                temp += 26;
            str[i] = temp % 26 + 'A';
        }else if (str[i]>=97 && str[i]<=122){
            str[i] -= 'a';
            int temp = str[i] - n;
            if (temp < 0)
                temp += 26;
            str[i] = temp % 26 + 'a';
        }
    }
}
int main(){
    printf("enter a string:\n");
    scanf("%s",s);
    encode(s,14);
    printf("encoded:%s\n",s);
    decode(s,14);
    printf("decoded:%s\n",s);
    return 0;
}