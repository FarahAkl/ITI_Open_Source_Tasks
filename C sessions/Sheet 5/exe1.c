#include <stdio.h>

void main(void)
{
    int size;
    printf("Enter the size :");
    scanf("%d", &size);

    int arr[size];
    int evenArr[size];
    int oddArr[size];

    int evenIndex = 0;
    int oddIndex = 0;

    printf("Enter the array : ");

    for (int i = 0; i < size;i++){
        scanf("%d", &arr[i]);

        if(arr[i]%2==0){
            evenArr[evenIndex] = arr[i];
            evenIndex++;
        }else{
            oddArr[oddIndex] = arr[i];
            oddIndex++;
        }
    }

    printf("\n The original array : ");
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    printf("\n The even array : ");
    for (int i = 0; i < evenIndex; i++)
    {
        printf("%d ", evenArr[i]);
    }

    printf("\n The odd array : ");
    for (int i = 0; i < oddIndex; i++)
    {
        printf("%d ", oddArr[i]);
    }
}