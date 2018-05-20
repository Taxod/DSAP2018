#include<iostream>
using namespace std;

class player{
	private:
		string name;
		double height;
		double weight;
		int number;
	public:
	virtual print(){
		cout << "name:" << name << endl;
		cout << "height:" << height << endl;
		cout << "weight:" << weight << endl;
		cout << "number:" << number << endl;
	}
};

class Pitcher :public player{
	double ER;//Earned Run
	print(){
		cout << "Earned Run:" << ER << endl;
		player::print();
	}
};

class Catcher:public player{
	double fielding_percentage;
	double Caught_Stealing;
	print(){
		cout << "fielding percentage:" << fielding_percentage << endl;
		cout << "Caught Stealing:" << Caught_Stealing << endl;
		player::print();
	}
};

class Infielder:public player{
	double fielding_percentage;
	print(){
		cout << "fielding percentage:" << fielding_percentage << endl;
		player::print();
	}
};

class Outfielder:public player{
	double fielding_percentage;
	print(){
		cout << "fielding percentage:" << fielding_percentage << endl;
		player::print();
	}
};
class Team{
	public:
		player* t;//constructor«ü¦V°}¦C 
		print();
};

int main(){	
	return 0;
} 
