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
    void swap(Itemtype& a,Itemtype& b);
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
    void printCnt(){
        cout << itemCnt << endl;
    }
    void printarray(){
        for (int i = 0; i < itemCnt; ++i)
        {
            cout << items[i] << " " ;
        }
        cout << endl;
    }
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

int main(int argc, char const *argv[])
{
    Heap<int> P;
    P.add(7878778);
    P.add(46879456);
    P.add(123);
    P.add(11);  
    P.add(846168);  
    while(!P.isEmpty()){
        cout << P.peekTop() << endl;
        P.remove();
    }
    return 0;
}






//Heap--------------------------------------------------------------------


template <typename Itemtype>
void Heap<Itemtype>::swap(Itemtype& a,Itemtype& b){
    Itemtype tmp;
    tmp = a;
    a = b;
    b = tmp;
}
template <typename Itemtype>
void Heap<Itemtype>::heapRebuild(int rootIndex,Itemtype* items,int itemCnt){
    if (rootIndex*2+2 < itemCnt || rootIndex*2+1 < itemCnt)
    {
        int largeChildIndex = 2 * rootIndex + 1;
        if (rootIndex*2+2 < itemCnt)
        {
            int rightchildindex = largeChildIndex + 1;
            if (items[rightchildindex] < items[largeChildIndex])//operatoroverloading!*
            {
                largeChildIndex = rightchildindex;
            }
            if (items[rootIndex] > items[largeChildIndex])
            {
                swap(items[rootIndex],items[largeChildIndex]);//swap items[rootindex] and items[largeChildIndex]
                heapRebuild(largeChildIndex,items,itemCnt);
            }
        }
    }
    // printarray();
}


template <typename Itemtype>
bool Heap<Itemtype>::remove(){
    bool result = false;
    items[0] = items[itemCnt-1];
    itemCnt--;
    heapRebuild(0,items,itemCnt);
    // cout << peekTop() << endl;
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
            swap(items[newDataIndex],items[parentIndex]);
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
