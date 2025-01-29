#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 1 = Found, 0 = Not Found
int is_string_in_block(char block[6][5], char* search_str);

int main() {
    srand((uint) time(NULL));

    char block[6][5] = {
        { 'P', 'J', 'P', 'L', 'I' },
        { 'S', 'D', 'H', 'X', 'A' },
        { 'Q', 'R', 'J', 'D', 'G' },
        { 'S', 'K', 'W', 'X', 'A' },
        { 'E', 'S', 'Z', 'P', 'H' },
        { '0', '8', '6', '9', 'K' }
    };
        
    /* /// Generate Block */
    /* for (int i = 0; i < 5; i++) { */
    /*     for (int j = 0; j < 5; j++) { */
    /*         block[i][j] = (char) ((double) rand() / RAND_MAX * 26 + 'A'); */
    /*     } */
    /* } */
    /* const char* student_digits = "0869K"; */
    /* for (int j = 0; j < 6; j++) { */
    /*     block[5][j] = student_digits[j]; */
    /* } */
    
    /// Print Block
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", block[i][j]);
        }
        printf("\n");
    }

    /// Input
    char input[7];
    int score = 0;
    while (1) {
        printf("Enter text to search in all rows and columns (type END to stop): ");
        scanf(" %6s", input);
        if (strcmp(input, "END") == 0) {
            break;
        }
        if (is_string_in_block(block, input)) {
            score++;
            printf("Text found in block! New score: %d\n", score);
        } else {
            score--;
            printf("Text NOT found in block! New score: %d\n", score);
        }
    }
}

int is_string_in_block(char block[6][5], char* search_str) {
    int started_matching = 0, search_str_index = 0;
    // Horizontal Search
    size_t str_len = strlen(search_str);
    for (int i = 0; i < 6; i++) {
        started_matching = 0;
        search_str_index = 0;
        for (int j = 0; j < 5; j++) {
            char search_char = search_str[search_str_index];
            printf("[%d][%d]: search: %c, matching: %d, search_str_index: %d\n",
                   i, j, search_char, started_matching, search_str_index);
            if (str_len == 1 && block[i][j] == search_char)
                return 1;
            else if (started_matching && search_str_index == str_len - 1)
                return 1;
            else if (started_matching && block[i][j] != search_char) {
                started_matching = 0;
                search_str_index = 0;
            } else if (block[i][j] == search_char) {
                started_matching = 1;
                search_str_index++;
            }
        }
    }
    /* // Vertical Search */
    /* for (int j = 0; j < 5; j++) { */
    /*     started_matching = 0; */
    /*     search_str_index = 0; */
    /*     for (int i = 0; i < 6; i++) { */
    /*         if (started_matching && search_str_index == strlen(search_str) - 1) { */
    /*             return 1; */
    /*         } */
    /*         else if (started_matching && block[i][j] != search_str[search_str_index]) { */
    /*             started_matching = 0; */
    /*             search_str_index = 0; */
    /*         } else if (block[i][j] == search_str[search_str_index]) { */
    /*             started_matching = 1; */
    /*             search_str_index++; */
    /*         } */
    /*     } */
    /* } */
    return 0;
}
