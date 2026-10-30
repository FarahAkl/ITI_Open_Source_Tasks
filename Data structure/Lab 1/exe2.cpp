
#include <iostream>
#include <cmath>
using namespace std;

int jumpSearch(int arr[], int n, int key)
{
    int step = sqrt(n);
    int prev = 0;

    while (prev < n && arr[min(step, n) - 1] < key)
    {
        prev = step;
        step += sqrt(n);

        if (prev >= n)
            return -1;
    }

    for (int i = prev; i < min(step, n); i++)
    {
        if (arr[i] == key)
            return i;
    }

    return -1;
}

int main()
{
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56};
    int n = 9;
    int key = 23;

    int result = jumpSearch(arr, n, key);

    if (result != -1)
        cout << "Element found at index " << result;
    else
        cout << "Element not found";

    return 0;
}
