#include<iostream>
using namespace std;

class Client{
};
class Platinum_Client : public Client{
	int Stock;
	int Bond; 
	int Fund; 
	int Insurance;
};
class High_Level_Client : public Client{
	int Stock;
	int Bond; 
	int Fund; 
	int Insurance;
};
class Normal_Client : public Client{
	int Stock;
	int Bond; 
	int Fund; 
	int Insurance;
};
int main(){
	Client* bank[100];	
	return 0;
} 
