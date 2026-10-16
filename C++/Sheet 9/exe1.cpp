#include <iostream>
using namespace std;

void swap(int &a, int &b);
int main()
{
    int a;
    int b;
    int temp;

    cout << "Enter the first number : " << endl;
    cin >> a;

    cout << "Enter the second number : " << endl;
    cin >> b;

    swap(a, b);

    return 0;
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "a = " << a << " b = " << b << endl;
}