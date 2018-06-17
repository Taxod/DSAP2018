#include <iostream>
#include <string>
#include<exception>
using namespace std;
template<typename Itemtype>
class Node
{
private:
  Itemtype item;
  Node<Itemtype>* next; 
public:
  Node();
  Node(const Itemtype& anItem);
  Node(const Itemtype& anItem, Node<Itemtype>* nextNodePtr);
  void setItem(const Itemtype& anItem);
  void setNext(Node<Itemtype>* nextNodePtr);
  Itemtype getItem() const ;
  Node<Itemtype>* getNext() const ;
};

template <typename Itemtype>
class queueInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool enqueue(const Itemtype& newEntry) = 0;
	virtual bool dequeue() = 0;
	virtual Itemtype peekFront() const = 0;
};

template <typename Itemtype>
class queue : public queueInterface<Itemtype>
{
private:
	Node<Itemtype>* backPtr;
	Node<Itemtype>* frontPtr;
	int queuecnt;
public:
	bool isEmpty() const;
	bool enqueue(const Itemtype& newEntry);
	bool dequeue();
	Itemtype peekFront() const;
	int getcnt(){return queuecnt;}
	queue();
	~queue();
	queue(const queue<Itemtype>& q);//copy constructor
};
template <typename Itemtype>
queue<Itemtype>::~queue(){
	while(!isEmpty()){
		this->dequeue();
	}
}

template <typename Itemtype>
queue<Itemtype>::queue(const queue<Itemtype>& q){//!*
	while(!this->isEmpty()){
		this->dequeue();
	}
	while(!q.isEmpty()){
		this->enqueue(q.peekFront());
		q.dequeue();
	}
}
template <typename Itemtype>
queue<Itemtype>::queue(){
	backPtr = nullptr;
	frontPtr = nullptr;
	queuecnt = 0;
}

template <typename Itemtype>
class HeapInterface
{
public:
	virtual bool isEmpty () const = 0;
	virtual int getNumberOfNodes () const = 0;
	// virtual int getHeight () const = 0;
	virtual Itemtype peekTop () const = 0;
	virtual bool add( const Itemtype & newData ) = 0;
	virtual bool remove() = 0;
	virtual void clear() = 0;
};

template <typename Itemtype>
class Heap :public HeapInterface<Itemtype>
{
protected:
	static const int ROOT_INDEX = 0;
	static const int DEFAULT_CAPACITY = 21;
	Itemtype* items;
	int itemCnt;
	int maxItem;//需要注意大小變更-------------------------------------------
	void heapRebuild(int rootIndex,Itemtype* items,int itemCnt);
	void swap(int a,int b);
public:
	Heap();
	Heap(const Heap<Itemtype>& H);
	~Heap();
	bool isEmpty () const;
	int getNumberOfNodes () const;
	// int getHeight () const;
	Itemtype peekTop () const;
	bool add( const Itemtype & newData );
	bool remove();
	void clear();	
};
template <typename Itemtype>
Heap<Itemtype>::Heap(const Heap<Itemtype> &H){
	while(!this->isEmpty()){
		this->remove();
	}
	delete items;
	this -> maxItem = H.maxItem;
	items = new Itemtype [maxItem];
	for (int i = 0; i < H.itemCnt; ++i)
	{
		this->items[i] = H.items[i];
	}
	this->itemCnt = H.itemCnt;
}
template <typename Itemtype>
Heap<Itemtype>::~Heap(){
	while(!isEmpty()){
		this->remove();
	}
}
template <typename Itemtype>
Heap<Itemtype>::Heap(){
	itemCnt = 0;
	items = new Itemtype [DEFAULT_CAPACITY];
	maxItem = DEFAULT_CAPACITY;
}

template <typename Itemtype>
class PriorityQueue : public Heap<Itemtype>
{
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue<Itemtype> &P);//!*
	~PriorityQueue();
	bool isEmpty() const ;
	bool add (const Itemtype& newEntry);
	bool remove();
	Itemtype peek() const;	
};
template <typename Itemtype>
PriorityQueue<Itemtype>::PriorityQueue(const PriorityQueue<Itemtype> & P){
	while(!this->isEmpty()){
		this->remove();
	}
	delete this->items;
	this -> maxItem = P.maxItem;
	this->items = new Itemtype [this->maxItem];
	for (int i = 0; i < P.itemCnt; ++i)
	{
		this->items[i] = P.items[i];
	}
	this->itemCnt = P.itemCnt;
}
template <typename Itemtype>
PriorityQueue<Itemtype>::~PriorityQueue(){
	while(!isEmpty()){
		this->remove();
	}
}
template <typename Itemtype>
PriorityQueue<Itemtype>::PriorityQueue(){
	// Heap<Itemtype>::Heap();!*
}



