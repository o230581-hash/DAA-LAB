#include <stdio.h>

int main() {
    int n, i, max = 0;
    int a[100], count[100] = {0};

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i] > max)
            max = a[i];
    }

    for (i = 0; i < n; i++)
        count[a[i]]++;

    printf("Sorted array: ");
    for (i = 0; i <= max; i++) {
        while (count[i] > 0) {
            printf("%d ", i);
            count[i]--;
        }
    }

    return 0;
}