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
class StackInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool push(const Itemtype& newEntry) = 0;
	virtual bool pop() = 0;
	virtual Itemtype peek() const = 0;
};

template <typename Itemtype>
class Stack : public StackInterface<Itemtype>
{
private:
	Node<Itemtype>* topPtr;
public:
	Stack();
	Stack(const Stack<Itemtype>& aStack);
	~Stack();
	bool isEmpty() const;
	bool push(const Itemtype& newEntry);
	bool pop();
	Itemtype peek() const;
};

bool seconed_precedence(char a,char b){
	if (b == '^')
	{
		return true;
	}
	if (b == '%' || b == '*' || b == '/')
	{
		if (a != '^')
		{
			return true;
		}else{
			return false;
		}
	}
	if (b == '+' || b == '-')
	{
		if (a == '+' || a == '-' )
		{
			return true;
		}else{
			return false;
		}
	}
}


string InfixtoPostfix(string s){
	Stack<char> _operator;
	string postfix = "";
	// cout << s << "\n";
	for (int i = 0; i < int(s.length()); ++i)
	{
		if (isdigit(s[i]) || s[i] == 'x')
		{
			postfix += s[i];
		}else if (s[i] == '(')
		{
			_operator.push(s[i]);
		}else if (s[i] == ')')
		{
			while(_operator.peek() != '('){
				postfix += _operator.peek();
				_operator.pop();
			}
			_operator.pop();
		}else{
			while(!_operator.isEmpty() && _operator.peek() != '(' && seconed_precedence(s[i],_operator.peek())){
				postfix += _operator.peek();
				_operator.pop();
			}
			_operator.push(s[i]);
		}
	}
	while(!_operator.isEmpty()){
		postfix += _operator.peek();
		_operator.pop();
	}
	// cout << postfix << endl;
	return postfix;
}


int main(int argc, char const *argv[])
{
	//12*x^2+(((5*x^2-3*x^3+x+2)/(2*x^2-2))^2)%(x^2+1)
	string s;
	getline(cin,s);
	string postfix = InfixtoPostfix(s);
	cout << postfix;
	return 0;
}





































































































































template <typename Itemtype>
Stack<Itemtype>::Stack():topPtr(nullptr){}

template <typename Itemtype>
Stack<Itemtype>::Stack(const Stack<Itemtype>& aStack){
	Node<Itemtype>* origChainPtr = aStack.topPtr;
	if (origChainPtr == nullptr)
	{
		topPtr = nullptr;
	}else{
		topPtr = new Node<Itemtype>();
		topPtr->setItem(origChainPtr->getItem());
		Node<Itemtype>* newChainPtr = topPtr;
		origChainPtr = origChainPtr->getNext();
		while(origChainPtr != nullptr){
			Itemtype nextItem = origChainPtr->getItem();
			Node<Itemtype>* newNodePtr = new Node<Itemtype>(nextItem);
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
}

template <typename Itemtype>
bool Stack<Itemtype>::push(const Itemtype& newItem){
	Node<Itemtype>* newNodePtr = new Node<Itemtype>(newItem,topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;
	return true;
}

template <typename Itemtype>
bool Stack<Itemtype>::pop(){
	bool result = false;
	if (!isEmpty())
	{
		Node<Itemtype>* nodeToDeletePtr = topPtr;
		topPtr = topPtr->getNext();

		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		return true;
	}
	return result;
}

template <typename Itemtype>
Stack<Itemtype>::~Stack(){
	while(!isEmpty()){
		pop();
	}
}

template <typename Itemtype>
Itemtype Stack<Itemtype>::peek()const {
	return topPtr->getItem();
}//-------------------------------------
//沒有考慮裡面沒東西--------------------------------------------

template <typename Itemtype>//不確定--------------------
bool Stack<Itemtype>::isEmpty() const{
	if (topPtr == nullptr)
	{
		return true;
	}else{
		return false;
	}
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
