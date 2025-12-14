// Ch7 Programs.cpp : Tic Tac Toe

#include <iostream>
#include <array>
#include <iomanip>

using namespace std;

const int N = 3;

void initBoard(array<array<char, N>, N>& board)//fills empty spaces with *
{
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            board[r][c] = '*';
}

void printBoard(const array<array<char, N>, N>& board)//Function to print the board
{
    cout << "\n   ";//indent for column headers
    for (int c = 0; c < N; ++c)
    {
        cout << setw(4) << c + 1;//column numbers spaced out
    }
    cout << "\n";
    cout << "     " << string(N * 4 - 1, '=') << "\n";
    for (int r = 0; r < N; ++r)
    {
        cout << "|" << setw(1) << r + 1 << "|";//row number
        for (int c = 0; c < N; ++c) 
        {
            cout << setw(4) << board[r][c];//each cell spaced evenly
        }
        cout << "\n\n";
    }
    cout << "\n";
}


bool isValidMove(const array<array<char, N>, N>& board, int row, int col)
{
    if (row < 0 || row >= N || col < 0 || col >= N) return false;
    return board[row][col] == '*';
}

bool checkWin(const array<array<char, N>, N>& board, char p)
{
    // Check rows
    for (int r = 0; r < N; ++r)
    {
        bool rowWin = true;
        for (int c = 0; c < N; ++c)
        {
            if (board[r][c] != p)
            {
                rowWin = false;
                break;
            }
        }
        if (rowWin) return true;
    }

    // Check columns
    for (int c = 0; c < N; ++c)
    {
        bool colWin = true;
        for (int r = 0; r < N; ++r)
        {
            if (board[r][c] != p)
            {
                colWin = false;
                break;
            }
        }
        if (colWin) return true;
    }

    // Check main diagonal
    bool mainDiagWin = true;
    for (int i = 0; i < N; ++i)
    {
        if (board[i][i] != p)
        {
            mainDiagWin = false;
            break;
        }
    }
    if (mainDiagWin) return true;

    // Check anti-diagonal
    bool antiDiagWin = true;
    for (int i = 0; i < N; ++i)
    {
        if (board[i][N - 1 - i] != p)
        {
            antiDiagWin = false;
            break;
        }
    }
    if (antiDiagWin) return true;

    return false;
}

bool checkDraw(const array<array<char, N>, N>& board)
{
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            if (board[r][c] == '*') return false;
    return true;
}

void makeMove(array<array<char, N>, N>& board, int row, int col, char p)
{
    board[row][col] = p;
}

char switchPlayer(char p)
{
    return (p == 'X') ? 'O' : 'X';
}

int main()
{
    array<array<char, N>, N> board;
    initBoard(board);

    char current = 'X';
    cout << "Tic-Tac-Toe (Player X vs Player O)\n";
    printBoard(board);

    while (true)
    {
        int row, col;
        cout << "Player " << current << ", enter your move (row col, 1-3 1-3): ";
        if (!(cin >> row >> col))
        {
            cout << "Invalid input. Exiting.\n";
            return 0;
        }

        // Convert to 0-based
        row -= 1; col -= 1;

        if (!isValidMove(board, row, col))
        {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        makeMove(board, row, col, current);
        printBoard(board);

        if (checkWin(board, current))
        {
            cout << "Player " << current << " wins!\n";
            break;
        }
        if (checkDraw(board))
        {
            cout << "It's a draw!\n";
            break;
        }

        current = switchPlayer(current);
    }

    return 0;
}