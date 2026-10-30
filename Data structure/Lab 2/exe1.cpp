#include <iostream>
#include <string>

using namespace std;

class Stack
{
private:
    char *arr;
    int top;
    int capacity;

public:
    Stack(int size)
    {
        capacity = size;
        arr = new char[capacity];
        top = -1;
    }
    ~Stack()
    {
        delete[] arr;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == capacity - 1;
    }

    void push(char c)
    {
        if (isFull())
        {
            cout << "Stack Overflow" << endl;
            return;
        }

        arr[++top] = c;
    }

    char pop()
    {
        if (isEmpty())
            return '\0';
        return arr[top--];
    }
};

bool isBalanced(string exp)
{
    Stack s(exp.length());

    for (int i = 0; i < exp.length(); i++)
    {
        char ch = exp[i];

        if (ch == '(' || ch == '[' || ch == '{')
        {
            s.push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if (s.isEmpty())
                return false;

            char top = s.pop();

            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{'))
            {
                return false;
            }
        }
    }

    return s.isEmpty();
}

int main()
{
    string exp;

    cout << "Enter an expression: ";
    getline(cin, exp);

    if (isBalanced(exp))
        cout << "Balanced\n";
    else
        cout << "Not Balanced\n";

    return 0;
}
