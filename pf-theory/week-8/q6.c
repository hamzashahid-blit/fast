#include <stdio.h>

int sticks_on_first_turn(int n) {
    return (n % 5 == 0) ? -1 : n % 5;
}

int main() {
    printf("Enter the number of matchsticks on the table: ");
    int matchstick_count = 0;
    scanf("%d", &matchstick_count);
    
    int game_result = sticks_on_first_turn(matchstick_count);
    if (game_result == -1) {
        printf("It is impossible for A to win... :(\n");
    } else {
        printf("A needs to pick up %d matchsticks on their first turn to win! :D\n", game_result);
    }
    
    return 0;
}
