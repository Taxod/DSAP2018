#include<iostream>
using namespace std;
//Team has players
class Team{
	player* member;//�bconstructor �̫��V�}�C 
};
class player{};
//Pitcher is a player
class Pitcher :public player{};
//Catcher is a player
class Catcher:public player{};
//Infielder is a player
class Infielder:public player{};
//Outfielder  is a player
class Outfielder:public player{};
int main(){
	return 0;
} 
