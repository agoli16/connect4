/*
 * connect.c
 *
 *  Created on: Sep 17, 2023
 *      Author: anishgoli
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define rows 6
#define column 7

char Board[rows][column];
int tokenstowin;
char c = 'i';

int IsValidToken() {
    int tempvar;
    if ((scanf("%d", &tempvar) == 1) && (tempvar >= 3) && (tempvar <= 5)) {
        return tempvar;
    } else {
        printf("Invalid input. Please choose between 3, 4 or 5: ");
        while (getchar() != '\n');
        return IsValidToken();
    }
}

void MakeBoard() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < column; j++) {
            Board[i][j] = ' ';
        }
    }
}

void PrintBoard() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            printf("|%c", Board[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------\n");
}

int IsColFull(char board[rows][column], int input) {
    return board[0][input] != ' ';
}

void EditBoard(char board[rows][column], int col, bool player) {
    char token = player ? 'R' : 'Y';
    for (int i = rows - 1; i >= 0; i--) {
        if (board[i][col] == ' ') {
            board[i][col] = token;
            break;
        }
    }
}

int Checkwin(char board[rows][column], bool player, int tokens_to_win) {
    char plyr = player ? 'R' : 'Y';
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < column; col++) {
            // Check horizontally
            int horizontal_count = 0;
            for (int k = 0; k < tokens_to_win; k++) {
                if (col + k < column && board[row][col + k] == plyr) {
                    horizontal_count++;
                } else {
                    break;
                }
            }
            if (horizontal_count == tokens_to_win) {
                return 1;
            }

            // Check vertically
            int vertical_count = 0;
            for (int k = 0; k < tokens_to_win; k++) {
                if (row + k < rows && board[row + k][col] == plyr) {
                    vertical_count++;
                } else {
                    break;
                }
            }
            if (vertical_count == tokens_to_win) {
                return 1;
            }

            // Check diagonally (top-left to bottom-right)
            int diagonal_count = 0;
            for (int k = 0; k < tokens_to_win; k++) {
                if (row + k < rows && col + k < column && board[row + k][col + k] == plyr) {
                    diagonal_count++;
                } else {
                    break;
                }
            }
            if (diagonal_count == tokens_to_win) {
                return 1;
            }

            // Check diagonally (top-right to bottom-left)
            diagonal_count = 0;
            for (int k = 0; k < tokens_to_win; k++) {
                if (row + k < rows && col - k >= 0 && board[row + k][col - k] == plyr) {
                    diagonal_count++;
                } else {
                    break;
                }
            }
            if (diagonal_count == tokens_to_win) {
                return 1;
            }
        }
    }
    return 0;
}

int CheckDraw(char board[rows][column]) {
    for (int j = 0; j < column; j++) {
        if (board[0][j] == ' ') {
            return 0;
        }
    }
    return 1;
}

int main() {
    do {
        char p1name[10], p2name[10];
        char input;
        bool currentplayer = true;
        int col;

        printf("What is the name of Player 1? ");
        scanf("%s", p1name);
        printf("What is the name of Player 2? ");
        scanf("%s", p2name);
        printf("%s is Red and %s is Yellow\n", p1name, p2name);
        printf("How many tokens are needed to win: 3, 4, or 5? ");
        tokenstowin = IsValidToken();
        MakeBoard();

        do {
            PrintBoard();
            if (currentplayer) {
                printf("Red to play. Pick a column (1-7): ");
            } else {
                printf("Yellow to play. Pick a column (1-7): ");
            }
            scanf("%d", &col);
            col--;
            if ((col < 0) || (col >= column) || IsColFull(Board, col)) {
                printf("Invalid input. Try again.\n");
                continue;
            }
            EditBoard(Board, col, currentplayer);

            if (Checkwin(Board, currentplayer, tokenstowin)) {
                PrintBoard();
                if (currentplayer) {
                    printf("Congratulations, %s has won!\n", p1name);
                } else {
                    printf("Congratulations, %s has won!\n", p2name);
                }
                break;
            }

            if (CheckDraw(Board)) {
                PrintBoard();
                printf("It's a draw!\n");
                break;
            }

            currentplayer = !currentplayer;

        } while (1);

        printf("Press q to quit. Press anything else to play again: ");
        scanf(" %c", &input);
        if (input != 'q') {
            continue;
        } else {
            break;
        }
    } while (1);

    return 0;
}
