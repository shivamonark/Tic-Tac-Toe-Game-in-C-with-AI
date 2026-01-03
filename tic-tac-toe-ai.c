#include <stdio.h>

/* -------- GLOBAL BOARD -------- */
char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

/* -------- FUNCTION DECLARATIONS -------- */
void printBoard();
int checkWin(char p);
int movesLeft();
int minimax(int depth, int isMax);
void computerMove();
void clearInputBuffer();

/* -------- FUNCTIONS -------- */

void clearInputBuffer() {
    while (getchar() != '\n');
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i != 2)
            printf("\n---|---|---\n");
    }
    printf("\n\n");
}

int checkWin(char p) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == p && board[i][1] == p && board[i][2] == p) ||
            (board[0][i] == p && board[1][i] == p && board[2][i] == p))
            return 1;
    }

    if ((board[0][0] == p && board[1][1] == p && board[2][2] == p) ||
        (board[0][2] == p && board[1][1] == p && board[2][0] == p))
        return 1;

    return 0;
}

int movesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 1;
    return 0;
}

int minimax(int depth, int isMax) {
    if (checkWin('O')) return 10 - depth;
    if (checkWin('X')) return depth - 10;
    if (!movesLeft()) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int val = minimax(depth + 1, 0);
                    board[i][j] = ' ';
                    if (val > best) best = val;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int val = minimax(depth + 1, 1);
                    board[i][j] = ' ';
                    if (val < best) best = val;
                }
            }
        }
        return best;
    }
}

void computerMove() {
    int bestVal = -1000;
    int r = -1, c = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(0, 0);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    r = i;
                    c = j;
                }
            }
        }
    }
    board[r][c] = 'O';
}

/* -------- MAIN FUNCTION -------- */

int main() {
    int row, col;

    printf("TIC TAC TOE (You = X, Computer = O)\n");
    printf("Enter row and column (0-2)\n");

    while (1) {
        printBoard();

        printf("Your move (row col): ");

        if (scanf("%d %d", &row, &col) != 2) {
            printf("⚠ Invalid input! Enter numbers only.\n");
            clearInputBuffer();
            continue;
        }

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("⚠ Invalid move! Try again.\n");
            continue;
        }

        board[row][col] = 'X';

        if (checkWin('X')) {
            printBoard();
            printf("🎉 YOU WIN!\n");
            break;
        }

        if (!movesLeft()) {
            printBoard();
            printf("🤝 DRAW!\n");
            break;
        }

        computerMove();

        if (checkWin('O')) {
            printBoard();
            printf("🤖 COMPUTER WINS!\n");
            break;
        }
    }

    return 0;
}
