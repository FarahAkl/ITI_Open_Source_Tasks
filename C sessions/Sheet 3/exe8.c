#include <stdio.h>
#include <conio.h>

void main(void)
{

    int number = 0;
    char ch;
    int counter = 0;

    printf("please number:");
    while ((ch = getch()) != 13)
    {
        switch (ch)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (counter < 5)
            {
                printf("%c", ch);
                number = number * 10 + ch - '0';
                counter++;
            }
            else
                printf("\a");
            break;
        case 8:
            if (counter > 0)
            {
                printf("\b \b");
                number = number / 10;
                counter--;
            }

            break;
        default:
            printf("\a");
        }
    }

    printf("\nNumber=%d\n", number);
}
