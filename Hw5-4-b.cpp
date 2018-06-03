#include <iostream>

using namespace std;

template <typename Itemtype>
class deque
{
private:
	Stack<Itemtype> mainStack;
	Stack<Itemtype> auxStack;
public:
	void add_front(Itemtype Item);
	void remove_back();
	void add_back(Itemtype Item);
	void remove_front();
	deque();
	~deque();
	
};
template <typename Itemtype>
void deque::add_back(Itemtype Item){
	while(!mainStack.isEmpty()){
		auxStack.push(mainStack.peek());
		mainStack.pop();
	}
	auxStack.push(Item);
	while(!auxStack.isEmpty()){
		mainStack.push(auxStack.peek());
		auxStack.pop();
	}
}
template <typename Itemtype>
void deque::remove_front(){
	mainStack.pop();
}
template <typename Itemtype>
void deque::add_front(Itemtype Item){
	mainStack.push(Item);
}

template <typename Itemtype>
void deque::remove_back(){
	while(!mainStack.isEmpty()){
		auxStack.push(mainStack.peek());
		mainStack.pop();
	}
	auxStack.pop();
	while(!auxStack.isEmpty()){
		mainStack.push(auxStack.peek());
		auxStack.pop();
	}
}



int main(int argc, char const *argv[])
{
	return 0;
}

