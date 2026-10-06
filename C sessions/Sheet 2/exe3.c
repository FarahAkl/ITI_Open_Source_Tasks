#include <stdio.h>

void first_num(int ones)
{
    switch (ones)
    {
    case 1:
        printf("One");
        break;
    case 2:
        printf("Two");
        break;
    case 3:
        printf("Three");
        break;
    case 4:
        printf("Four");
        break;
    case 5:
        printf("Five");
        break;
    case 6:
        printf("Six");
        break;
    case 7:
        printf("Seven");
        break;
    case 8:
        printf("Eight");
        break;
    case 9:
        printf("Nine");
        break;
    default:
        break;
    }
}

void main(void)
{
    int num, tens, ones;

    printf("Enter the number : ");
    scanf("%d", &num);
    tens = num / 10;
    ones = num % 10;

    if (ones == 0 && tens == 0)
    {
        printf("Zero");
    }

    switch (tens)
    {
    case 9:
        printf("Ninety ");
        break;
    case 8:
        printf("Eighty ");
        break;
    case 7:
        printf("Seventy ");
        break;
    case 6:
        printf("Sixty ");
        break;
    case 5:
        printf("Fifty ");
        break;
    case 4:
        printf("Forty ");
        break;
    case 3:
        printf("Thirty ");
        break;
    case 2:
        printf("Twenty ");
        break;
    case 1:
        switch (ones)
        {
        case 0:
            printf("Ten");
            break;
        case 1:
            printf("Eleven");
            break;
        case 2:
            printf("Twelve");
            break;
        case 3:
            printf("Thirteen");
            break;
        case 4:
            printf("Fourteen");
            break;
        case 5:
            printf("Fifteen");
            break;
        case 6:
            printf("Sixteen");
            break;
        case 7:
            printf("Seventeen");
            break;
        case 8:
            printf("Eighteen");
            break;
        case 9:
            printf("Nineteen");
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    if (tens != 1)
        first_num(ones);
}