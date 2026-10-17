
#include <iostream>
using namespace std;

class Point
{
    int x, y;

public:
    Point(int x1, int y1)
    {
        x = x1;
        y = y1;
    }

    Point add(Point p2)
    {
        return Point(x + p2.x,y + p2.y);
    }

    Point sub(Point p2)
    {
        return Point(x - p2.x, y - p2.y);
    }

    void print(Point p)
    {
        cout << "( " << p.x << " , " << p.y << " )" << endl;
    }
};

int main()
{
    Point p1(10, 20);
    Point p2(4, 5);

    Point result1 = p1.add(p2);
    Point result2 = p1.sub(p2);

    result1.print(result1);
    result2.print(result2);
    return 0;
}
