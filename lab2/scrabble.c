#include <stdio.h>
#include <string.h>
#include <ctype.h>

void get_word(char player[]);
int get_score(int points[], char word[]);
int result(int score_1, int score_2);

int main(void) {
    // Letters' value. Alphabetical order.
    int points[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

    // Variables for players' input.
    char player_1[50];
    char player_2[50];

    // Variables for players' score.
    int score_1 = 0;
    int score_2 = 0;

    // Store players' input.
    printf("Player 1, enter your word: \n");
    get_word(player_1);

    printf("Player 2, enter your word: \n");
    get_word(player_2);

    // Get players' score.
    score_1 = get_score(points, player_1);
    score_2 = get_score(points, player_2);

    // Get the winner.
    result(score_1, score_2);

    return 0;
}

// Get players input.
void get_word(char player[]) {
    scanf("%s", player);
}

// Calculate score.
int get_score(int points[], char word[]) {
    int score = 0;
    for (int i = 0; i < strlen(word); i++) {
        score += points[tolower(word[i]) - 97];
    }
    return score;
}

int result(int score_1, int score_2) {
    if (score_1 > score_2) {
        printf("The winner is player 1!\nHe scored %i points.\nPlayer 2 scored %i points.\n", score_1, score_2);
    }
    else if (score_1 < score_2) {
        printf("The winner is player 2!\nHe scored %i points.\nPlayer 1 scored %i points.\n", score_2, score_1);
    }
    else {
        printf("It's a draw.\nPlayer 1: %i points.\nPlayer 2: %i points.\n", score_1, score_2);
    }

    return 0;
}