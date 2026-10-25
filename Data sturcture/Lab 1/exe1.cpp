
#include <iostream>
using namespace std;

template <class T>
class List
{
private:
    T *arr;
    int size;
    int capacity;

public:
    List(int cap = 5)
    {
        capacity = cap > 0 ? cap : 5;
        size = 0;
        arr = new T[capacity];
    }

    void append(T value)
    {
        if (size == capacity)
        {
            capacity *= 2;

            T *temp = new T[capacity];

            for (int i = 0; i < size; i++)
            {
                temp[i] = arr[i];
            }

            delete[] arr;
            arr = temp;
        }

        arr[size] = value;
        size++;
    }

    void insert(T value, int i)
    {
        if (i < 0 || i > size)
        {
            cout << "Invalid index" << endl;
            return;
        }

        if (size == capacity)
        {
            capacity *= 2;
            T *temp = new T[capacity];

            for (int j = 0; j < size; j++)
            {
                temp[j] = arr[j];
            }

            delete[] arr;
            arr = temp;
        }
        for (int j = size; j > i; j--)
        {
            arr[j] = arr[j - 1];
        }

        arr[i] = value;
        size++;
    }

    void remove(T value)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == value)
            {
                for (int j = i; j < size - 1; j++)
                {
                    arr[j] = arr[j + 1];
                }
                size--;
                return;
            }
        }
    }

    T pop(int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "Invalid index" << endl;
            return T{};
        }

        T temp = arr[index];

        for (int j = index; j < size - 1; j++)
        {
            arr[j] = arr[j + 1];
        }
        size--;
        return temp;
    }

    void clear()
    {
        size = 0;
    }

    int index(T value)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == value)
            {
                return i;
            }
        }

        return -1;
    }

    int count(T value)
    {
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == value)
                count++;
        }

        return count;
    }

    void reverse()
    {
        T temp;

        for (int i = 0; i < size / 2; i++)
        {
            temp = arr[i];
            arr[i] = arr[size - 1 - i];
            arr[size - 1 - i] = temp;
        }
    }

    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~List()
    {
        delete[] arr;
    }
};

int main()
{
    List<int> numbers;

    numbers.append(10);
    numbers.append(20);
    numbers.append(30);

    numbers.display();

    List<double> values;

    values.append(2.5);
    values.append(3.7);

    values.display();

    return 0;
}
