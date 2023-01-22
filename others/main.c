#include<stdio.h>
int main()
{
	int all;
	int i,j,k;
	int m,n;
	int temp;
	for(i=10;i<100;i++)
	{
		for(j=100;j<1000;j++)
		{
			k=i*j;
			if(k<10000)
			{
				all=i*10000000+j*10000+k;
				int flag=1;
				int a[10]={0};
				for(m=0;m<9;m++)
				{

					temp=all%10;
					a[temp]++;
					all/=10;
					if(a[temp]>1)
					{
						flag=0;
						break;
					}
				}
				if(flag)
				printf("%d*%d=%d\n",i,j,k);
			 } 
		}
	}
	return 0;
 } 
