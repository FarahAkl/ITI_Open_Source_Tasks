#include <iostream>
using namespace std;

class Complex
{
    float real, imaginary;

public:
    Complex(float r = 0, float i = 0)
    {
        real = r;
        imaginary = i;
    }

    Complex add(Complex c)
    {
        return Complex(real + c.real,
                       imaginary + c.imaginary);
    }

    Complex sub(Complex c)
    {
        return Complex(real - c.real,
                       imaginary - c.imaginary);
    }

    Complex mult(Complex c)
    {
        return Complex(
            real * c.real - imaginary * c.imaginary,
            real * c.imaginary + imaginary * c.real);
    }

    Complex div(Complex c)
    {
        float denominator =
            c.real * c.real + c.imaginary * c.imaginary;

        if (denominator == 0)
        {
            cout << "Division by zero is not allowed." << endl;
            return Complex();
        }

        return Complex(
            (real * c.real + imaginary * c.imaginary) / denominator,
            (imaginary * c.real - real * c.imaginary) / denominator);
    }

    void display()
    {
        cout << real;

        if (imaginary >= 0)
            cout << " + " << imaginary << "i";
        else
            cout << " - " << -imaginary << "i";

        cout << endl;
    }
};

int main()
{
    Complex c1(6, 4);
    Complex c2(2, 2);

    cout << "Addition: ";
    c1.add(c2).display();

    cout << "Subtraction: ";
    c1.sub(c2).display();

    cout << "Multiplication: ";
    c1.mult(c2).display();

    cout << "Division: ";
    c1.div(c2).display();

    return 0;
}
