#include <iostream>
using namespace std;

class Stack
{
private:
    int *data;
    int capacity;

public:
    Stack(int size) : data(new int[size]), capacity(size), top(-1)
    {
    }

    ~Stack()
    {
        delete[] data;
    }

    int top = -1;

    int push(int num)
    {
        if (isfull())
        {
            return -1;
        }
        data[++top] = num;
    }

    int pop()
    {
        if (top == -1)
            return -1;

        return data[top--];
    }
    int peek()
    {
        if (isempty())
            return -1;
        return data[top];
    }

    bool isempty()
    {
        return top == -1;
    }

    bool isfull()
    {
        return top == capacity - 1;
    }
};

int main()
{
    Stack s(3);

    s.push(10);
    s.push(20);
    s.push(30);

    cout << s.peek() << endl;
    cout << s.pop() << endl;
    cout << s.peek() << endl;

    return 0;
}