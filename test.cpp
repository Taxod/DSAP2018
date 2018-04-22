#include <iostream>
#include <string>
#include<stdlib.h>
#include <math.h>
using namespace std;
template<typename ItemType>
class Node
{
private:
  ItemType item; //放置物件
  Node<ItemType>* next; //放置指標
public:
  Node();
  Node(const ItemType& anItem);
  Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
  void setItem(const ItemType& anItem);//設定物件
  void setNext(Node<ItemType>* nextNodePtr);//設定指到下一個物件的pointer
  ItemType getItem() const ;//回傳物件
  Node<ItemType>* getNext() const ;//回傳指到下一個物件的pointer
};


template<typename ItemType>
class Bag
{
private:
  Node<ItemType>* headPtr;//指向第一個Node
  int itemCount; //總共有幾個Node
  Node<ItemType>* getPointerTo(const ItemType& target) const; // 傳入item找到指向該item的pointer 
public:
  Bag();//constuctor
  Bag(const Bag<ItemType>& aBag); // Copy constructor
  ~Bag();//destructor            
  int getCurrentSize() const;//回傳有幾個Node
  bool add(const ItemType& newEntry);//新增一個Node到Bag裡
  void clear();//清除所有東西
  Node<ItemType>* get(const ItemType& target);//傳入item回傳指向它的pointer
  Node<ItemType>* get(string target);//傳入名稱回傳指向它的pointer
  Node<ItemType>* getfirstnode(){return headPtr;}//得到指向第一個item的pointer
};


struct loc{//地點structure
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
    int attribute_len;//標籤長度
    int time;//上一次更新時間 int
    int gap;//等待時間間隔
public:
    Entity(string id,int time,int attributeN);
    Entity();
    virtual void print();//印出東西
    string getid(){return id;}//回傳物件的ID
    loc getlocation(){return location;}//回傳物件的位置
    void setlocation(loc c){location = c;}//設定物件位置
    void settime(int time){this->time = time;}//設定時間
    int gettime(){return time;}//回傳時間
    bool* getattribute(){return attribute;}//回傳物件屬性
    bool getser(){return isser;}//回傳是否服務中
    bool geton(){return ison;}//回傳是否上線
    void seton(bool a){ison = a;}//設定物件是否上線
    void setser(bool a){isser = a;}//設定物件是不是在服務中
    void setgap(int t){gap = t;}//設定物件的等待時間
    int getgap(){return gap;}//回傳物件的等待時間
    void setattribute(bool tmp[]){//設定標籤
        for (int i = 0; i < attribute_len; ++i)
        {
            attribute[i] = tmp[i];
        }
    }
};


class Passenger : public Entity
{
private:
    string C_id;//紀錄配對車子的ID
public:
    Passenger();
    Passenger(string id,int time,int attributeN);
    void print();//印出乘客資料
    void setC_id(string C){C_id = C;}//設定配對車子ID
    string getC_id(){return C_id;}//回傳配對車子ID
};

class car : public Entity{
protected:
    int score;//生涯累積分數
    bool high_level;//高檔車
    char direction;//方向
    int judge_time;//被評分次數
    string P;//配對的乘客ID
public:
    car();
    car(string id,int time,bool high_level,int attributeN);
    void print();//印出車子的基本資料
    char getdirection();//回傳車子的方向
    void setdirection(char c);//設定車子的方向
    bool getlevel(){return high_level;}//回傳車子的等級
    string getP(){return P;};//回傳乘客的ID
    void setP(string k){ P = k;};//設定乘客的ID
    void setscore(int s){score = s;}//設定分數
    int getscore(){return score;}//回傳分數
    void setjudge_time(int n){judge_time = n;}//設定評分次數
    int getjudge_time(){return judge_time;}//回傳評分次數
};


int chargetime(string T);//change time to int

car change_car_loc_by_time(car A,int timegap);//change car location by time

int distance(loc A,loc B);//calaulte distance between two location



