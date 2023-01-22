#include<stdio.h>
int main(){
	int dadage,sonage;
	dadage =9*28/3;
	sonage = (dadage - 4) / 2;
	printf("%d,%d\n",dadage,sonage);
	printf("Diophantus was %d years old when his son died.",dadage - 4);
	return 0;
}
/* (1/6+ 1/12 + 1/7)* dadage + 5 + dadage/2  +4 = dadage ;
5  + 2 = (1-1/6-1/12-1/7 - 1/2)* dadage;
*/
