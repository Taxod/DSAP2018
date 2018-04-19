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
};



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
    int attribute_len;
    int time;//上一次更新時間 int
    int gap;
public:
    Entity(string id/*,bool* attribute*/,int time,int attributeN);
    Entity();
    virtual void print(int attributeN);
    string getid(){return id;}
    loc getlocation(){return location;}
    void setlocation(loc c){location = c;}
    void settime(int time){this->time = time;}
    void setison(bool on){ison = on;}
    int gettime(){return time;}
    bool* getattribute(){return attribute;}
    bool getser(){return isser;}
    bool geton(){return ison;}
    void seton(bool a){ison = a;}
    void setser(bool a){isser = a;}
    void setgap(int t){gap = t;}
    int getgap(){return gap;}
};
class Passenger : public Entity
{
private:
    string C_id;
public:
    Passenger();
    Passenger(string id/*,bool *attribute*/,int time,int attributeN);
    Passenger(const Passenger &anPassenger);
    void print(int attributeN);
    void setC_id(string C){C_id = C;}
    string getC_id(){return C_id;}
    // ~passenger();
    
};

class car : public Entity{
protected:
    int score;//生涯累積分數
    bool high_level;//高檔車
    char direction;//方向
    int judge_time;//被評分次數
    string P;
    //基本價、單位里程價
public:
    car();
    car(string id/*,bool*attribute*/,int time,bool high_level,int attributeN);
    car(const car &ancar);
    void print(int attributeN);
    char getdirection();
    void setdirection(char c);
    bool getlevel(){return high_level;}
    string getP(){return P;};
    void setP(string k){ P = k;};
    void setscore(int s){score = s;}
    int getscore(){return score;}
    void setjudge_time(int n){judge_time = n;}
    int getjudge_time(){return judge_time;}
};
void car::setdirection(char c){
    direction = c;
}
char car::getdirection(){
    return direction;
}
int chargetime(string T){
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

car change_car_loc_by_time(car A,int timegap){
    char d = A.getdirection();//原本的方向
    loc tmp = A.getlocation();//原本的位置
    //更新位置
    //車子移動的速度差異R 1/min other 2/min
    int speed = 0;
    if (A.getlevel() == true)
    {
        speed = 2;
    }else{
        speed = 1;
    }
    switch(d){
        case 'N':
            tmp.y += (timegap*speed);
            break;
        case 'S':
            tmp.y -= (timegap*speed);
            break;
        case 'W':
            tmp.x -= (timegap*speed);
            break;
        case 'E':
            tmp.x += (timegap*speed);
            break;
        case 'H':
            break;
    }
    A.setlocation(tmp);
    return A;
}


int distance(loc A,loc B){
    int d = abs(A.x - B.x) + abs(A.y - B.y);
    return d;
}



int main()
{   
    int a = 3;
    Bag<Entity> car_bag;
    car C("123",1,1,a);
    // car_bag.add(C);
    // Node<car>* ptr;
    // ptr = car_bag.get(C.getid());
    // ptr->getItem().print(a); 
    car D(C);
    return 0;
}
Passenger::Passenger(const Passenger &anPassenger){
    this->id = anPassenger.id;
    for (int i = 0; i < attribute_len; ++i)
    {
        this->attribute[i] = anPassenger.attribute[i];
    }
    this->time = anPassenger.time;
    attribute_len = anPassenger.attribute_len;
    this->C_id = anPassenger.C_id;
    this->isser = anPassenger.isser;
    this->ison = anPassenger.ison;
    this->location = anPassenger.location;
    this->gap = anPassenger.gap;
}
Passenger::Passenger():Entity(){}
Passenger::Passenger(string id/*,bool*attribute*/,int time,int attributeN)
:Entity(id/*,attribute*/,time,attributeN)
{
    C_id="";
    gap = -1;
}

car::car(const car &ancar){
    this->id = ancar.id;
    for (int i = 0; i < attribute_len; ++i)
    {
        this->attribute[i] = ancar.attribute[i];
    }
    this->time = ancar.time;
    attribute_len = ancar.attribute_len;
    this->isser = ancar.isser;
    this->ison = ancar.ison;
    this->location = ancar.location;
    score = ancar.score;
    high_level = ancar.high_level;
    direction = ancar.direction;
    judge_time = ancar.judge_time;
    gap = ancar.gap;
    P = ancar.P;
}

car::car():Entity(){}
car::car(string id/*,bool*attribute*/,int time,bool high_level,int attributeN)
:Entity(id/*,attribute*/,time,attributeN),high_level(high_level)
{
    judge_time = 0;
    direction = 'X';
    score = 0;
    P=""; 
    gap = -1;
}
Entity::Entity(){}
Entity::Entity(string id/*,bool*attribute*/,int time,int attributeN)
  : id(id)/*,attribute(attribute)*/,time(time){
    attribute = new bool [attributeN];
    for(int i = 0 ; i < attributeN ; i++){
        attribute[i] = 0;
    }
    attribute_len = attributeN;
    location = {0,0};
    ison = 0;
    isser = 0;
  }
void Passenger::print(int attributeN)
{
    Entity::print(attributeN);
}
void Entity::print(int attributeN){
    cout << "ID:" << id << endl;
    cout << "ison" << ison << endl;
    cout << "isser" << isser << endl;
    cout << "location: "<< location.x << " " << location.y << endl; 
    cout << "time: " << time << endl;
    cout << "attribute: ";
    cout << attributeN << "*\n";
    for (int i = 0; i < attributeN; ++i)
    {
        cout << attribute[i] << " ";
    }cout << endl;
}
void car::print(int attributeN){
    cout << "Car\n";
    Entity::print(attributeN);
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
    bool* tmpatt = new bool [attributeN];//---------------------------------------------------------------
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
    car result(_id,time,carlevel,attributeN);
    return result;

}



Passenger NP_condition(string s,int time,string total_attribute[],int attributeN){
    string _id = s.substr(0,s.find('('));
    s = s.substr(s.find('(')+1,s.find(')'));
    bool* tmpatt = new bool [attributeN];//-----------------------------------------------------
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
    Passenger result(_id,time,attributeN);
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
