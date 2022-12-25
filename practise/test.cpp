#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<cmath>
using namespace std;
stack<int> numbers;
vector<double> all;
int main(){
    string s;
    cin>>s;
    for (int i=0;i<s.size();i++){
        if (s[i] != ',' && s[i] != '.'){
            numbers.push(s[i]-'0');
        }else if(s[i] == '.'){
            double zhengshu = 0.0;
            int beishu = 1;
            while(numbers.size()){
                zhengshu += numbers.top() * beishu;
                beishu *= 10;
                numbers.pop();
            }
            all.push_back(zhengshu);
        }else if(s[i] == ','){
            double xiaoshu = 0.0, beishu = pow(0.1,numbers.size());
            while (numbers.size()){
                xiaoshu += numbers.top() * beishu;
                beishu *= 10;
                numbers.pop();
            }
            all[all.size()-1] += xiaoshu;
        }else {
            continue;
        }
    }
    for (int i=0;i<all.size();i++){
        cout<<all[i]<<" ";
    }
    return 0;
}