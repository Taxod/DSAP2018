#include<iostream>
using namespace std;
int N = 100;
class Client{};
class Bank{
	private:
	Client* c;//construtor���V�}�C 
	public:
	virtual check();
};
class Financial_instrument{};
class stock : public Financial_instrument{};
class Bond : public Financial_instrument{};
class Fund : public Financial_instrument{};
class Insurance : public Financial_instrument{};
class Platinum_Client : public Client{
	private:
	Financial_instrument* P;//construtor���V�}�C
	public:
		check();
};
class High_Level_Client : public Client{
	private:
	Financial_instrument* P;//construtor���V�}�C
	public:
		check();
	};
class Normal_Client : public Client{
	private:
	Financial_instrument* P;//construtor���V�}�C
	public:
		check();
	};
int main(){	
	return 0;
} 
