#include <iostream>
#include <string>
#include<stdlib.h>
#include <math.h>
using namespace std;
template<typename ItemType>
class Node
{
private:
  ItemType item;
  Node<ItemType>* next; 
public:
  Node();
  Node(const ItemType& anItem);
  Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
  void setItem(const ItemType& anItem);
  void setNext(Node<ItemType>* nextNodePtr);
  ItemType getItem() const ;
  Node<ItemType>* getNext() const ;
}; 
template<typename ItemType>
class Bag
{
private:
  Node<ItemType>* headPtr;
  int itemCount;
  Node<ItemType>* getPointerTo(const ItemType& target) const; 
public:
  Bag();
  Bag(const Bag<ItemType>& aBag); // Copy constructor
  ~Bag();                       
  int getCurrentSize() const;
  bool isEmpty() const;
  bool add(const ItemType& newEntry);
  bool remove(const ItemType& anEntry);
  void clear();
  bool contains(const ItemType& anEntry) const;
  Node<ItemType>* get(const ItemType& target);
  Node<ItemType>* get(string target);
  Node<ItemType>* getfirstnode(){
  	return headPtr;
  }
  
  // int getFrequencyOf(const ItemType& anEntry) const;
  // vector<ItemType> toVector() const;
};



//using namespace std;
struct loc{
	int x;
	int y;
};

class Entity{
protected:
	string id;//ID
	bool ison;//是否上線
	bool isser;//是不是在服務中
	loc location;//地點
	bool* attribute;//標籤 bool array
	int time;//上一次更新時間 int
public:
	Entity(string id,bool* attribute,int time);
	Entity();
	virtual void print();
	string getid();
	loc getlocation();
	void setlocation(loc c){
		location = c;
	}
	void settime(int time){
		this->time = time;
	}
	void setison(bool on){
		ison = on;
	}
	int gettime(){
		return time;
	}
	bool* getattribute(){return attribute;}
};
loc Entity::getlocation(){
	return location;
}
string Entity::getid(){
	return id;
}
class Passenger : public Entity
{
private:
	// int gap;
public:
	Passenger();
	Passenger(string id,bool *attribute,int time);
	void print();
	// ~passenger();
	
};

class car : public Entity{
protected:
	int score;//生涯累積分數
	bool high_level;//高檔車
	char direction;//方向
	int judge_time;//被評分次數
	string P;
	int gap;
	//基本價、單位里程價
public:
	car();
	car(string id,bool*attribute,int time,bool high_level);
	void print();
	char getdirection();
	void setdirection(char c);
	bool getlevel(){
		return high_level;
	}
	string getP(){return P;};
	int getscore(){return score;}
	int getjudge_time(){return judge_time;}
	void setP(string k){ P = k;};
	void setgap(int t){gap = t;}
	int getgap(){return gap;}
};
void car::setdirection(char c){
	direction = c;
}
char car::getdirection(){
	return direction;
}
int chargetime(string T){
	// int time = 0;
	string tmp = T.substr(0,T.find(':'));
	T = T.substr(T.find(':')+1,string::npos);
	int hour_ten = tmp[0]-'0';
	int hour_one = tmp[1]-'0';
	int hour = hour_ten*10 + hour_one;
	int minute_ten = T[0] - '0';
	int minute_one = T[1] - '0';
	int minute = minute_ten*10 + minute_one;
	int time = hour*60 + minute;
	return time;
}

car NC_condition(string s,int time,string total_attribute[],int attributeN);
Passenger NP_condition(string s,int time,string total_attribute[],int attributeN);
// template<typename ItemType>
void OC_condition(string s,int time,Bag<car> car_bag){
	/*cout << "*\n";
	
*/
}
int distance(loc A,loc B){
	int d = abs(A.x - B.x) + abs(A.y - B.y);
	return d;
}



