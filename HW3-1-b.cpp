#include<iostream>
using namespace std;

class Client{
	int Stock;
	int Bond; 
	int Fund; 
	int Insurance;
};
class Platinum_Client : public Client{
	
};
class High_Level_Client : public Client{
};
class Normal_Client : public Client{
};
int main(){	
	Client* bank[1000];
	return 0;
} 
