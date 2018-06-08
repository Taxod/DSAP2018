
#include <iostream>
#include <string>
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
	queue();
	~queue();
};

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