int main()
{
	int max_dis,ar,br,al,bl,k,h,p,attributeN;
	cin >> max_dis >> ar >> br >> al >> bl >> k >> h >> p >> attributeN;
	string trash;
	getline(cin,trash);
	string tmp_a;
	string* total_attribute = new string [attributeN];
	getline(cin,tmp_a);
	
	for (int i = 0; i < attributeN-1; ++i)
	{
		string atmp = tmp_a.substr(0,tmp_a.find(';'));
    	tmp_a.erase(0,tmp_a.find(';')+1);
    	total_attribute[i] = atmp;	
	}
	total_attribute[attributeN-1] = tmp_a;

	string s;
	/*
	00:01 NC:AAA111(love,enjoy,hate)L
	00:05 NP:0987654321(love,enjoy,hate)
	00:12 OC:AAA111(1,5)N
	00:19 EC:AAA111(E)
	*/
	Bag<car> car_bag;
	Bag<Passenger> Passenger_bag;
	while(getline(cin,s)){
		string T = 	s.substr(0,s.find(' ')); // T 時間字串 ex : 00:00
		int time = chargetime(T);
		s = s.substr(s.find(' ')+1,string::npos);
		string condition = s.substr(0,s.find(':'));
		s = s.substr(s.find(':')+1,string::npos);
		if (condition == "NP")
		{	
			Passenger_bag.add(NP_condition(s,time,total_attribute,attributeN));
		}else if (condition == "NC")
		{
			car_bag.add(NC_condition(s,time,total_attribute,attributeN));
		}else if (condition == "OC")
		{
			string target = s.substr(0,s.find('('));
			Node<car>* car_node_ptr = car_bag.get(target);
			loc pl;
			pl.x = stoi(s.substr(s.find('(')+1,s.find(',')));
			pl.y = stoi(s.substr(s.find(',')+1,s.find(')')));
			char c = s.substr(s.find(')')+1,string::npos)[0];
			if (car_node_ptr != nullptr)
			{
				car tt = car_node_ptr->getItem();
				tt.setdirection(c);
				tt.setlocation(pl);
				tt.settime(time);
				tt.setison(true);
				car_node_ptr->setItem(tt);
			}
			car_node_ptr->getItem().print();
		}else if (condition == "EC")
		{
			string target = s.substr(0,s.find('('));
			Node<car>* car_node_ptr = car_bag.get(target);
			char c = s.substr(s.find('(')+1,s.find(')'))[0];
			if (car_node_ptr != nullptr)
			{
				car tt = car_node_ptr->getItem();
				int timegap = time - tt.gettime();
				char d = tt.getdirection();
				loc tmp = tt.getlocation();
				switch(d){
					case 'N':
						tmp.y += timegap;
						break;
					case 'S':
						tmp.y -= timegap;
						break;
					case 'W':
						tmp.x -= timegap;
						break;
					case 'E':
						tmp.x += timegap;
						break;
					case 'H':
						break;
				}
				tt.setlocation(tmp);
				tt.setdirection(c);
				tt.settime(time);
				car_node_ptr->setItem(tt);
			}
			car_node_ptr->getItem().print();
		}else if (condition == "OP")
		{
			//0987654321(6,10)L
			string target = s.substr(0,s.find('('));
			Node<Passenger>* Passenger_node_ptr = Passenger_bag.get(target);
			// string suit_id;
			loc pl;
			pl.x = stoi(s.substr(s.find('(')+1,s.find(',')));
			pl.y = stoi(s.substr(s.find(',')+1,s.find(')')));
			
			char le = s.substr(s.find(')')+1,string::npos)[0];
			bool need_car_level = 0;
			if (le != 'R')
			{
				need_car_level = 1;
			}
			int max_suit = -100;

			Node<car>* first = car_bag.getfirstnode();
			Node<car>* max_suit_car = first;
			if (Passenger_node_ptr != nullptr)
			{
				for (int i = 0; i < car_bag.getCurrentSize(); ++i)
				{
					if (first->getItem().getlevel() == need_car_level)
					{
						int dis = distance(Passenger_node_ptr->getItem().getlocation(),first->getItem().getlocation());
						if (dis < max_dis)
						{
							int atricnt = 0;
							for (int i = 0; i < attributeN; ++i)
							{
								if ((first->getItem().getattribute())[i] && (Passenger_node_ptr->getItem().getattribute())[i])
								{
									atricnt ++;
								}
							}
							int suit_num = first->getItem().getscore() - k*first->getItem().getjudge_time() + h*atricnt - p * dis; //-------------------------------------------------- 
							//適配度計算
							if (suit_num > max_suit)
							{
								max_suit = suit_num;
								max_suit_car = first;
							}
						}
					}
					first = first->getNext();
				}
				Passenger tmpP(Passenger_node_ptr->getItem());
				tmpP.settime(time);
				tmpP.setlocation(pl);
				car tmpcar(first->getItem());
				tmpcar.setP(Passenger_node_ptr->getItem().getid());
				tmpcar.settime(time);
				//更改狀態------------------------------------NEED
				first->setItem(tmpcar);
			}
			
		}else if (condition == "CP")
		{
			//BBB111
			Node<car>* car_node_ptr = car_bag.get(s);
			car tmpcar = car_node_ptr->getItem();//------------------------NEED copy constructor
			string wait_passenger = car_node_ptr->getItem().getP();
			Node<Passenger>* Passenger_node_ptr = Passenger_bag.get(wait_passenger);
			Passenger tmpP = Passenger_node_ptr->getItem();
			tmpcar.setgap((time - tmpP.gettime()));
			tmpP.settime(time);
			tmpcar.settime(time);
			car_node_ptr->setItem(tmpcar);
			Passenger_node_ptr->setItem(tmpP);
		}else if (condition == "AD")
		{
			//BBB111(6,14)S
			
			
		}else if (condition == "LC")
		{
			
		}else if (condition == "SC")
		{
			
		}else if (condition == "SP")
		{
			
		}else if (condition == "SR")
		{
			
		}else if (condition == "ZZ")
		{	
		}
	}
	return 0;
}

