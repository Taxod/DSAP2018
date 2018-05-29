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

template<typename Itemtype>
class Bag
{
private:
  Node<Itemtype>* headPtr;
  int itemCount;
  Node<Itemtype>* getPointerTo(const Itemtype& target) const; 
public:
  Bag();
  Bag(const Bag<Itemtype>& aBag); // Copy constructor
  ~Bag();                       
  int getCurrentSize() const;
  bool isEmpty() const;
  bool add(const Itemtype& newEntry);
  bool remove(const Itemtype& anEntry);
  void clear();
  bool contains(const Itemtype& anEntry) const;
  Itemtype get(const Itemtype& target)const;
  Itemtype get(const string target)const;
  // int getFrequencyOf(const Itemtype& anEntry) const;
  // vector<Itemtype> toVector() const;
};

template <typename Itemtype>
Itemtype Bag<Itemtype>::get(const Itemtype& target)const{
	Node<Itemtype>* ptr;
	ptr = getPointerTo(target);
	return ptr->getItem;
}

template <typename Itemtype>
Itemtype Bag<Itemtype>::get(const string target)const{
	bool found = false;
	Node<Itemtype>* tmptr = headPtr;
	while(!found && (tmptr != nullptr)){
		if (target == tmptr->getItem().id)
		{
			found = true;
		}else{
			tmptr = tmptr->getNext();
		}
	}
	return tmptr->getItem();
}

template<typename Itemtype>
Node<Itemtype>* Bag<Itemtype>::getPointerTo(const Itemtype& target) const{
	bool found = false;
	Node<Itemtype>* tmptr = headPtr;
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

template<typename Itemtype>
Bag<Itemtype>::Bag():headPtr(nullptr),itemCount(0){}

template<typename Itemtype>
Bag<Itemtype>::Bag(const Bag<Itemtype>& aBag){//copy--------
	itemCount = aBag.itemCount;
    Node<Itemtype>* origChainPtr = aBag.headPtr;   
    if(origChainPtr == nullptr)
    	headPtr = nullptr;
    else{
    	headPtr = new Node<Itemtype>();
    	headPtr->setItem(origChainPtr->getItem());
    	Node<Itemtype>* newChainPtr = headPtr;
    while(origChainPtr != nullptr)
    {
        origChainPtr = origChainPtr->getNext();
        Itemtype nextItem = origChainPtr->getItem();
        Node<Itemtype>* newNodePtr = new Node<Itemtype>(nextItem);
        newChainPtr->setNext(newNodePtr);
        newChainPtr = newChainPtr->getNext();
    }      
    newChainPtr->setNext(nullptr);
  } 
}

template<typename Itemtype>
int Bag<Itemtype>::getCurrentSize() const{
	return itemCount;
}
template<typename Itemtype>
bool Bag<Itemtype>::isEmpty() const{
	if (itemCount == 0)
	{
		return true;
	}else{
		return false;
	}
}
template<typename Itemtype>
bool Bag<Itemtype>::add(const Itemtype& newEntry){//----copy
	Node<Itemtype>* newNodePtr = new Node<Itemtype>();
    newNodePtr->setItem(newEntry);
    newNodePtr->setNext(headPtr);
    headPtr = newNodePtr;
    itemCount++; 
    return true;
}

template<typename Itemtype>
bool Bag<Itemtype>::remove(const Itemtype& anEntry){
	Node<Itemtype>* entryNodePtr = getPointerTo(anEntry);
  	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
  	if (canRemoveItem)
  	{
    	entryNodePtr->setItem(headPtr->getItem());
    	Node<Itemtype>* nodeToDeletePtr = headPtr;
    	headPtr = headPtr->getNext();
    	delete nodeToDeletePtr;
    	nodeToDeletePtr = nullptr; 
    	itemCount--;
  	} 
	return canRemoveItem;
}

template<typename Itemtype>
void Bag<Itemtype>::clear(){//-----------copy
	Node<Itemtype>* nodeToDeletePtr = headPtr;
  	while (headPtr != nullptr)
    {
    	headPtr = headPtr->getNext();
    	nodeToDeletePtr->setNext(nullptr);
    	delete nodeToDeletePtr;
    	nodeToDeletePtr = headPtr;
    }  
    itemCount = 0;
}

template<typename Itemtype>
bool Bag<Itemtype>::contains(const Itemtype& anEntry) const{
	if (getPointerTo(anEntry) == nullptr)
	{
		return false;
	}else{
		return true;
	}
}
template<typename Itemtype>
Bag<Itemtype>::~Bag(){
	clear();
}


// template<typename Itemtype>
void fii(Bag<int> u){}
int main(int argc, char const *argv[])
{
	Bag<int> oo;
	int k = 1;
	oo.add(k);
	fii(oo);

	return 0;
}