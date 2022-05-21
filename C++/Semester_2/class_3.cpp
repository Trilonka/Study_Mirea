#include <iostream>
using namespace std;

class A1 
{
protected:
    int a1;
public:
    A1(int a = 0)
    { 
        a1 = a;
        cout << "\nClass A1 constructor";
    }
    virtual void print() { cout << "\nVariable of A1 class"; }
    virtual void show() { cout << "\na1 = " << a1; }

};

class B1 : virtual public A1
{
protected:
    int b1;
public:
    B1(int b = 0, int a = 0) : A1(a) 
    {
        b1 = b;
        cout << "\nClass B1 constructor";
    }
    void print() { cout << "\nVariable of B1 class"; }
    void show()
    {
        cout << "\nb1 = " << b1 << ", a1 = " << a1;
    }
};

class B2 : virtual public A1 
{
protected:
    int b2;
public:
    B2(int b = 0, int a = 0) : A1(a) 
    {
        b2 = b;
        cout << "\nClass B2 constructor";
    }
    void print() { cout << "\nVariable of B2 class"; }
    void show()
    {
        cout << "\nb2 = " << b2 << ", a1 = " << a1;
    }
};

class C1 : virtual public B1, virtual public B2 
{
protected:
    int c1;
public:
    C1(int c = 0, int b1 = 0, int b2 = 0, int a = 0) : B1(b1), B2(b2)
    {
        c1 = c;
        cout << "\nClass C1 constructor";
    }
    void print() { cout << "\nVariable of C1 class"; }
    void show()
    {
        cout << "\nc1 = " << c1 << ", b1 = " << b1 << ", b2 = " << b2 << ", a1 = " << a1;
    }
};

class C2 : virtual public B1, virtual public B2 
{
protected:
    int c2;
public:
    C2(int c = 0, int b1 = 0, int b2 = 0, int a = 0) : B1(b1, a), B2(b2, a)
    {
        c2 = c;
        cout << "\nClass C2 constructor";
    }
    void print() { cout << "\nVariable of C2 class"; }
    void show()
    {
        cout << "\nc2 = " << c2 << ", b1 = " << b1 << ", b2 = " << b2 << ", a1 = " << a1;
    }
};

int main()
{
    C1 test1(1,2,3,4);
    B1 test2(9,8);
    B2 test66(3,3);
    A1 test3(123);

    cout << "\n\nC1";
    A1* ptr = &test1;
    ptr->show();
    ptr->print();

    cout << "\n\nB1";
    ptr = &test2;
    ptr->show();
    ptr->print();

    cout << "\n\nA1";
    ptr = &test3;
    ptr->show();
    ptr->print();
}