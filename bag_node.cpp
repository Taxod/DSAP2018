#include <iostream>
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
  ItemType get(const ItemType& target)const;
  ItemType get(const string target)const;
  // int getFrequencyOf(const ItemType& anEntry) const;
  // vector<ItemType> toVector() const;
};

template <typename ItemType>
ItemType Bag<ItemType>::get(const ItemType& target)const{
	Node<ItemType>* ptr;
	ptr = getPointerTo(target);
	return ptr->getItem;
}

template <typename ItemType>
ItemType Bag<ItemType>::get(const string target)const{
	bool found = false;
	Node<ItemType>* tmptr = headPtr;
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


// template<typename ItemType>
void fii(Bag<int> u){}
int main(int argc, char const *argv[])
{
	Bag<int> oo;
	int k = 1;
	oo.add(k);
	fii(oo);

	return 0;
}