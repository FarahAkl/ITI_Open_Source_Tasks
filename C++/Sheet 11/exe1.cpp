#include <iostream>
using namespace std;

class Complex
{
private:
    double real, imag;

public:
    Complex(double r = 0, double i = 0)
    {
        real = r;
        imag = i;
    }

    friend istream &operator>>(istream &in, Complex &c)
    {
        in >> c.real >> c.imag;
        return in;
    }

    friend ostream &operator<<(ostream &out, const Complex &c)
    {
        out << c.real;

        if (c.imag >= 0)
            out << " + " << c.imag << "i";
        else
            out << " - " << -c.imag << "i";

        return out;
    }

    Complex operator+(const Complex &c) const
    {
        return Complex(real + c.real, imag + c.imag);
    }

    Complex operator-(const Complex &c) const
    {
        return Complex(real - c.real, imag - c.imag);
    }

    Complex operator*(const Complex &c) const
    {
        return Complex(
            real * c.real - imag * c.imag,
            real * c.imag + imag * c.real);
    }

    Complex operator/(const Complex &c) const
    {
        double denominator = c.real * c.real + c.imag * c.imag;

        if (denominator == 0)
        {
            throw "Division by zero";
        }

        return Complex(
            (real * c.real + imag * c.imag) / denominator,
            (imag * c.real - real * c.imag) / denominator);
    }

    Complex operator-() const
    {
        return Complex(-real, -imag);
    }
};

int main()
{
    Complex c1, c2;

    cout << "Enter real and imaginary parts of first number: ";
    cin >> c1;

    cout << "Enter real and imaginary parts of second number: ";
    cin >> c2;

    cout << "\nFirst number: " << c1;
    cout << "\nSecond number: " << c2;

    cout << "\n\nAddition: " << c1 + c2;
    cout << "\nSubtraction: " << c1 - c2;
    cout << "\nMultiplication: " << c1 * c2;

    cout << "\nDivision: " << c1 / c2;

    cout << "\nNegation of first number: " << -c1;

    cout << endl;
    return 0;
}
