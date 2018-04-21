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
//    virtual Entity(const Entity& anEntity);
    Entity();
    virtual void print();
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
    void setattribute(bool tmp[]){
        for (int i = 0; i < attribute_len; ++i)
        {
            attribute[i] = tmp[i];
        }
    }
};
class Passenger : public Entity
{
private:
    string C_id;
public:
    Passenger();
    Passenger(string id/*,bool *attribute*/,int time,int attributeN);
    // Passenger(const Passenger &anPassenger);
    void print();
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
    // car(const car &ancar);
    void print();
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
    // cout << tmp.x << " " << tmp.y << ";" << d << endl;
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
    // cout << "distance: " << A.x <<":" << A.y << " || " << B.x <<":"<< B.y<<endl;
    int d = abs(A.x - B.x) + abs(A.y - B.y);
    return d;
}



int main()
{   
    int benefit = 0;
    int max_dis,ar,br,al,bl,k,h,p,attributeN;
    cin >> max_dis >> ar >> br >> al >> bl >> k >> h >> p >> attributeN;
    string trash;
    getline(cin,trash);
    string tmp_a;
    string* total_attribute = new string [attributeN];
    getline(cin,tmp_a);
    if(attributeN != 0){
    	for (int i = 0; i < attributeN-1; ++i)
    {
        string atmp = tmp_a.substr(0,tmp_a.find(';'));
        tmp_a.erase(0,tmp_a.find(';')+1);
        total_attribute[i] = atmp;  
    }
    total_attribute[attributeN-1] = tmp_a;	
	}
	

    string s;
    /*
10 50 2 80 3 4 10 1 4
love programming;hate programming;love baseball;enjoy chatting
00:01 NP:0987654321(love baseball,enjoy chatting,hate programming)
00:08 SC:AAA111
00:08 NC:LLL111()L
00:08 NC:AAA111(love baseball)R
00:10 NC:BBB111(hate programming,enjoy chatting)R
00:12 OC:AAA111(1,5)N
00:13 OC:BBB111(5,8)N
00:13 OC:LLL111(6,10)H
00:19 EC:AAA111(E)
00:23 LC:LLL111
00:23 OP:0987654321(6,10)L
00:24 OP:0987654321(6,10)R
00:30 CP:BBB111
00:42 SR
00:42 AD:BBB111(6,14)S
00:42 SR
00:45 LC:AAA111
00:49 SC:AAA111
00:50 SC:BBB111
00:51 SC:CCC111
00:52 SP:0988123456
00:53 NP:0999888777()
00:53 OC:LLL111(20,20)H
00:53 OP:0999888777(20,20)L
00:53 CP:LLL111
00:55 ZZ
00:56 SC:BBB111
00:57 OC:AAA111(9,8)S
00:57 SR

    */
    Bag<car> car_bag;
    Bag<Passenger> Passenger_bag;
    while(getline(cin,s)){
        string T =  s.substr(0,s.find(' ')); // T 時間字串 ex : 00:00
        
        int time = chargetime(T);
        //處理時間

        s = s.substr(s.find(' ')+1,string::npos);
        // string condition = s.substr(0,s.find(':'));
        string condition = s.substr(0,2);
        // cout << condition << "*\n";
        s = s.substr(s.find(':')+1,string::npos);
        

        if (condition == "NP")
        {   
            //新增乘客
            Passenger_bag.add(NP_condition(s,time,total_attribute,attributeN));
        }else if (condition == "NC")
        {
            //新增車子
            car_bag.add(NC_condition(s,time,total_attribute,attributeN));
        }else if (condition == "OC")
        {
            //車子上線
            string target = s.substr(0,s.find('('));
           
            Node<car>* car_node_ptr = car_bag.get(target);
            //車子上線地點
            loc pl;
            pl.x = stoi(s.substr(s.find('(')+1,s.find(',')));
            pl.y = stoi(s.substr(s.find(',')+1,s.find(')')));
           
            //車子行駛方向
            char c = s.substr(s.find(')')+1,string::npos)[0];
           
            //如果找的到車子
            if (car_node_ptr != nullptr)
            {
                car tt(car_node_ptr->getItem());
                // cout << "setdirection: " << c << endl;
                tt.setdirection(c);//設定方向
                tt.setlocation(pl);//設定地點
                tt.settime(time);//設定時間
                tt.setison(true);//設定為上線
                tt.setser(false);
                car_node_ptr->setItem(tt);
            }
        }else if (condition == "EC")//空車改變移動方式
        {
            string target = s.substr(0,s.find('('));
            

            Node<car>* car_node_ptr = car_bag.get(target);
            
            //要改變的方向
            char c = s.substr(s.find('(')+1,s.find(')'))[0];
            
            if (car_node_ptr != nullptr)
            {
                car tt = car_node_ptr->getItem();
                
                int timegap = time - tt.gettime();//時間差
                tt = change_car_loc_by_time(tt,timegap);
                tt.setdirection(c);//設定新的方向
                tt.settime(time);//設定新時間
                car_node_ptr->setItem(tt);
            }
        }else if (condition == "OP")//乘客上線
        {
            //0987654321(6,10)L
            string target = s.substr(0,s.find('('));
            Node<Passenger>* Passenger_node_ptr = Passenger_bag.get(target);
			//更新送達目的地乘客ID刪除--------------------------------------------------

            loc pl;
            pl.x = stoi(s.substr(s.find('(')+1,s.find(',')));
            pl.y = stoi(s.substr(s.find(',')+1,s.find(')')));
            
            //車子等級
            char le = s.substr(s.find(')')+1,string::npos)[0];
            bool need_car_level = 0;
            if (le != 'R')
            {
                need_car_level = 1;
            }

            int max_suit = -100;
            Node<car>* first = car_bag.getfirstnode();
            Node<car>* max_suit_car = nullptr;
            if (Passenger_node_ptr != nullptr)
            {
                //從第一輛車開始檢查
				while(first!=nullptr)
                {
                    if (first->getItem().geton() == false || first->getItem().getser() == true)
                    {
                        first = first->getNext();
                        continue;
                    }
            
                    if (first->getItem().getlevel() == need_car_level)
                    {
                        //refresh car location
                        int timegap = time - first->getItem().gettime();
                        first->setItem(change_car_loc_by_time(first->getItem(),timegap));
                        int dis = distance(pl,first->getItem().getlocation());
                        if (dis <= max_dis)
                        {
                            int atricnt = 0;//相同的屬性個數
                            for (int i = 0; i < attributeN; ++i)
                            {
                                if ((first->getItem().getattribute())[i] && (Passenger_node_ptr->getItem().getattribute())[i])
                                {
                                    atricnt ++;
                                }
                            }
                            //適配度計算
                            int suit_num = first->getItem().getscore() - k*first->getItem().getjudge_time() + h*atricnt - p * dis; 
                            if (suit_num > max_suit)
                            {
                                max_suit = suit_num;
                                max_suit_car = first;
                            }
                        }
                    }
                    first = first->getNext();
                }
                if (max_suit_car != nullptr)
                {
                    // cout << "OP succes!!\n";
                    Passenger tmpP(Passenger_node_ptr->getItem());
                    car tmpcar(max_suit_car->getItem());
                    tmpP.settime(time);
                    tmpP.setlocation(pl);
                    tmpP.setser(true);
                    tmpP.setC_id(tmpcar.getid());
                    tmpcar.setser(true);
                    tmpcar.setP(Passenger_node_ptr->getItem().getid());
                    tmpcar.settime(time);
                    Passenger_node_ptr->setItem(tmpP);
                    max_suit_car->setItem(tmpcar);
                }

            }
            
        }else if (condition == "CP")//車子接到乘客
        {
            //BBB111
            Node<car>* car_node_ptr = car_bag.get(s);
            if (car_node_ptr != nullptr)
            {
            	car tmpcar = car_node_ptr->getItem();
            if (tmpcar.geton() && tmpcar.getP() != "" && tmpcar.getser())
            {
            	string wait_passenger = car_node_ptr->getItem().getP();
	            Node<Passenger>* Passenger_node_ptr = Passenger_bag.get(wait_passenger);
	            Passenger tmpP = Passenger_node_ptr->getItem();
	            
	            //更新等待時間
	            tmpcar.setgap((time - tmpP.gettime()));
	            tmpP.setgap((time - tmpP.gettime()));
	            tmpP.settime(time);
	            tmpcar.settime(time);
	            tmpcar.setlocation(tmpP.getlocation());
	            
	            car_node_ptr->setItem(tmpcar);
	            Passenger_node_ptr->setItem(tmpP);
	            }
            }
            
            
        }else if (condition == "AD")//車子載乘客抵達目的地
        {
            //BBB111(6,14)S
            loc pl;
            pl.x = stoi(s.substr(s.find('(')+1,s.find(',')));
            pl.y = stoi(s.substr(s.find(',')+1,s.find(')')));
            string target = s.substr(0,s.find('('));
            
            char c = s.substr(s.find(')')+1,string::npos)[0];
            
            Node<car>* car_node_ptr = car_bag.get(target);
            if (car_node_ptr == nullptr)
            {
            	continue;
            }
            car tmpcar(car_node_ptr->getItem());
            if (tmpcar.geton() && tmpcar.getser() && tmpcar.getP() != "" && tmpcar.getgap() != -1)
            {
            	int length = distance(pl,tmpcar.getlocation());//車子移動的路徑長
            int drive_time = time - tmpcar.gettime();//開車的時間

            Node<Passenger>* Passenger_node_ptr = Passenger_bag.get(tmpcar.getP());
            Passenger tmpP = Passenger_node_ptr->getItem();
            
            tmpP.setlocation(pl);
            tmpcar.setlocation(pl);
            tmpcar.setdirection(c);
            tmpcar.setjudge_time(tmpcar.getjudge_time()+1);
            //車資 、 分數、 被評分次數
            int get_money = 0;
            if (tmpcar.getlevel() == true)//高級車
            {
                if (tmpcar.getgap() > 20 || drive_time > (length/2)*3)
                {
                    get_money = 0;
                }else{
                    get_money = al + bl*length;
                }
            }else{
                if (tmpcar.getgap() > 20 || drive_time > (length)*3)
                {
                    get_money = 0;
                }else{
                    get_money = ar+br*length;
                }
            }
            benefit += get_money;

            int base_score = 4;
            if (tmpcar.getlevel() == true)
            {
                if (tmpcar.getgap() >10 && tmpcar.getgap() <= 20)
                {
                    base_score --;
                }else if (tmpcar.getgap() > 20)
                {
                    base_score -= 2;
                }
                if (drive_time > 2*(length/2) && drive_time <= 3*(length/2))
                {
                    base_score --;
                }else if (drive_time > 3*(length/2))
                {
                    base_score -= 2;
                }
            }else{
                if (tmpcar.getgap() >10 && tmpcar.getgap() <= 20)
                {
                    base_score --;
                }else if (tmpcar.getgap() > 20)
                {
                    base_score -= 2;
                }
                if (drive_time > 2*(length) && drive_time <= 3*(length))
                {
                    base_score --;
                }else if (drive_time > 3*(length))
                {
                    base_score -= 2;
                }
            }
            for (int i = 0; i < attributeN; ++i)
            {
                if (tmpcar.getattribute()[i] && tmpP.getattribute()[i])
                {
                    base_score++;
                }
            }
            if (base_score > 5)
            {
                base_score = 5;
            }else if (base_score < 1)
            {
                base_score = 1;
            }
            tmpcar.setscore(tmpcar.getscore()+base_score);
            tmpcar.settime(time);
            tmpcar.setser(false);
            tmpP.setser(false);
            tmpP.seton(false);
            tmpcar.setgap(-1);
            tmpP.setgap(-1);
            tmpcar.setP("");
            tmpP.setC_id("");
            car_node_ptr->setItem(tmpcar);
            Passenger_node_ptr->setItem(tmpP);
            }
            
        }else if (condition == "LC")//車子離線
        {
            //AAA111
            // Node<car>* first = car_bag.getfirstnode();
            Node<car>* car_node_ptr = car_bag.get(s);
            if (car_node_ptr!=nullptr)
            {
                car tmpcar(car_node_ptr->getItem());
                if (!tmpcar.getser())
                {
                    tmpcar.settime(time);
                    tmpcar.seton(false);
                    car_node_ptr->setItem(tmpcar);
                }   
            }
        }else if (condition == "SC")//查詢車子
        {
            //AAA111
            int status = 0;
            Node<car>* car_node_ptr = car_bag.get(s);

            if (car_node_ptr == nullptr)
            {
                cout << s << ": no registration!\n";
            }else{
                car tmpcar = car_node_ptr->getItem();
                if (tmpcar.geton())
                {
                    status++;
                    int timegap = time - tmpcar.gettime();
                    tmpcar = change_car_loc_by_time(tmpcar,timegap);

                    if (tmpcar.getser())
                    {
                        status++;
                        if (tmpcar.getgap() != -1)
                        {
                            status++;
                        }
                    }
                }
                cout << s <<" "<< status <<" "<<tmpcar.getjudge_time() << " "<< tmpcar.getscore();
                if (status == 1)
                {
                    cout <<" "<< tmpcar.getlocation().x <<" "<< tmpcar.getlocation().y;
                }else if (status == 2 || status == 3)
                {
                    cout << " "<< tmpcar.getP() ;
                }
                cout << endl;
            }
        }else if (condition == "SP")//查詢乘客
        {
            //0987654321
            Node<Passenger>* Passenger_node_ptr = Passenger_bag.get(s);
            if (Passenger_node_ptr == nullptr)
            {
                cout << s << ": no registration!\n"; 
            }else{
                int status = 0;
                if (Passenger_node_ptr->getItem().geton())
                {
                    status++;
                    if (Passenger_node_ptr->getItem().getgap() != -1)
                    {
                        status++;
                    }
                }
                cout << s << " " << status;
                if (status != 0)
                {
                    cout << " " << Passenger_node_ptr->getItem().getC_id();
                }
                cout << endl;
            }
        }else if (condition == "SR")//查詢平台收益
        {
            cout << benefit << endl;
        }else if (condition == "ZZ")//當機
        {   
            // 全部離線
        	Node<car>* car_node_ptr = car_bag.getfirstnode();
        	Node<Passenger>* Passenger_node_ptr = Passenger_bag.getfirstnode();
        	int i = 0;
        	while(car_node_ptr != nullptr){
        		// i++;
        		// cout << i;
        		car tmpcar(car_node_ptr->getItem());
        		tmpcar.seton(false);
        		tmpcar.setser(false);
        		tmpcar.setP("");
        		car_node_ptr->setItem(tmpcar);
        		car_node_ptr = car_node_ptr->getNext();
        	}
        	while(Passenger_node_ptr != nullptr){
        		Passenger tmpP(Passenger_node_ptr->getItem());
        		tmpP.seton(false);
        		tmpP.setser(false);
        		tmpP.setC_id("");
        		Passenger_node_ptr->setItem(tmpP);
        		Passenger_node_ptr = Passenger_node_ptr->getNext();
        	}
        }
    }
    return 0;
}
// Passenger::Passenger(const Passenger &anPassenger){
//  this->id = anPassenger.id;
//  for (int i = 0; i < attribute_len; ++i)
//  {
//      this->attribute[i] = anPassenger.attribute[i];
//  }
//  this->time = anPassenger.time;
//  attribute_len = anPassenger.attribute_len;
//  this->C_id = anPassenger.C_id;
//  this->isser = anPassenger.isser;
//  this->ison = anPassenger.ison;
//  this->location = anPassenger.location;
//  this->gap = anPassenger.gap;
// }
Passenger::Passenger():Entity(){}
Passenger::Passenger(string id/*,bool*attribute*/,int time,int attributeN)
:Entity(id/*,attribute*/,time,attributeN)
{
    C_id="";
    gap = -1;
    attribute_len = attributeN;
}

