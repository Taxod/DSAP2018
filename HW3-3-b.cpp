#include <iostream >
#include<stdexcept>
using namespace std;
const int MAX_LEN = 10;
int getArrayElement(const int array[], int len, int index)throw (out_of_range);
int main()
{
	int array[MAX_LEN] = {0};

	int index = 0;
	cin >> index;
	try{
		int result = getArrayElement(array , MAX_LEN, index);
	}
	catch(out_of_range e){
		cout << e.what();
	}
	return 0;
}

int getArrayElement(const int array[], int len, int index) throw (out_of_range)
{
if(0 <= index && index < len)
	return array[index];
else
	throw out_of_range ("Bad index!\n");
}
