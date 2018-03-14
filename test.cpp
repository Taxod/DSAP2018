#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <fstream>
using namespace std;
int main() {
    int n = 0;
    string find_wr = "";
    cin >> n;
    cin >> find_wr;
    string* dic = new string[n];
    int find_cnt = 0;
    
    transform(find_wr.begin(),find_wr.end(),find_wr.begin(),::tolower);
    
    string filename = "";
    cin >> filename;
    
    ifstream fp;
    fp.open(filename);
    if (fp) {
        cout << "read success";
    }
    for (int i = 0; i < n; i++) {
        fp >> dic[i];
        cout << ";";
        cout << dic[i];
        if (dic[i] == find_wr) {
            find_cnt++;
        }
    }
    fp.close();
    
    cout << find_cnt;
    delete[] dic;
    return 0;
}

/*
5
watermelon
test.txt
*/
