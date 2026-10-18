#include <iostream>
using namespace std;

class Shape
{
protected:
    double width, height;

public:
    Shape(double w, double h)
    {
        width = w;
        height = h;
    }
};

class Triangle : public Shape
{
public:
    Triangle(double w, double h) : Shape(w, h) {}

    double area()
    {
        return 0.5 * width * height;
    }
};

class Rectangle : public Shape
{
public:
    Rectangle(double w, double h) : Shape(w, h) {}

    double area()
    {
        return width * height;
    }
};

int main()
{
    Triangle t(12, 5);
    Rectangle r(10, 4);

    cout << "Triangle area = " << t.area() << endl;
    cout << "Rectangle area = " << r.area() << endl;

    return 0;
}