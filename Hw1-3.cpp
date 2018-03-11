#include<iostream>
#include<stdlib.h>
using namespace std;
struct TwoInt
{
	int i;
	int j;
};
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
	double operator[](struct TwoInt) const;
};
double MyVector::operator[](TwoInt p) const{
	if(p.i >= 0 && p.j > p.i && n-1 >= p.j){
		double sum = 0;
		for(int i = p.i;i <= p.j;i++){
			sum += m[i];
		}
		return sum;
	}else{
		exit(1);
	}
}
int main(){
	double d[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	MyVector v(5, d);
	TwoInt ti = {1, 3};
	cout << v[ti];
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
