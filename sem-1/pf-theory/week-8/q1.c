#include<stdio.h>
#include<limits.h>
#define ARR_LENGTH 5

int main() {
    int arr[ARR_LENGTH];
    int input = 0, min = INT_MAX;
    for (int i = 0; i < ARR_LENGTH; i++) {
        printf("Enter element #%d: ", i);
        scanf("%d", &input);
        if (input >= 9999) {
            printf("Value must be less than 9999!\n");
            i--;
            continue;
        }
        arr[i] = input;
        if (arr[i] < min) min = arr[i];
    }
    
    int secondMin = INT_MAX;
    for (int i = 0; i < ARR_LENGTH; i++) {
        if (arr[i] != min && arr[i] < secondMin) {
            secondMin = arr[i];
        }
    }
    
    if (secondMin == INT_MAX) {
        printf("There is no second smallest (is your entire array filled with the same value?)\n");
    } else {
        printf("Second smallest number in the array is %d.\n", secondMin);
    }

    return 0;
}
