#include <iostream>

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
class StackInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool push(const Itemtype& newEntry) = 0;
	virtual bool pop() = 0;
	virtual Itemtype peek() const = 0;
};

class Stack : public StackInterface<Itemtype>
{
private:
	Node<Itemtype>* topPtr;
public:
	Stack();
	~Stack();
	bool isEmpty() const;
	bool push(const Itemtype& newEntry);
	bool pop();
	Itemtype peek() const;
};

template <typename Itemtype>
Stack<Itemtype>::Stack():topPtr(nullptr){}

int main(int argc, char const *argv[])
{
	return 0;
}


//overload item operator=
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