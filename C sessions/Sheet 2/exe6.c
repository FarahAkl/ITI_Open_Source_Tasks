#include <stdio.h>
#include <math.h>

void main(void)
{
    float a, b, c, res;
    printf("Enter the 3 Coefficients : ");
    scanf("%f %f %f", &a, &b, &c);

    float d = b * b - 4 * a * c;

    if (a == 0)
    {
        printf("This is not a quadritic equation");
    }
    else if (d < 0)
    {
        printf("This equation has no real solutions");
    }
    else if (d == 0)
    {
        res = b * -1 / (2 * a);
        printf("Result  = %f", res);
    }
    else
    {
        res = (b * -1 + sqrt(d)) / (2 * a);
        printf("First Result  = %f\n", res);

        res = (b * -1 - sqrt(d)) / (2 * a);
        printf("Second Result  = %f", res);
    }
}