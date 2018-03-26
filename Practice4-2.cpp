#include <iostream>
using namespace std;


template<typename T>
class MyVector2D
{
private:
  T x;
  T y;
public:
  MyVector2D() : x(0), y(0) {}
  MyVector2D(T x, T y) : x(x), y(y) {} 
  void print() const;   
  bool operator==(const MyVector2D& v) const;
};

template<typename T>
void MyVector2D<T>::print() const 
{
  cout << "(" << this->x << ", " << this->y << ")\n";
}
template<typename T>
bool MyVector2D<T>::operator==(const MyVector2D& v) const
{
  if(this->x == v.x && this->y == v.y)
    return true;
  else
    return false;
}







int main()
{
  MyVector2D<double> u(1.2, 2.3);
  MyVector2D<double> v(1.4, 2.6);
  u.print();
  v.print();
  
  if(u == v)
    cout << "Equal!\n";
  else
    cout << "Unequal!\n";
  
  return 0;
}