Passenger::Passenger():Entity(){}
Passenger::Passenger(string id,bool*attribute,int time)
:Entity(id,attribute,time)
{}
car::car():Entity(){}
car::car(string id,bool*attribute,int time,bool high_level)
:Entity(id,attribute,time),high_level(high_level)
{
	judge_time = 0;
	direction = 'X';
	score = 0;
	P; 
}
Entity::Entity(){}
Entity::Entity(string id,bool*attribute,int time)
  : id(id),attribute(attribute),time(time){
  	location = {0,0};
  	ison = 0;
  	isser = 0;
  }
void Passenger::print()
{
	Entity::print();
}
void Entity::print(){
	// cout << "Entity:\n";
	cout << "ID:" << id << endl;
	cout << "ison" << ison << endl;
	cout << "isser" << isser << endl;
	cout << "location: "<< location.x << " " << location.y << endl; 
	cout << "time: " << time << endl;
	cout << "attribute: ";
	for (int i = 0; i < 4; ++i)
	{
		cout << attribute[i] << " ";
	}cout << endl;
}
void car::print(){
	cout << "Car\n";
	Entity::print();
	cout <<"score:" <<  score << endl;
	cout <<"high_level:" << high_level << endl;
	cout <<"direction:" << direction << endl;
	cout <<"judge_time:" << judge_time << endl;
	
}


car NC_condition(string s,int time,string total_attribute[],int attributeN){
	string _id = s.substr(0,s.find('('));
	char level = s.substr(s.find(')')+1,string::npos)[0];
	bool carlevel = 1;
	if (level == 'R')
	{
		carlevel = false;
	}
	s = s.substr(s.find('(')+1,s.find(')'));
	bool* tmpatt = new bool [attributeN];
	for (int i = 0; i < attributeN; ++i)
	{
		tmpatt[i] = 0;
	}
    while(s.find(',') != string::npos){
    	string stmp = s.substr(0,s.find(','));
        s.erase(0,s.find(',')+1);
        for (int i = 0; i < attributeN; ++i)
        {
        	if (stmp == total_attribute[i])
        	{
        		tmpatt[i] = 1;
        		break;
        	}
        }
    }
    s = s.substr(0,s.find(')'));
    for (int i = 0; i < attributeN; ++i)
        {
        	if (s == total_attribute[i])
        	{
        		tmpatt[i] = 1;
        	}
        }
    car result(_id,tmpatt,time,carlevel);
    return result;

}



Passenger NP_condition(string s,int time,string total_attribute[],int attributeN){
	string _id = s.substr(0,s.find('('));
	s = s.substr(s.find('(')+1,s.find(')'));
	bool* tmpatt = new bool [attributeN];
	for (int i = 0; i < attributeN; ++i)
	{
		tmpatt[i] = 0;
	}
    while(s.find(',') != string::npos){
    	string stmp = s.substr(0,s.find(','));
        s.erase(0,s.find(',')+1);
        for (int i = 0; i < attributeN; ++i)
        {
        	if (stmp == total_attribute[i])
        	{
        		tmpatt[i] = 1;
        		break;
        	}
        }
    }
    s = s.substr(0,s.find(')'));
    for (int i = 0; i < attributeN; ++i)
        {
        	if (s == total_attribute[i])
        	{
        		tmpatt[i] = 1;
        	}
        }
    Passenger result(_id,tmpatt,time);
    return result;

}




















































































