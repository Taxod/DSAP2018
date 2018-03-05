#include<iostream>

using namespace std;
//�o���D�حnoverload assighment�A�_�h�i��X�� 
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
	friend MyVector operator-(MyVector& v);
};
MyVector operator-(MyVector& v);
int main(){
	double d = 1.23;
	double m[3] = {-d, -d, -d};
	MyVector v(3, m);
	v.print();
	v = -v;
	v.print();
	if(v == d)
		cout << "Equal!";
	else
		cout << "Unequal!";
	return 0;
}

MyVector operator-(MyVector& v){
	MyVector t(v);
	for(int i = 0 ; i < t.n ; i++){
//		t.m[i] = -1*t.m[i];
//		t.m[i] *= -1;
		t.m[i] = -t.m[i]; 
	}
	return t;
}
//����member funtion ���ζǰѼơA����ŦX�޿�(�t���) 

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
