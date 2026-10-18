#include <iostream>
using namespace std;

class Poly
{
private:
    double a, b, c;

public:
    Poly()
    {
        a = 0;
        b = 0;
        c = 0;
    }

    Poly(double x, double y, double z)
    {
        a = x;
        b = y;
        c = z;
    }

    Poly operator+(const Poly &p) const
    {
        return Poly(a + p.a, b + p.b, c + p.c);
    }

    friend ostream &operator<<(ostream &out, const Poly &p)
    {
        bool printed = false;

        if (p.a != 0)
        {
            out << p.a << "x^2";
            printed = true;
        }

        if (p.b != 0)
        {
            if (printed)
                out << (p.b > 0 ? " + " : " - ");
            else if (p.b < 0)
                out << "-";

            out << (p.b < 0 ? -p.b : p.b) << "x";
            printed = true;
        }

        if (p.c != 0)
        {
            if (printed)
                out << (p.c > 0 ? " + " : " - ");
            else if (p.c < 0)
                out << "-";

            out << (p.c < 0 ? -p.c : p.c);
            printed = true;
        }

        if (!printed)
            out << "0";

        return out;
    }
};

int main()
{
    Poly q1(5, -3, 7);
    Poly q2(2, 6, -4);
    Poly sum;

    sum = q1 + q2;

    cout << q1 << " : q1\n";
    cout << q2 << " : q2\n";
    cout << sum << " : q1+q2\n";

    return 0;
}
