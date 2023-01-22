#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
string code(string str){
    for (int i=0;i<str.size();i++){
            str[i] = (str[i] + 1) % 26;
    }
    return str;
}
string decode(string str){
    for (int i=0;i<str.size();i++){
            str[i] -= 1;
            if (str[i] < 0) str[i] += 26;
    }
    return str;
}
int main(){
    string s;
    cin>>s;
    printf("%s\n",code(s));
    printf("%s\n",decode(s));
    return 0;
}