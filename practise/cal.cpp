#include<iostream>
#include<stack>
#include<string>
stack<int> s;
using namespace std;
int main(){
    string str;
    cin>>str;
    for (int i=0;i<str.size();i++){
        if (str[i] - '0' <= '9' && str[i] - '0' >= '0'){
            s.push(str[i] - '0');
        }else if (str[i] == '+'){
            int t1 = s.top();
            s.pop();
            int t2 = s.top();
            s.pop();
            s.push(t1+t2);
        }else if (str[i] == '-'){
            int t1 = s.top();
            s.pop();
            int t2 = s.top();
            s.pop();
            s.push(t2-t1);
        }else if (str[i] == '*'){
            int t1 = s.top();
            s.pop();
            int t2 = s.top();
            s.pop();
            s.push(t1*t2);
        }else if (str[i] == '/'){
            int t1 = s.top();
            s.pop();
            int t2 = s.top();
            s.pop();
            s.push(t2/t1);
        }
    }
}