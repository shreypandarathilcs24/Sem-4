#include <stdio.h>
#define N 5  // Change this to solve for any board size

int board[N][N];

// Check if placing a queen at (row, col) is safe
int isSafe(int row, int col) {
    // Check column above
    for (int i = 0; i < row; i++)
        if (board[i][col]) return 0;

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return 0;

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j]) return 0;

    return 1;  // Safe to place
}

// Print the board
void printBoard() {
    static int count = 0;
    printf("\nSolution %d:\n", ++count);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%s ", board[i][j] ? "Q" : ".");
        printf("\n");
    }
}

// Backtracking function: place queens row by row
void solve(int row) {
    if (row == N) {   // All N queens placed successfully
        printBoard();
        return;
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;   // Place queen
            solve(row + 1);        // Recurse to next row
            board[row][col] = 0;   // Backtrack (remove queen)
        }
    }
}

int main() {
    printf("N-Queens Solutions for N = %d:\n", N);
    solve(0);  // Start from row 0
    return 0;
}
