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
public:
	bool isEmpty() const;
	bool enqueue(const Itemtype& newEntry);
	bool dequeue();
	Itemtype peekFront() const;
	queue();//-------------------------------------------------------
	~queue();//------------------------------------------------------
};

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
private:
	static const int ROOT_INDEX = 0;
	static const int DEFAULT_CAPACITY = 21;
	Itemtype* items;
	int itemCnt;
	int maxItem;//需要注意大小變更-------------------------------------------
	void heapRebuild(int rootIndex,Itemtype* items,int itemCnt);
	void swap(int a,int b);
public:
	Heap();//-------------------------------------------------
	~Heap();//------------------------------------------

	bool isEmpty () const;
	int getNumberOfNodes () const;
	// int getHeight () const;
	Itemtype peekTop () const;
	bool add( const Itemtype & newData );
	bool remove();
	void clear();	
};

template <typename Itemtype>
class PriorityQueue : private Heap<Itemtype>
{
public:
	PriorityQueue();//--------------------------------
	~PriorityQueue();//-------------------------------
	bool isEmpty() const ;
	bool add (const Itemtype& newEntry);
	bool remove();
	Itemtype peek() const throw( logic_error/*PreconViolatedExcep*/);	
};

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
Itemtype PriorityQueue<Itemtype>::peek() const throw( logic_error/*PreconViolatedExcep*/){
	try{
		return Heap<Itemtype>::peekTop();
	}
	catch(/*PreconViolatedExcep */logic_error e){
		throw /*PreconViolatedExcep*/ logic_error("Attemped peek into an empty priority queue.");
	}
}



int TransferTime(string s){
	string hour = s.substr(0,s.find(":"));
	s = s.substr(s.find(":")+1,string::npos);
	string minute = s.substr(0,s.find(":"));
	string second = s.substr(s.find(":")+1,string::npos);
	// int result = 60*60*stoi(hour) + 60*stoi(minute) + second;
	// return result;
	return 0;
}






int main(int argc, char const *argv[])
{
	string test = "00:05:10";
	// int h = TransferTime(test);
	return 0;
}



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
	items[b] = items[a];
}
template <typename Itemtype>
void Heap<Itemtype>::heapRebuild(int rootIndex,Itemtype* items,int itemCnt){
	if (rootIndex*2+2 < itemCnt || rootIndex*2+1 < itemCnt)
	{
		int largeChildIndex = 2 * rootIndex + 1;
		if (rootIndex*2+2 < itemCnt)
		{
			int rightchildindex = largeChildIndex + 1;
			if (items[rightchildindex] > items[largeChildIndex])//operatoroverloading---------------
			{
				largeChildIndex = rightchildindex;
			}
			if (items[rootIndex] < items[largeChildIndex])
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
	int result = 0;
	items[itemCnt] = newData;
	int newDataIndex = itemCnt;
	bool inplace = false;
	while((newDataIndex > 0) and !inplace){
		int parentIndex = (newDataIndex-1) / 2;
		if (items[newDataIndex] <= items[parentIndex])
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