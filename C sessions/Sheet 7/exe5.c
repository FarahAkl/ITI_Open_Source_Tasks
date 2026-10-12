
#include <stdio.h>

struct Customer
{
    char name[50];
    int accountNumber;
    float balance;
};

void printLowBalance(struct Customer customers[], int size);
void addBonus(struct Customer customers[], int size);

int main()
{
    int size;

    printf("Enter number of customers: ");
    scanf("%d", &size);

    struct Customer customers[size];

    for (int i = 0; i < size; i++)
    {
        printf("\nEnter customer %d information:\n", i + 1);

        printf("Name: ");
        scanf(" %49[^\n]", customers[i].name);

        printf("Account Number: ");
        scanf("%d", &customers[i].accountNumber);

        printf("Balance: ");
        scanf("%f", &customers[i].balance);
    }

    printf("\nCustomers with balance less than $200:\n");
    printLowBalance(customers, size);

    printf("\nCustomers with balance more than $1000 after increment:\n");
    addBonus(customers, size);

    return 0;
}

void printLowBalance(struct Customer customers[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (customers[i].balance < 200)
        {
            printf("%s\n", customers[i].name);
        }
    }
}

void addBonus(struct Customer customers[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (customers[i].balance > 1000)
        {
            customers[i].balance += 100;

            printf("Name: %s, New Balance: %.2f\n",
                   customers[i].name,
                   customers[i].balance);
        }
    }
}
