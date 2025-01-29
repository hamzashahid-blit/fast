#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void print_horizontal_histogram(const int* values, int value_count);
void print_vertical_histogram(const int* values, int value_count);
int take_histogram_input(int** values);

int main()
{
    int *values = NULL;
    int value_count = take_histogram_input(&values);
    print_horizontal_histogram(values, value_count);
    print_vertical_histogram(values, value_count);

    free(values);
    return 0;
}

void print_horizontal_histogram(const int* values, int value_count) {
    for (int i = 0; i < value_count; i++) {
        printf("%d | ", i);
        for (int j = 0; j < values[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void print_vertical_histogram(const int* values, int value_count) {
    int max = INT_MIN;
    for (int i = 0; i < value_count; i++) {
        if (values[i] > max) max = values[i];
    }

    char** histogram = malloc(value_count * sizeof(char*));
    for (int i = 0; i < value_count; i++) {
        histogram[i] = (char*) malloc(max * sizeof(char));
        memset(histogram[i], '*', values[i] * sizeof(char));
        memset(&histogram[i][values[i]], ' ', max - values[i] * sizeof(char));
    }

    for (int i = 0; i < max; i++) {
        for (int j = 0; j < value_count; j++) {
            printf("%c ", histogram[j][max - i - 1]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < value_count; i++) {
        printf("%d ", values[i]);
        free(histogram[i]);
    }
    free(histogram);   

    printf("\n");
}

// values is a pointer to which will be assigned an array
int take_histogram_input(int** values_ptr) {
    int value_count = 0;
    printf("Enter number of values you want to input: ");
    scanf("%d", &value_count);
    int* values = malloc(value_count * sizeof(int));
    memset(values, 0, value_count);
    for (int i = 0; i < value_count; i++) {
        printf("Enter value #%d: ", i+1);
        scanf("%d", &values[i]);
    }
    *values_ptr = values;
    return value_count;
}
