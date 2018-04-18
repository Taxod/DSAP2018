#include <iostream>
#include <string>

using namespace std;

struct test
{
    int x ;
    int y;
};
int main(int argc, char const *argv[])
{
    test Q = {1,2};
    cout << Q.x<<Q.y;
    // string T = "123,456,78)9";
    // char level = (T.substr(T.find(')')+1,string::npos))[0];
    // cout << level;
    // // cout << T.find(':');
    // while(T.find(',') != string::npos){
    //     // cout << T.substr(0,T.find(',')) << "*\n";
    //     T.erase(0,T.find(',')+1);
    // }
    // cout << T << "end\n";
    return 0;
}