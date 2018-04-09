#include <iostream>
#include<stdexcept>
#include<math.h>
#include<string>
using namespace std;

class MyException : public exception
{
public:
	MyException(const string& msg = ""): exception(msg.c_str()) {}
};
bool isPrime(int n)throw (MyException){
	if(n < 2){
		throw MyException("smaller than one");
	}
	for(int i = 2 ; i < sqrt(n);i++){
		if(n % i == 0){
			return false;
		}else{
			return true;
		}
	}
}
int main(){
	int n = 0;
	bool result;
	try{
		result = isPrime(n);
	}
	catch(MyException e){
		cout << e.what();
	}
	return 0;
}