// car::car(const car &ancar){
//  cout << "here!!";
//  this->id = ancar.id;
//  cout << "1\n";
//  for (int i = 0; i < attribute_len; ++i)
//  {
//      attribute[i] = ancar.attribute[i];
//      cout << "*";
//  }
//  cout << "2\n";
//  this->time = ancar.time;
//  attribute_len = ancar.attribute_len;
//  this->isser = ancar.isser;
//  this->ison = ancar.ison;
//  this->location = ancar.location;
//  cout << "3\n";
//  score = ancar.score;
//     high_level = ancar.high_level;
//     direction = ancar.direction;
//     judge_time = ancar.judge_time;
//     gap = ancar.gap;
//     P = ancar.P;
// }

car::car():Entity(){}
car::car(string id/*,bool*attribute*/,int time,bool high_level,int attributeN)
:Entity(id/*,attribute*/,time,attributeN),high_level(high_level)
{
    judge_time = 0;
    attribute_len = attributeN;
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
void Passenger::print()
{
    Entity::print();
}
void Entity::print(){
    cout << "ID:" << id << endl;
    cout << "ison" << ison << endl;
    cout << "isser" << isser << endl;
    cout << "location: "<< location.x << " " << location.y << endl; 
    cout << "time: " << time << endl;
    cout << "attribute: ";
    // cout << attributeN << "*\n";
    for (int i = 0; i < attribute_len; ++i)
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
    cout << "P: "<< P << endl;
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
                continue;//------------------------------------------------
            }
        }
    }
    s = s.substr(0,s.find(')'));
    for (int i = 0; i < attributeN; ++i)
        {
            if (s == total_attribute[i])
            {
                tmpatt[i] = 1;
                continue;//------------------------------------
            }
        }
    car result(_id,time,carlevel,attributeN);
    result.setattribute(tmpatt);

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
    result.setattribute(tmpatt);
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
