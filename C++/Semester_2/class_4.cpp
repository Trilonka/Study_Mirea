#include <iostream>
using namespace std;

class BaseString
{
protected:
    char *p;
    int len;
    int capacity;

public:
    BaseString(char *ptr)
    {
        //cout<<"\nBase Constructor 1\n";
        len = 0;
        for (int i = 0; ptr[i] != '\0'; i++) {
            len++;
        }
        capacity = (len >= 256) ? len << 1 : 256;
        p = new char[capacity];
        for (int i = 0; i < len; i++) {
            p[i] = ptr[i];
        }
        p[len] = '\0';
    }

    BaseString(const char *ptr)
    {
        //cout<<"\nBase Constructor 1\n";
        len = 0;
        for (int i = 0; ptr[i] != '\0'; i++) {
            len++;
        }
        capacity = (len >= 256) ? len << 1 : 256;
        p = new char[capacity];
        for (int i = 0; i < len; i++) {
            p[i] = ptr[i];
        }
        p[len] = '\0';
    }

    BaseString(int Capacity = 256)
    {
        //cout<<"\nBase Constructor 0\n";
        capacity = Capacity;
        p = new char[capacity];
        len = 0;
    }

    BaseString(const BaseString &s)
    {
        //cout<<"\nBase Copy Constructor\n";
        len = s.len;
        capacity = s.capacity;
        p = new char[capacity];
        for(int i=0; i<len;i++) {
            p[i] = s.p[i];
        }
        p[len] = '\0';
    }

    ~BaseString()
    {
        //cout<<"\nBase Destructor\n";
        if (p != NULL)
            delete[] p;
        len = 0;
    }

    int Length() { return len; }
    int Capacity() { return capacity; }
    char *get() { return p; }
    char &operator[](int i) { return p[i]; }

    BaseString &operator=(const BaseString &s)
    {
        //cout<<"\nBase Operator = \n";
        delete[] p;
        len = s.len;
        capacity = s.capacity;
        p = new char[capacity];
        for (int i = 0; i < len; i++) {
            p[i] = s.p[i];
        }
        p[len] = '\0';
        return *this;
    }

    BaseString operator+(const BaseString &s)
    {
        BaseString res;
        res.len = len + s.len;
        res.capacity = (res.len >= 256) ? res.len << 1 : 256;
        for (int i = 0; i < len; i++) {
            res.p[i] = p[i];
        }
        for (int i = len; i < res.len; i++) {
            res.p[i] = s.p[i - len];
        }
        return res;
    }

    virtual void print()
    {
        int i = 0;
        while (p[i] != '\0') {
            cout << p[i++];
        }
    }
};

class String : public BaseString
{
public:
    String(char *ptr) : BaseString(ptr) {}
    String(const char *s) : BaseString(s) {}
    String(int Capacity = 256) : BaseString(Capacity) {}
    String(const String &s)
    {
        delete[] p;
        capacity = s.capacity;
        p = new char[capacity];
        len = s.len;
        for (int i = 0; i < len; i++) {
            p[i] = s.p[i];
        }
        p[len] = '\0';
    }

    ~String() {}

    int IndexOf(char c) 
    {
        for (int i = 0; i < len; i++) {
            if (p[i] == c) {
                return i;
            }
        }
        return -1;
    }

    int string_to_number()
    {
        int ans = 0;
        char k = 1;
        bool isNum = true;
        for (int i = len-1; i>=0; i--) {
            if(i==0 && p[i]=='-' && isNum) {
                return ans *= -1;
            }
            if (p[i]>='0' && p[i]<='9') {
                ans += k*p[i];
                k *= 10;
            } else {
                isNum = false;
                break;
            }
        }
        if (!isNum) cout << "It isn't a number, returned 0" << endl;
        return isNum ? ans : 0;
    }
};

int main()
{
        BaseString str1("hi teacher, have you a good day!");
        str1.print(); cout << endl;
        BaseString str2(" you are the best");
        BaseString str3;
        str3 = str1 + str2;
        str3.print(); cout << endl;

        String s1("wow");
        String s2(str3.get());
        s2.print(); cout << endl;
        s1 = s2;
        cout << s1.IndexOf('o') << endl;

        String num1("4213");
        num1.print();
        String num2("-3213");
        
        cout << num1.string_to_number() << endl;
        cout << num2.string_to_number() << endl;
        cout << s1.string_to_number() << endl;
}