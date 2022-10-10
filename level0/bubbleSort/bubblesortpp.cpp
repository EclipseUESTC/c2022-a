#include<iostream>
using namespace std;
int a[105];
int main(){
    int n;
    cin>>n;
    for (int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for (int i=0;i<n;i++){
        bool swapped = false;
        for (int j=1;j<n;j++){
            if (a[j]<a[j-1]){
                int temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    for (int i=0;i<n;i++)
    cout<<a[i]<<" ";
    return 0;
}