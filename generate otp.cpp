#include<bits/stdc++.h>
using namespace std;
string generateotp(int len){
    string str="abcdefghijklmnopqrstuvwxyzABCD"
               "EFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int n=str.length();
    string OTP;
    for(int i=1;i<=len;i++){
        OTP.push_back(str[rand()%n]);

    }
    return OTP;
}
int main(){
    srand(time(NULL));
    int len= 6;
    cout<<"your OTP is "<<generateotp(len).c_str();
    return 0;
}