int TransferTime(string s){
	string hour = s.substr(0,s.find(":"));
	s = s.substr(s.find(":")+1,string::npos);
	string minute = s.substr(0,s.find(":"));
	string second = s.substr(s.find(":")+1,string::npos);
	int result = 60*60*stoi(hour) + 60*stoi(minute) + stoi(second);
	return result;
}
class Event
{
private:
	string ID;
	int starttime;
	int endtime;
	char car;//N:non-reserved S:standard B:business
	bool inser;
	bool finished;
	char Eventtype;
	int period_time;
	int changed;
public:
	Event();
	Event(string ID,int starttime,char Eventtype);
	Event(string ID,int starttime,char Eventtype,int changed);
	Event(string ID,int starttime,char Eventtype,int period_time,char car);
	Event(const Event& P);
	bool operator==(const Event &P);
	bool operator>(const Event &E);
	bool operator<(const Event &E);
	bool operator<=(const Event &E);
	bool operator>=(const Event &E);
	int gettime(){return starttime;}
	char getevent(){return Eventtype;}
	char getcarclass(){return car;}
	void setser(bool ser){inser = ser;}
	void setendtime(int end){endtime = end;}
	void setevent(char e){Eventtype = e;}
	void print(){cout << ID << ":" << Eventtype << endl;}
	int getperiod(){return period_time;}
	// ~Event();
};
bool Event::operator>=(const Event &E){
	if(this->starttime >= E.starttime)
		return true;
	else
		return false;
}
bool Event::operator<=(const Event &E){
	if(this->starttime <= E.starttime)
		return true;
	else
		return false;
}
bool Event::operator>(const Event& E){
	if (this->starttime > E.starttime)
		return true;
	else
		return false;
}
bool Event::operator<(const Event&E){
	if (this->starttime < E.starttime)
	{
		return true;
	}else{
		return false;
	}
}
bool Event::operator==(const Event& P){
	if (this->ID == P.ID)
	{
		return true;
	}else{
		return false;
	}
}
Event::Event(){
	starttime = 0;
	endtime = 0;
	ID = "";
	car = 'A';
	inser = false;
	finished = false;
	Eventtype = 'A';
	period_time = 0;
	changed = 0;
}
Event::Event(string ID,int starttime,char Eventtype,int period_time,char car):ID(ID),starttime(starttime),Eventtype(Eventtype),period_time(period_time),car(car){
	endtime = 0;
	inser = false;
	finished = false;
	changed = 0;
}
Event::Event(string ID,int starttime,char Eventtype):ID(ID),starttime(starttime),Eventtype(Eventtype){
	endtime = 0;
	inser = false;
	finished = false;
	car = 'A';
	period_time = 0;
	changed = 0;
}
Event::Event(string ID,int starttime,char Eventtype,int changed):ID(ID),starttime(starttime),Eventtype(Eventtype),changed(changed){
	endtime = 0;
	inser = false;
	finished = false;
	car = 'A';
	period_time = 0;
}
Event::Event(const Event& P){
	this->ID = P.ID;
	this->starttime = P.starttime;
	this -> endtime = P.endtime;
	this->car = P.car;
	this -> inser = P.inser;
	this->finished = P.finished;
	this->Eventtype = P.Eventtype;
	this->period_time = P.period_time;
}



