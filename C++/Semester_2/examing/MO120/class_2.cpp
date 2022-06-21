#include <iostream>
#include <cmath>

using namespace std;

class Point
{
private:
    double x;
    double y;
public:
    Point()
    {
        x = y = 0;
    }

    Point(double t)
    {
        x = y = t;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator<(Point& other)
    {
        return sqrt(x*x + y*y) < sqrt(other.x*other.x + other.y*other.y);
    }

    bool operator==(double other_x)
    {
        return x == other_x;
    }
};

bool operator==(double other_x, Point& x)
{
    return x == other_x;
}

int main()
{
    Point a;
    Point b(2);
    Point c(3, 4);
    
    cout << (c==3) << endl;
    cout << (5==a) << endl;
    cout << (a<c) << endl;
    cout << (c<b) << endl;

    cout << (8<<1);

    return 0;
}