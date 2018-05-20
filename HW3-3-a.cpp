#include <iostream >
using namespace std;
const int MAX_LEN = 10;
int getArrayElement(const int array[], int len, int index);
int main()
{
	int array[MAX_LEN] = {0};

	int index = 0;
	cin >> index;
	int result = getArrayElement(array , MAX_LEN, index);

	if(result == -1)
		cout << "Bad index!\n";
	else
		cout << result << endl;
	return 0;
}

int getArrayElement(const int array[], int len, int index)
{
if(0 <= index && index < len)
	return array[index];
else
	return -1;
}
