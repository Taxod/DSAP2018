#include<iostream>
using namespace std;
int N = 100;
//Client has Platinum Client, High level Client, Normal Client
class Client{};
//Bank has Clients
class Bank{
	Client* c;//�bconstructor �̫��V�}�C
};
//Financial_instrument has stock, Bond, Fund, Insurance
class Financial_instrument{};
//stock is a Financial_instrument
class stock : public Financial_instrument{};
//Bond is a Financial_instrument 
class Bond : public Financial_instrument{};
//Fund is a Financial_instrument
class Fund : public Financial_instrument{};
//Insurance is a Financial_instrument
class Insurance : public Financial_instrument{};
//Platinum_Client has Financial_instruments
class Platinum_Client : public Client{
	Financial_instrument* P;//�bconstructor �̫��V�}�C
};
//High_Level_Client has Financial_instruments
class High_Level_Client : public Client{
	Financial_instrument* P;//�bconstructor �̫��V�}�C
	};
//Noraml_Client has Financial_instruments
class Normal_Client : public Client{
	Financial_instrument* P;//�bconstructor �̫��V�}�C
	};
int main(){	
	return 0;
} 
