#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRANSACTIONS_CAP 20
#define TRANSACTION_CAP 50

int is_anagram(char* lhs, char* rhs);

int main()
{
    char transactions[TRANSACTIONS_CAP][TRANSACTION_CAP + 1];
    memset(transactions, 0, sizeof(transactions)); // sizeof works cz auto-alloc array
    int transaction_count = 0;
    printf("Enter %d or less transactions, and enter '-' to stop.\n", TRANSACTIONS_CAP);
    for (int i = 0; i < TRANSACTIONS_CAP; i++) {
        printf("Transaction #%d: ", i+1);
        scanf(" %50[^\n]", transactions[i]);
        if (strcmp(transactions[i], "-") == 0)
            break;
        transaction_count++;
    }

    int grouped_indices[TRANSACTIONS_CAP][TRANSACTIONS_CAP];
    int recorded_indices[TRANSACTIONS_CAP];
    memset(grouped_indices, -1, sizeof(grouped_indices));
    memset(recorded_indices, 0, sizeof(recorded_indices));
    for (int i = 0; i < transaction_count; i++) {
        for (int j = 0; j < transaction_count; j++) {
            if (recorded_indices[j] == 0 &&
                is_anagram(transactions[i], transactions[j])) {
                recorded_indices[j] = 1;
                grouped_indices[i][j] = j;
            }
        }
    }

    printf("\nAnagram Groups: ");
    int is_printing_group = 0, is_first_group = 1;
    for (int i = 0; i < transaction_count; i++) {
        is_printing_group = 0;
        for (int j = 0; j < transaction_count; j++) {
            if (grouped_indices[i][j] != -1) {
                if (!is_printing_group) {
                    is_printing_group = 1;
                    if (!is_first_group) printf(", ");
                    printf("[");
                } else {
                    printf(", ");
                }
                printf("%s", transactions[grouped_indices[i][j]]);
                is_first_group = 0;
            }
        }
        if (is_printing_group) printf("]");
    }
    
    printf("\n");

    return 0;
}

int is_anagram(char* lhs, char* rhs) {
    int lhs_length = strlen(lhs);
    int rhs_length = strlen(rhs);
    if (lhs_length != rhs_length)
        return 0;

    char lhs_char = 0, rhs_char = 0; 
    int unmatch_count = 0, len = lhs_length; // len EXCLUDES null-term byte
    for (int i = 0; i < len; i++) {
        lhs_char = lhs[i];
        for (int j = 0; j < len; j++) {
            rhs_char = rhs[j];
            if (lhs_char != rhs_char) {
                unmatch_count++;
            } else {
                unmatch_count = 0;
                break;
            }
            if (unmatch_count == len) return 0;
        }
    }

    return 1;
}
