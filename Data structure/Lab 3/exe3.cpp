#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>
using namespace std;

template <class T>
struct Node
{
    T data;
    Node<T> *next;

    Node(T value)
    {
        data = value;
        next = nullptr;
    }
};

template <class T>
class Stack
{
private:
    Node<T> *top;

public:
    Stack()
    {
        top = nullptr;
    }

    ~Stack()
    {
        T value;
        while (pop(value))
        {
        }
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    void push(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
    }

    bool pop(T &value)
    {
        if (isEmpty())
            return false;

        Node<T> *temp = top;
        value = temp->data;
        top = top->next;

        delete temp;
        return true;
    }

    bool peek(T &value) const
    {
        if (isEmpty())
            return false;

        value = top->data;
        return true;
    }

    void display() const
    {
        Node<T> *current = top;

        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }
};

bool isOperator(char ch)
{
    return ch == '+' || ch == '-' ||
           ch == '*' || ch == '/' || ch == '^';
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    if (op == '^')
        return 3;

    return 0;
}

bool isRightAssociative(char op)
{
    return op == '^';
}

bool isNumber(const string &token)
{
    if (token.empty())
        return false;

    bool hasDigit = false;
    bool hasDot = false;

    for (char ch : token)
    {
        if (isdigit(static_cast<unsigned char>(ch)))
        {
            hasDigit = true;
        }
        else if (ch == '.' && !hasDot)
        {
            hasDot = true;
        }
        else
        {
            return false;
        }
    }

    return hasDigit;
}

bool validateExpression(const string &expression)
{
    Stack<char> parentheses;
    bool expectOperand = true;
    bool hasToken = false;

    for (size_t i = 0; i < expression.size();)
    {
        char ch = expression[i];

        if (isspace(static_cast<unsigned char>(ch)))
        {
            i++;
            continue;
        }

        if (isdigit(static_cast<unsigned char>(ch)) || ch == '.')
        {
            if (!expectOperand)
                return false;

            bool hasDigit = false;
            bool hasDot = false;

            while (i < expression.size() &&
                   (isdigit(static_cast<unsigned char>(expression[i])) ||
                    expression[i] == '.'))
            {
                if (expression[i] == '.')
                {
                    if (hasDot)
                        return false;

                    hasDot = true;
                }
                else
                {
                    hasDigit = true;
                }

                i++;
            }

            if (!hasDigit)
                return false;

            expectOperand = false;
            hasToken = true;
        }
        else if (ch == '(')
        {
            if (!expectOperand)
                return false;

            parentheses.push(ch);
            expectOperand = true;
            hasToken = true;
            i++;
        }
        else if (ch == ')')
        {
            if (expectOperand || parentheses.isEmpty())
                return false;

            char open;
            parentheses.pop(open);

            expectOperand = false;
            i++;
        }
        else if (isOperator(ch))
        {
            if (expectOperand)
                return false;

            expectOperand = true;
            i++;
        }
        else
        {
            return false;
        }
    }

    return hasToken && !expectOperand && parentheses.isEmpty();
}

string infixToPostfix(const string &expression, bool &valid)
{
    Stack<char> operators;
    string postfix;
    valid = true;

    for (size_t i = 0; i < expression.size();)
    {
        char ch = expression[i];

        if (isspace(static_cast<unsigned char>(ch)))
        {
            i++;
        }
        else if (isdigit(static_cast<unsigned char>(ch)) || ch == '.')
        {
            while (i < expression.size() &&
                   (isdigit(static_cast<unsigned char>(expression[i])) ||
                    expression[i] == '.'))
            {
                postfix += expression[i];
                i++;
            }

            postfix += ' ';
        }
        else if (ch == '(')
        {
            operators.push(ch);
            i++;
        }
        else if (ch == ')')
        {
            char op;

            while (operators.peek(op) && op != '(')
            {
                operators.pop(op);
                postfix += op;
                postfix += ' ';
            }

            if (!operators.pop(op))
            {
                valid = false;
                return "";
            }

            i++;
        }
        else if (isOperator(ch))
        {
            char topOperator;

            while (operators.peek(topOperator) &&
                   topOperator != '(' &&
                   (precedence(topOperator) > precedence(ch) ||
                    (precedence(topOperator) == precedence(ch) &&
                     !isRightAssociative(ch))))
            {
                operators.pop(topOperator);
                postfix += topOperator;
                postfix += ' ';
            }

            operators.push(ch);
            i++;
        }
        else
        {
            valid = false;
            return "";
        }
    }

    char op;

    while (operators.pop(op))
    {
        if (op == '(')
        {
            valid = false;
            return "";
        }

        postfix += op;
        postfix += ' ';
    }

    return postfix;
}

bool evaluatePostfix(const string &postfix, double &result)
{
    Stack<double> values;
    istringstream input(postfix);
    string token;

    while (input >> token)
    {
        if (isNumber(token))
        {
            values.push(stod(token));
        }
        else if (token.size() == 1 && isOperator(token[0]))
        {
            double right, left;

            if (!values.pop(right))
                return false;

            if (!values.pop(left))
                return false;

            double answer = 0;

            switch (token[0])
            {
            case '+':
                answer = left + right;
                break;

            case '-':
                answer = left - right;
                break;

            case '*':
                answer = left * right;
                break;

            case '/':
                if (right == 0)
                    return false;

                answer = left / right;
                break;

            case '^':
                answer = pow(left, right);

                if (!isfinite(answer))
                    return false;

                break;
            }

            values.push(answer);
        }
        else
        {
            return false;
        }
    }

    if (!values.pop(result))
        return false;

    if (!values.isEmpty())
        return false;

    return true;
}

int main()
{
    string expression;

    while (true)
    {
        cout << "\nEnter an expression (or type exit): ";
        getline(cin, expression);

        if (expression == "exit")
            return 0;

        if (!validateExpression(expression))
            continue;

        bool valid;
        string postfix = infixToPostfix(expression, valid);

        if (!valid)
            continue;

        double result;

        if (!evaluatePostfix(postfix, result))
            continue;

        cout << "Postfix: " << postfix << endl;
        cout << "Result = " << result << endl;
    }

    return 0;
}