int main(int argc, char const *argv[])
{
	// string test = "00:05:10";
	PriorityQueue<Event> eventlist;
	int standard_car,business_car;
	cin >> standard_car >> business_car;
	int toatal_car = standard_car + business_car;
	bool* is_business_car_queues = new bool [(standard_car+business_car)];
	for (int i = 0; i < (business_car+standard_car); ++i)
	{
		if (i < business_car)
		{
			is_business_car_queues[i] = true;
		}else{
			is_business_car_queues[i] = false;
		}
	}
	queue<Event>* ticket_counter = new queue<Event> [(business_car+standard_car)];
	bool* teller_isser = new bool [(business_car+standard_car)];
	for (int i = 0; i < (business_car+standard_car); ++i)
	{
		teller_isser[i] = 0;
	}
	
	string trash = "";
	getline(cin,trash);
	
	string s;
	
	while(!getline(cin,s).eof()){
		int time = TransferTime(s.substr(0,s.find(" ")));
		s = s.substr(s.find(" ")+1,string::npos);
		
		char event = s.substr(0,s.find(" "))[0];
		s = s.substr(s.find(" ")+1,string::npos);

		string Event_ID = "";
		char carclass = 0;
		int period = 0;
		int changed_line = 0;
		
		if (event == 'A')
		{
			Event_ID = s.substr(0,s.find(" "));
			s = s.substr(s.find(" ")+1,string::npos);
			carclass = s.substr(0,s.find(" "))[0];
			period = stoi(s.substr(s.find(" ")+1,string::npos));
			Event E(Event_ID,time,'A',period,carclass);
			eventlist.add(E);
			// cout << Event_ID << ":" << carclass << ":" << peroid;
			// cout << 'A' << endl;
		}else if (event == 'D')
		{
			Event_ID = s;
			Event E(Event_ID,time,'D');
			eventlist.add(E);
			// cout << Event_ID << ":" << endl;
			// cout << 'D' << endl;
		}else{
			Event_ID = s.substr(0,s.find(" "));
			changed_line = stoi(s.substr(s.find(" ")+1,string::npos));
			Event E(Event_ID,time,'Q',changed_line);
			eventlist.add(E);
			// cout << Event_ID << ":" << changed_line << "\n";
			// cout << 'Q' << endl;
		}
	}

	while(!eventlist.isEmpty()){
		Event tmp(eventlist.peek());
		int currenttime = tmp.gettime();

		if (tmp.getevent() == 'A')
		{
			if (tmp.getcarclass() == 'B')
			{
				int minwait = ticket_counter[0].getcnt();
				int minindex = 0;
				bool finished_ = false;
				for (int i = 0; i < toatal_car; ++i)
				{
					if (ticket_counter[i].isEmpty() && !teller_isser[i])
					{
						eventlist.remove();
						int departtime = currenttime + tmp.getperiod();
						Event depart(tmp);//----
						depart.setser(true);
						depart.setendtime(departtime);
						depart.setevent('D');
						eventlist.add(depart);
						teller_isser[i] = true;
						finished_ = true;
						break;
					}else{
						if (ticket_counter[i].getcnt() < minwait)
						{
							minindex = i;
						}
					}
				}
				if (!finished_)
				{
					eventlist.remove();
					ticket_counter[minindex].enqueue(tmp);
					finished_ = true;
				}
			}else{
				int minwait = ticket_counter[business_car].getcnt();
				int minindex = business_car;
				bool finished_ = false;
				for (int i = 0; i < toatal_car; ++i)
				{
					if (ticket_counter[i].isEmpty() && !teller_isser[i] && !is_business_car_queues[i])
					{
						eventlist.remove();
						int departtime = currenttime + tmp.getperiod();
						Event depart(tmp);//----
						depart.setser(true);
						depart.setendtime(departtime);
						depart.setevent('D');
						eventlist.add(depart);
						teller_isser[i] = true;
						finished_ = true;
						break;
					}else{
						if (ticket_counter[i].getcnt() < minwait)
						{
							minindex = i;
						}
					}
				}
				if (!finished_)
				{
					eventlist.remove();
					ticket_counter[minindex].enqueue(tmp);
					finished_ = true;
				}
			}
		}else if (tmp.getevent() == 'D')
		{
			/* code */
					eventlist.remove();
		}else{

					eventlist.remove();
		}

		// eventlist.peek().print();
		// eventlist.remove();
	}



	return 0;
}























//priortyqueue-----------------------------------------

template <typename Itemtype>
bool PriorityQueue<Itemtype>::isEmpty() const{
	return Heap<Itemtype>::isEmpty();
}

template <typename Itemtype>
bool PriorityQueue<Itemtype>::add(const Itemtype& newEntry){
	return Heap<Itemtype>::add(newEntry);
}

template <typename Itemtype>
bool PriorityQueue<Itemtype>::remove(){
	return Heap<Itemtype>::remove();
}

template <typename Itemtype>
Itemtype PriorityQueue<Itemtype>::peek() const{
	return Heap<Itemtype>::peekTop();
}
//-----------------------------------------------------


