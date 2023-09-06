#include <iostream>
using namespace std;

class Point
{
private:
    int x;
    int y;

public:
    void Init()
    {
        x = rand() % 20;
        y = rand() % 10;
    }

    void Print()
    {
        cout << x << "\t" << y << endl;
    }
};

int main()
{
    Point a;
}