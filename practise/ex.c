#include<stdio.h>
#define num 256
char *s,*t;
void RLEcoding(char s[] , char t[]);//s是输入数据行，t是输出数据行 
int main()
{

	printf("请输入数据行:");
	scanf("%s",s);
	fflush(stdin);
	printf("mains:%s\n",s);//没问题 
	printf("maint:%s\n",t); 
	RLEcoding(s,t);
	printf("mains:%s\n",s); //出事
	printf("out:%p\n",t); 
	printf("maint:%s\n",t); 
	return 0;
 } 
 
void RLEcoding(char *s , char *t)//s 输入 t输出
{
	printf("ins:%s\n",s);
	t = "aaaa1";
	printf("in:%p\n",t);
	printf("int:%s\n",t);
}