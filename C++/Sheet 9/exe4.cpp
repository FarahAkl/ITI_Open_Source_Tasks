#include <iostream>
#include <windows.h>
using namespace std;

void goto_row_col(int row, int col)
{
    COORD c;
    c.X = col;
    c.Y = row;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main()
{
    int size = 4;
    int value = 1;

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            goto_row_col(row + 1, (col + 1) * 4);

            if (row == col || row + col == size - 1)
                cout << size * size + 1 - value;
            else
                cout << value;

            // Sleep(500);
            value++;
        }
    }

    return 0;
}
