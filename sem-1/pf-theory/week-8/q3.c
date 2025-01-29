#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENTENCES_CAP 10
#define SENTENCE_CAP 50

typedef struct {
    int compress_count;
    char* str;
} Compressed;

Compressed* compress_str(char* input);

int main()
{
    char sentences[SENTENCES_CAP][SENTENCE_CAP + 1];
    memset(sentences, 0, sizeof(sentences)); // sizeof works cz auto-alloc array
    int sentences_count = 0;
    printf("Enter 10 or less sentences/words, and enter '-' to stop.\n");
    for (int i = 0; i < SENTENCES_CAP; i++) {
        printf("Sentence/Word #%d: ", i+1);
        scanf(" %50[^\n]", sentences[i]);
        if (strcmp(sentences[i], "-") == 0)
            break;
        sentences_count++;
    }

    Compressed* compressed = NULL;
    printf("\nCompressed: ");
    for (int i = 0; i < sentences_count; i++) {
        if (i != 0) printf(", ");
        compressed = compress_str(sentences[i]);
        if (!compressed) {
            printf("[ERROR] Unable to compress!");
            return -1;
        }
        printf("\"%s\" (%d removed)", compressed->str, compressed->compress_count);
        free(compressed->str);
        compressed = NULL;
    }
    printf("\n");
        
    return 0;
}

// Assignment said to do compression in a func so I had to leave
// mem-management up to the caller... cant be returning freed ptrs
Compressed* compress_str(char* input)
{
    int output_bytes = (strlen(input) + 1) * sizeof(char);
    char* output = malloc(output_bytes);
    memset(output, 0, output_bytes);

    char prev_char = 0, curr_char = 0;
    int compress_count = 0;
    for (int i = 0, j = 0; input[i] != '\0'; i++, j++) {
        prev_char = curr_char;
        curr_char = input[i];
        if (prev_char == curr_char) {
            j--;
            compress_count++;
        }
        output[j] = input[i];
    }
    
    return &(Compressed){
        .compress_count = compress_count,
        .str = output,
    };
}