int main()
{   
    int benefit = 0;//平台總收益

    int max_dis,ar,br,al,bl,k,h,p,attributeN;//系統參數
    cin >> max_dis >> ar >> br >> al >> bl >> k >> h >> p >> attributeN;
    
    string trash;
    getline(cin,trash);


    //切割標籤
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
    
    Bag<car> car_bag;
    Bag<Passenger> Passenger_bag;
    while(getline(cin,s)){

        string T =  s.substr(0,s.find(' ')); // T 時間字串 ex : 00:00
        int time = chargetime(T);//處理時間

        s = s.substr(s.find(' ')+1,string::npos);
        string condition = s.substr(0,2);//事件代號
        s = s.substr(s.find(':')+1,string::npos);
        

        if (condition == "NP")
        {   
            //新增乘客
            string _id = s.substr(0,s.find('('));
            if (car_bag.get(_id) != nullptr)//已經被註冊過
            {
                continue;
            }
            s = s.substr(s.find('(')+1,s.find(')'));
            bool* tmpatt = new bool [attributeN];
            for (int i = 0; i < attributeN; ++i)
            {
                tmpatt[i] = 0;
            }
            //屬性標籤
            while(s.find(',') != string::npos){
                string stmp = s.substr(0,s.find(','));
                s.erase(0,s.find(',')+1);
                for (int i = 0; i < attributeN; ++i)
                {
                    if (stmp == total_attribute[i])
                    {
                        tmpatt[i] = 1;
                        continue;
                    }
                }
            }
            s = s.substr(0,s.find(')'));
            for (int i = 0; i < attributeN; ++i)
                {
                    if (s == total_attribute[i])
                    {
                        tmpatt[i] = 1;
                        continue;
                    }
                }
            Passenger result(_id,time,attributeN);
            result.setattribute(tmpatt);
            result.seton(false);
            result.setser(false);
            Passenger_bag.add(result);//新增乘客
        }else if (condition == "NC")
        {
            //新增車子
            string _id = s.substr(0,s.find('('));
            if (car_bag.get(_id) != nullptr)//不符合新增條件
            {
                continue;
            }
            char level = s.substr(s.find(')')+1,string::npos)[0];
            bool carlevel = 1;
            if (level == 'R')//車子種類
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
                        continue;
                    }
                }
            }
            s = s.substr(0,s.find(')'));
            for (int i = 0; i < attributeN; ++i)
                {
                    if (s == total_attribute[i])
                    {
                        tmpatt[i] = 1;
                        continue;
                    }
                }
            car result(_id,time,carlevel,attributeN);
            result.setattribute(tmpatt);
            result.seton(false);
            result.setser(false);
            car_bag.add(result);//新增一個車子
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
           
            //如果找的到車子、車子原本是離線狀態
            if (car_node_ptr != nullptr && car_node_ptr->getItem().geton() == false)
            {
                car tt(car_node_ptr->getItem());
                tt.setdirection(c);//設定方向
                tt.setlocation(pl);//設定地點
                tt.settime(time);//設定時間
                tt.seton(true);//設定為上線
                tt.setser(false);
                tt.setP("");
                car_node_ptr->setItem(tt);
            }
        }else if (condition == "EC")//空車改變移動方式
        {
            string target = s.substr(0,s.find('('));
            

            Node<car>* car_node_ptr = car_bag.get(target);
            
            //要改變的方向
            char c = s.substr(s.find('(')+1,s.find(')'))[0];
            
            if (car_node_ptr != nullptr && car_node_ptr->getItem().getser() == false && car_node_ptr->getItem().geton() == true)
            {
                int timegap = time - car_node_ptr->getItem().gettime();//時間差
                car tt(change_car_loc_by_time(car_node_ptr->getItem(),timegap));
                tt.setdirection(c);//設定新的方向
                tt.settime(time);//設定新時間
                car_node_ptr->setItem(tt);
                
            }
        }else if (condition == "OP")//乘客上線
        {
            //0987654321(6,10)L
            string target = s.substr(0,s.find('('));
            Node<Passenger>* Passenger_node_ptr = Passenger_bag.get(target);

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

            int max_suit = -1000000;
            Node<car>* first = car_bag.getfirstnode();
            Node<car>* max_suit_car = nullptr;
            if (Passenger_node_ptr != nullptr && Passenger_node_ptr->getItem().geton() == false)
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
                        car tcar(change_car_loc_by_time(first->getItem(),timegap));
                        tcar.settime(time);
                        first->setItem(tcar);
                        
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
                    //變更車子及乘客狀態
                    Passenger tmpP(Passenger_node_ptr->getItem());
                    car tmpcar(max_suit_car->getItem());
                    tmpP.settime(time);
                    tmpP.setlocation(pl);
                    tmpP.setser(false);
                    tmpP.seton(true);
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
            if (car_node_ptr != nullptr && car_node_ptr->getItem().getser() == true)
            {
                car tmpcar = car_node_ptr->getItem();
            if (tmpcar.geton() && tmpcar.getP() != "" && tmpcar.getser() && time >= tmpcar.gettime())
            {
                string wait_passenger = car_node_ptr->getItem().getP();
                Node<Passenger>* Passenger_node_ptr = Passenger_bag.get(wait_passenger);
                Passenger tmpP = Passenger_node_ptr->getItem();
                if (tmpP.getser() == true)
                {
                    continue;
                }
                
                //更新等待時間
                tmpcar.setgap((time - tmpP.gettime()));
                tmpP.setgap((time - tmpP.gettime()));
                //變更車子及乘客狀態
                tmpP.setser(true);
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
            if (tmpcar.geton() && tmpcar.getser() && tmpcar.getP() != "" && tmpcar.getgap() != -1 && time >= tmpcar.gettime())
            {
                int length = distance(pl,tmpcar.getlocation());//車子移動的路徑長
            int drive_time = time - tmpcar.gettime();//開車的時間

            Node<Passenger>* Passenger_node_ptr = Passenger_bag.get(tmpcar.getP());
            Passenger tmpP = Passenger_node_ptr->getItem();
            if (tmpP.getser() == false)
            {
                continue;
            }
            
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
            Node<car>* car_node_ptr = car_bag.get(s);
            if (car_node_ptr!=nullptr && car_node_ptr->getItem().getser() == false)
            {
                car tmpcar(car_node_ptr->getItem());
                tmpcar.settime(time);
                tmpcar.seton(false);
                car_node_ptr->setItem(tmpcar);   
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
            //車子離線、變更狀態
            while(car_node_ptr != nullptr){
                int timegap = time - car_node_ptr->getItem().gettime();
                car tmpcar(change_car_loc_by_time(car_node_ptr->getItem(),timegap));
                tmpcar.settime(time);
                tmpcar.seton(false);
                tmpcar.setser(false);
                tmpcar.setP("");
                tmpcar.setgap(-1);
                car_node_ptr->setItem(tmpcar);
                car_node_ptr = car_node_ptr->getNext();
            }
            //乘客離線、變更狀態
            while(Passenger_node_ptr != nullptr){
                int timegap = time - Passenger_node_ptr->getItem().gettime();
                Passenger tmpP(Passenger_node_ptr->getItem());
                tmpP.settime(time);
                tmpP.seton(false);
                tmpP.setser(false);
                tmpP.setC_id("");
                tmpP.setgap(-1);
                Passenger_node_ptr->setItem(tmpP);
                Passenger_node_ptr = Passenger_node_ptr->getNext();
            }
        }
    }
    return 0;
}
Passenger::Passenger():Entity(){}
Passenger::Passenger(string id,int time,int attributeN)
:Entity(id,time,attributeN)
{
    C_id="";
    gap = -1;
    attribute_len = attributeN;
}


car::car():Entity(){}
car::car(string id,int time,bool high_level,int attributeN)
:Entity(id,time,attributeN),high_level(high_level)
{
    judge_time = 0;
    attribute_len = attributeN;
    direction = 'X';
    score = 0;
    P=""; 
    gap = -1;
}
Entity::Entity(){}
Entity::Entity(string id,int time,int attributeN)
  : id(id),time(time){
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




void car::setdirection(char c){
    direction = c;
}
char car::getdirection(){
    return direction;
}


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












































// -----------------------------------------------------------------------------------------
template <typename ItemType>
Node<ItemType>::Node():next(nullptr){}
template <typename ItemType>
Node<ItemType>::Node(const ItemType& anItem):item(anItem),next(nullptr){}
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
Bag<ItemType>::Bag(const Bag<ItemType>& aBag){
    itemCount = aBag.itemCount;
    Node<ItemType>* origChainPtr = aBag.headPtr;
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
bool Bag<ItemType>::add(const ItemType& newEntry){
    Node<ItemType>* newNodePtr = new Node<ItemType>();
    newNodePtr->setItem(newEntry);
    newNodePtr->setNext(headPtr);
    headPtr = newNodePtr;
    itemCount++; 
    return true;
}


template<typename ItemType>
void Bag<ItemType>::clear(){
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
