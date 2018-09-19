/*
  this is a case about static binding and dynamic binding
  that can help you to understand the difference of its
*/
#include<iostream>
using namespace std;

class A {
public:
      virtual void f() const {
              cout << "A::f()" << endl;
      }
};

class B: public A {
public:
      virtual void f() const {
              cout << "B::f()" << endl;
      }      
};

int main() {
    B b1, b2, b3;
    A a = b1;
    A *p1 = &b2;
    A &p2 = b3;
    p1->f();//dynamic binding
    p2.f();//dynamic binding
    a.f();//static binding
    
    int t;
    cin >> t;
    return 0;   
}
