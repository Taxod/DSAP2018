#include <iostream>
#include<string>

using namespace std;


string IntToTime(int n){
    int hour = 0;
    int minute = 0;
    int second = 0;
    string result = "";
    while(n >= 3600){
		hour = n / 3600;
        n %= 3600;
    }
    while(n >=60){
        minute = n / 60;
        n %= 60;
    }
    second = n;
    if (hour == 0)
    {
        result += "00:";
    }else if (hour < 10)
    {
        result += "0";
        result += to_string(hour);
        result +=":";
    }else{
        result += to_string(hour);
        result += ":";
    }
    if (minute == 0)
    {
        result += "00:";
    }else if (minute < 10)
    {
        result += "0";
        result += to_string(minute);
        result +=":";
    }else{
        result += to_string(minute);
        result += ":";
    }
    if (second == 0)
    {
        result += "00";
    }else if (second < 10)
    {
        result += "0";
        result += to_string(second);
//        result +=":";
    }else{
        result += to_string(second);
        // result += ":";
    }
    return result;
}

int TransferTime(string s){
    string hour = s.substr(0,s.find(":"));
    s = s.substr(s.find(":")+1,string::npos);
    string minute = s.substr(0,s.find(":"));
    string second = s.substr(s.find(":")+1,string::npos);
    int result = 60*60*stoi(hour) + 60*stoi(minute) + stoi(second);
    return result;
}





int main(int argc, char const *argv[])
{
    string T = "23:11:00";
    int n =  TransferTime(T);
    cout << n<< endl;
    string s = IntToTime(n);
    cout << s << endl;
    return 0;
}
