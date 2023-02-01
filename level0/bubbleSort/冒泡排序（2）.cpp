#include<iostream>
using namespace std;
int a[10005];
int main(){
	freopen("algor.in","r",stdin);
	int n;
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>a[i];
	}
	for (int i=0;i<n;i++){
		bool swap = false;
		for (int j=0;j<n-i-1;j++){
			if (a[j+1]<a[j]){
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				swap = true;
				for (int i=0;i<n;i++){
					cout<<a[i]<<" ";
				}
				cout<<endl; 
			}
		}
		cout<<endl;
		if (!swap) break;
	}
	for (int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
