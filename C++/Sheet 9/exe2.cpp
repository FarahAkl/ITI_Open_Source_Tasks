#include <iostream>
using namespace std;

int sum(int a, int b)
{
    return a + b;
}

int sum(int a, int b, int c)
{
    return a + b + c;
}

int sum(int a, int b, int c, int d)
{
    return a + b + c + d;
}

int main()
{
    int a, b, c, d;

    cout << "Enter the first number : " << endl;
    cin >> a;

    cout << "Enter the second number : " << endl;
    cin >> b;

    cout << "Enter the third number : " << endl;
    cin >> c;

    cout << "Enter the fourth number : " << endl;
    cin >> d;

    cout << sum(a, b) << endl;
    cout << sum(a, b, c) << endl;
    cout << sum(a, b, c, d) << endl;

    return 0;
}
