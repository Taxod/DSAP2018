#include <iostream>

using namespace std;

template <typename Itemtype>
class queue
{
private:
	Stack<Itemtype> mainStack;
	Stack<Itemtype> auxStack;
public:
	void add(Itemtype Item);
	void remove();
	queue();
	~queue();
	
};

template <typename Itemtype>
void queue::add(Itemtype Item){
	mainStack.push(Item);
}

template <typename Itemtype>
void queue::remove(){
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