// -----------------------------------------------------------------------------------------
//overload item operator=
template <typename ItemType>
Node<ItemType>::Node():next(nullptr){}
template <typename ItemType>
Node<ItemType>::Node(const ItemType& anItem):item(anItem),next(nullptr){
	//overload assignment operator，constructor
}
template <typename ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr):next(nextNodePtr),item(anItem){}
template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
  item = anItem;
} 

template<typename ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
  next = nextNodePtr;
} 

template<typename ItemType>
ItemType Node<ItemType>::getItem() const
{
  return item;
} 

template<typename ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
  return next;
} 

template<typename ItemType>
Node<ItemType>* Bag<ItemType>::getPointerTo(const ItemType& target) const{
	bool found = false;
	Node<ItemType>* tmptr = headPtr;
	while(!found && (tmptr != nullptr)){
		if (target == tmptr->getItem())
		{
			found = true;
		}else{
			tmptr = tmptr->getNext();
		}
	}
	return tmptr;
}

template<typename ItemType>
Bag<ItemType>::Bag():headPtr(nullptr),itemCount(0){}

template<typename ItemType>
Bag<ItemType>::Bag(const Bag<ItemType>& aBag){//copy--------
	itemCount = aBag.itemCount;//??
    Node<ItemType>* origChainPtr = aBag.headPtr;//??   
    if(origChainPtr == nullptr)
    	headPtr = nullptr;
    else{
    	headPtr = new Node<ItemType>();
    	headPtr->setItem(origChainPtr->getItem());
    	Node<ItemType>* newChainPtr = headPtr;
    while(origChainPtr != nullptr)
    {
        origChainPtr = origChainPtr->getNext();
        ItemType nextItem = origChainPtr->getItem();
        Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
        newChainPtr->setNext(newNodePtr);
        newChainPtr = newChainPtr->getNext();
    }      
    newChainPtr->setNext(nullptr);
  } 
}

template<typename ItemType>
int Bag<ItemType>::getCurrentSize() const{
	return itemCount;
}
template<typename ItemType>
bool Bag<ItemType>::isEmpty() const{
	if (itemCount == 0)
	{
		return true;
	}else{
		return false;
	}
}
template<typename ItemType>
bool Bag<ItemType>::add(const ItemType& newEntry){//----copy
	Node<ItemType>* newNodePtr = new Node<ItemType>();
    newNodePtr->setItem(newEntry);
    newNodePtr->setNext(headPtr);
    headPtr = newNodePtr;
    itemCount++; 
    return true;
}

template<typename ItemType>
bool Bag<ItemType>::remove(const ItemType& anEntry){
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
  	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
  	if (canRemoveItem)
  	{
    	entryNodePtr->setItem(headPtr->getItem());
    	Node<ItemType>* nodeToDeletePtr = headPtr;
    	headPtr = headPtr->getNext();
    	delete nodeToDeletePtr;
    	nodeToDeletePtr = nullptr; 
    	itemCount--;
  	} 
	return canRemoveItem;
}

template<typename ItemType>
void Bag<ItemType>::clear(){//-----------copy
	Node<ItemType>* nodeToDeletePtr = headPtr;
  	while (headPtr != nullptr)
    {
    	headPtr = headPtr->getNext();
    	nodeToDeletePtr->setNext(nullptr);
    	delete nodeToDeletePtr;
    	nodeToDeletePtr = headPtr;
    }  
    itemCount = 0;
}

template<typename ItemType>
bool Bag<ItemType>::contains(const ItemType& anEntry) const{
	if (getPointerTo(anEntry) == nullptr)
	{
		return false;
	}else{
		return true;
	}
}
template<typename ItemType>
Bag<ItemType>::~Bag(){
	clear();
}
template <typename ItemType>
Node<ItemType>* Bag<ItemType>::get(const ItemType& target){
	Node<ItemType>* ptr;
	ptr = getPointerTo(target);
	return ptr;
}

template <typename ItemType>
Node<ItemType>* Bag<ItemType>::get(string target){
	bool found = false;
	Node<ItemType>* tmptr = headPtr;
	while(!found && (tmptr != nullptr)){
		if (target == tmptr->getItem().getid())
		{
			found = true;
		}else{
			tmptr = tmptr->getNext();
		}
	}
	return tmptr;
}
