#include <stdio.h>

void main(void)
{
    float salary, tax, net_salary;

    printf("Enter your salary : ");
    scanf("%f", &salary);

    if (salary <= 7000)
    {
        tax = 0;
    }
    else if (salary <= 20000)
    {
        tax = (salary - 7000) * 0.1;
    }
    else if (salary <= 45000)
    {
        tax = (20000 - 7000) * 0.1 + (salary - 20000) * 0.15;
    }
    else if (salary <= 200000)
    {
        tax = (45000 - 20000) * 0.15 + (20000 - 7000) * 0.1 + (salary - 45000) * 0.20;
    }
    else
    {
        tax = (200000 - 45000) * 0.2 + (45000 - 20000) * 0.15 + (20000 - 7000) * 0.1 + (salary - 200000) * 0.4;
    }

    net_salary = salary - tax;

    printf("Your net salary = %f", net_salary);
}