#include <stdio.h>
#include <windows.h>
void goto_row_col(int row, int col)
{
    COORD c;

    c.X = col;
    c.Y = row;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void main(void)
{

    int size;
    int row, col;
    int value;

    do
    {
        printf("please size of magic square odd :");
        scanf("%3d", &size);
    } while (size % 2 == 0);

    row = 1;
    col = (size + 1) / 2;
    value = 1;
    int k;

    do
    {
        goto_row_col(row, col * 3);
        printf("%d", value);
        Sleep(3000);
        if (value % size == 0)
            row++;
        else
        {
            row--;
            col--;
        }
        if (row == 0)
            row = size;
        if (col == 0)
            col = size;
        value++;
    } while (value <= size * size);
}
