#include <stdio.h>

int main() {
    int n, i, j, min, max, temp;
    int a[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (i = 0; i < n / 2; i++) {
        min = i;
        max = i;

        for (j = i + 1; j < n - i; j++) {
            if (a[j] < a[min])
                min = j;

            if (a[j] > a[max])
                max = j;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;

        if (max == i)
            max = min;

        temp = a[n - i - 1];
        a[n - i - 1] = a[max];
        a[max] = temp;
    }

    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}