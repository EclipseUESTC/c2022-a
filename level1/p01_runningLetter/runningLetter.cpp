#include<iostream>
#include<string>
#include<ctime>
#include<windows.h>
#include<stdlib.h>
#include<cstdio>
using namespace std;
const int n = 10;
int main(){
	string s;
	cin>>s;
	int pos = 0,dir = 1;
	int len = s.size();
	while(1){
		int i,j;
		for (i=0;i<=pos;i++)
		cout<<" ";
		cout<<s<<endl;
//		for (i=-1;i<=pos;i++)
//		printf("pos = %d",pos);
		Sleep(100);
		system("cls");
		pos += dir;
		if (pos+len >= 120 or pos+len <= 0) dir *= -1;
	}
	return 0;
} 