//queue-------------------------------------------------
template <typename Itemtype>
Itemtype queue<Itemtype>::peekFront() const{
	return frontPtr->getItem();
}
template <typename Itemtype>
bool queue<Itemtype>::isEmpty() const{
	if (frontPtr == nullptr)
	{
		return true;
	}else{
		return false;
	}
}
template <typename Itemtype>
bool queue<Itemtype>::enqueue(const Itemtype& newEntry){
	Node<Itemtype>* newNodePtr = new Node<Itemtype>(newEntry);
	if(isEmpty()){
		frontPtr = newNodePtr;
	}else{
		backPtr->setNext(newNodePtr);
	}
	backPtr = newNodePtr;
	queuecnt++;
	return true;
}
template <typename Itemtype>
bool queue<Itemtype>::dequeue(){
	bool result = false;
	if (!isEmpty())
	{
		Node<Itemtype>* nodeToDeletePtr = frontPtr;
		if (frontPtr == backPtr)
		{
			frontPtr = nullptr;
			backPtr = nullptr;
		}else{
			frontPtr = frontPtr->getNext();
		}
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		result = true;
	}
	queuecnt--;
	return result;
}
//-------------------------------------------


//Node----------------------------------------

template <typename Itemtype>
Node<Itemtype>::Node():next(nullptr){}
template <typename Itemtype>
Node<Itemtype>::Node(const Itemtype& anItem):item(anItem),next(nullptr){
	//overload assignment operator，constructor
}
template <typename Itemtype>
Node<Itemtype>::Node(const Itemtype& anItem, Node<Itemtype>* nextNodePtr):next(nextNodePtr),item(anItem){}
template<class Itemtype>
void Node<Itemtype>::setItem(const Itemtype& anItem)
{
  item = anItem;
} 

template<typename Itemtype>
void Node<Itemtype>::setNext(Node<Itemtype>* nextNodePtr)
{
  next = nextNodePtr;
} 

template<typename Itemtype>
Itemtype Node<Itemtype>::getItem() const
{
  return item;
} 

template<typename Itemtype>
Node<Itemtype>* Node<Itemtype>::getNext() const
{
  return next;
} 
//-------------------------------------------------------------






















//Heap--------------------------------------------------------------------


template <typename Itemtype>
void Heap<Itemtype>::swap(int a,int b){
	Itemtype tmp;
	tmp = items[a];
	items[a] = items[b];
	items[b] = tmp;
}
template <typename Itemtype>
void Heap<Itemtype>::heapRebuild(int rootIndex,Itemtype* items,int itemCnt){
	if (rootIndex*2+2 < itemCnt || rootIndex*2+1 < itemCnt)
	{
		int largeChildIndex = 2 * rootIndex + 1;
		if (rootIndex*2+2 < itemCnt)
		{
			int rightchildindex = largeChildIndex + 1;
			if (items[rightchildindex] < items[largeChildIndex])//operatoroverloading
			{
				largeChildIndex = rightchildindex;
			}
			if (items[rootIndex] > items[largeChildIndex])
			{
				swap(rootIndex,largeChildIndex);//swap items[rootindex] and items[largeChildIndex]
				heapRebuild(largeChildIndex,items,itemCnt);
			}
		}
	}
}


template <typename Itemtype>
bool Heap<Itemtype>::remove(){
	bool result = false;
	items[0] = items[itemCnt-1];
	itemCnt--;
	heapRebuild(0,items,itemCnt);
	return true;
}


template <typename Itemtype>
bool Heap<Itemtype>::add(const Itemtype& newData){
	if (itemCnt + 1 >= maxItem)
	{
		Itemtype* tmp = items;
		delete items;
		items = new Itemtype [maxItem*2];
		maxItem*=2;
		for (int i = 0; i < itemCnt; ++i)
		{
			items[i] = tmp[i];
		}
	}//!*
	items[itemCnt] = newData;
	int newDataIndex = itemCnt;
	bool inplace = false;
	while((newDataIndex > 0) and !inplace){
		int parentIndex = (newDataIndex-1) / 2;
		if (items[newDataIndex] >= items[parentIndex])
		{
			inplace = true;
		}else{
			swap(newDataIndex,parentIndex);
			newDataIndex = parentIndex;
		}
	}
	itemCnt++;
	return true;
}


/*
template <typename Itemtype>
int Heap<Itemtype>::getHeight()const{
	int result = 0;
	return result;
}*/


template <typename Itemtype>
void Heap<Itemtype>::clear(){
	delete [] items;
	items = nullptr;
	itemCnt = 0;
	//可能出錯--------------------------
}


template <typename Itemtype>
Itemtype Heap<Itemtype>::peekTop()const{
	return items[0];
}



template <typename Itemtype>
int Heap<Itemtype>::getNumberOfNodes()const{
	return itemCnt;
}


template <typename Itemtype>
bool Heap<Itemtype>::isEmpty()const{
	if (itemCnt == 0)
	{
		return true;
	}else{
		return false;
	}
}


//----------------------------------------------------------
