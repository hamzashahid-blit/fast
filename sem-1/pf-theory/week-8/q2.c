#include<stdio.h>
#include<string.h>

#define SLOGANS_CAPACITY 10
#define SLOGAN_CAPACITY 50
#define LETTER_COUNT 26

int main() {
    char slogans[SLOGANS_CAPACITY][SLOGAN_CAPACITY + 1];
    int slogan_count = 0;

    /// Taking input
    printf("Enter 10 or less slogans, and enter '-' to stop.\n");
    for (int i = 0; i < SLOGANS_CAPACITY; i++) {
        printf("Slogan #%d: ", i+1);
        scanf(" %50[^\n]", slogans[i]);
        if (strcmp(slogans[i], "-") == 0)
            break;
        slogan_count++;
    }

    /// Filling the buckets
    int letter_freqs[LETTER_COUNT];
    memset(letter_freqs, 0, sizeof(letter_freqs)); // sizeof works cz auto-alloc array
    for (int i = 0; slogans[i] != NULL && i < SLOGANS_CAPACITY; i++) {
        for (int j = 0; slogans[i][j] != '\0'; j++) {
            if (slogans[i][j] >= 'a' && slogans[i][j] <= 'z') {
                letter_freqs[slogans[i][j] - 'a']++;
            } else if (slogans[i][j] >= 'A' && slogans[i][j] <= 'Z') {
                letter_freqs[slogans[i][j] - 'A']++;
            }
        }
    }

    /// Printing the buckets
    int has_printed = 0;
    for (int i = 0; i < LETTER_COUNT; i++) {
        if (letter_freqs[i] == 0) continue;
        if (!has_printed) {
            has_printed = 1;
            printf("'%c': %d", 'A' + i, letter_freqs[i]);
        }
        else printf(", '%c': %d", 'A' + i, letter_freqs[i]);
    }
    printf("\n");
    
    return 0;
}
