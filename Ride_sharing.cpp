#include <iostream>
#include <string>

using namespace std;
struct loc{
	int x;
	int y;
};
//讀的時候把全部的標籤記下來，定訂次序，讀資料的時候比對、設定對應bool
class Entity{
protected:
	string id;//ID
	bool ison;//是否上線
	bool isser;//是不是在服務中
	loc location;//地點
	bool* attribute;//標籤 bool array
	int time;//上一次更新時間 int
public:
	Entity(string id,bool ison,bool isser,loc location,bool* attribute,int time);
	Entity();
	virtual void print();
};

class car : public Entity{
protected:
	int score;//生涯累積分數
	bool high_level;//高檔車
	char direction;//方向
	int judge_time;//被評分次數
	//基本價、單位里程價
public:
	car();
	car(string id,bool ison,bool isser,loc location,bool*attribute,int time,int score,bool high_level,char direction,int judge_time);
	void print();
};



int main(int argc, char const *argv[])
{
	bool *ptr=0;
	loc C = {1,1};
	Entity* A = new car("name",1,1,C,ptr,10,100,true,'N',10);
	A->print();
	return 0;
}


car::car():Entity(){}
car::car(string id,bool ison,bool isser,loc location,bool*attribute,int time,int score,bool high_level,char direction,int judge_time)
:Entity(id,ison,isser,location,attribute,time),score(score),high_level(high_level),direction(direction),judge_time(judge_time)
{}
Entity::Entity(){}
Entity::Entity(string id,bool ison,bool isser,loc location,bool*attribute,int time)
  : id(id), ison(ison), isser(isser), location(location), attribute(attribute),time(time){}


void Entity::print(){
	// cout << "Entity:\n";
	cout << "ID:" << id << endl;
	cout << "ison" << ison << endl;
	cout << "isser" << isser << endl;
	cout << "location: "<< location.x << " " << location.y << endl; 
}
void car::print(){
	cout << "Car\n";
	Entity::print();
	cout <<"score:" <<  score << endl;
	cout <<"high_level:" << high_level << endl;
	cout <<"direction:" << direction << endl;
	cout <<"judge_time:" << judge_time << endl;
}