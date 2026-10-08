#include <stdio.h>
#include <conio.h>
#include <windows.h>

void main()
{
    char *menu[] = {
        "New",
        "Open",
        "Save",
        "Exit"};

    int size = 4;
    int selected = 0;
    char key;

    while (1)
    {
        system("cls");

        for (int i = 0; i < size; i++)
        {
            if (i == selected)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                printf("  %s  ", menu[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else
            {
                printf("  %s  ", menu[i]);
            }

            printf("\n");
        }

        key = getch();

        if (key == -32)
        {
            key = getch();

            if (key == 72) // Up Arrow
            {
                selected--;

                if (selected < 0)
                    selected = size - 1;
            }
            else if (key == 80) // Down Arrow
            {
                selected++;

                if (selected >= size)
                    selected = 0;
            }
        }
        else if (key == 13) // Enter
        {
            if (selected == size - 1)
                break;
        }
    }
}