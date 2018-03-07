#include<iostream>
#include<string>
#include<cstring>
#include<stdlib.h>
#include <typeinfo>
using namespace std;
class MyVector
{
private:
	int n;
	double* m;
public:
	MyVector();
	MyVector(int n, double m[]);
	MyVector(const MyVector& v);
	~MyVector();
	void print();
	bool operator==(const double d) const;
	double operator[](char* c) const;
};

double MyVector::operator[](char* c) const{
	
	char* delim = ":";
	char* ptr;
	ptr = strtok(c,delim);
	int num[2] = {0};
	int count = 0;
	while(ptr != nullptr){
		num[count] = atoi(ptr);
		count ++;
		ptr = strtok(nullptr,delim);
	}
	if(num[0] >= 0 && num[1] > num[0] && n-1 >= num[1]){
		double sum = 0;
		for(int i = num[0];i <=num[1];i++){
			sum += m[i];
		}
		return sum;
	}else{
		exit(1);
	}
	return 0; 
}
int main(){
	double d[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	MyVector v(5, d);
	char c[] = "1:3";
	cout << v[c];

	return 0;
}

MyVector::MyVector()
{
	n = 0;
	m = nullptr;
}

MyVector::MyVector(int dim, double v[])
{
	n = dim;
	m = new double[dim];
	for(int i = 0; i < dim; i++)
	m[i] = v[i];
}

MyVector::~MyVector()
{
	delete [] m;
}

MyVector::MyVector(const MyVector& v)
{
	n = v.n;
	m = new double[n];
	for(int i = 0; i < n; i++)
		m[i] = v.m[i];
}

void MyVector::print()
{
	cout << "(";
	for(int i = 0; i < n - 1; i++)
		cout << m[i] << ", ";
	cout << m[n-1] << ")\n";
}
bool MyVector::operator==(const double d) const
{
	for(int i = 0; i < n; i++) {
		if(this->m[i] - d > 0.00001)
			return false;
	}
	return true;
}

