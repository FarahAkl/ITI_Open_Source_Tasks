#include <iostream>
using namespace std;

class Stack
{
    int data[100];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    void push(int num)
    {
        if (isfull())
        {
            cout << "Stack Overflow" << endl;
            return;
        }

        data[++top] = num;
    }

    int pop()
    {
        if (isempty())
        {
            cout << "Stack Underflow" << endl;
            return -1;
        }

        return data[top--];
    }

    int peek()
    {
        if (isempty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }

        return data[top];
    }

    bool isempty()
    {
        return top == -1;
    }

    bool isfull()
    {
        return top == 99;
    }
};

int main()
{
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element: " << s.peek() << endl;
    cout << "Popped element: " << s.pop() << endl;
    cout << "Top element: " << s.peek() << endl;

    cout << boolalpha;
    cout << "Is empty: " << s.isempty() << endl;
    cout << "Is full: " << s.isfull() << endl;

    return 0;
}
