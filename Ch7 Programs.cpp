// Ch7 Programs.cpp : Tic Tac Toe

#include <iostream>
#include <array>
#include <iomanip>

using namespace std;

const int N = 3;
//initialize Board, fills empty spaces with *
void initializeBoard(array<array<char, N>, N>& board) 
{
    for (int r = 0; r < N; ++r)//loops through every row, 0-2
        for (int c = 0; c < N; ++c)//loops through every column 0-2
            board[r][c] = '*';//assigns * to each spot
}
//Function formats the board in a nice grid
void displayBoard(const array<array<char, N>, N>& board)
{
    cout << "\n   ";//indent for column headers
    for (int c = 0; c < N; ++c)//loops through each column 0, 1, and 2
    {
        cout << setw(4) << c + 1;//prints column numbers spaced out
    }
    cout << "\n";
    cout << "     " << string(N * 4 - 1, '=') << "\n";//prints a seperator line
    for (int r = 0; r < N; ++r)//loops through each row 0, 1, and 2
    {
        cout << "|" << setw(1) << r + 1 << "|";//prints row number
        for (int c = 0; c < N; ++c) 
        {
            cout << setw(4) << board[r][c];//prints each cell stored in the board, spaced evenly
        }
        cout << "\n\n";
    }
    cout << "\n";
}

//checks valid input
bool isValidMove(const array<array<char, N>, N>& board, int row, int col)
{
    if (row < 0 || row >= N || col < 0 || col >= N) return false;//Check the move is within range 1-3
    return board[row][col] == '*';//check to make sure the cell was empty
}
//check for the win
bool checkWin(const array<array<char, N>, N>& board, char p)
{
    //check rows
    for (int r = 0; r < N; ++r)//loops through each row
    {
        bool rowWin = true;//assumes true then trys to prove it wrong
        for (int c = 0; c < N; ++c)//loops through the column of each row
        {
            if (board[r][c] != p)//checks to see if the column of each row matches the current player
            {
                rowWin = false;
                break;
            }
        }
        if (rowWin) return true;
    }
    //check columns, works the same as above but checks columns then rows
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

    //Check top left to bottow right diagonal
    bool Back_Slash = true;
    for (int i = 0; i < N; ++i)//loops through the each index
    {
        if (board[i][i] != p)//checks if cells 00, 11, ans 22 all equal the current player
        {
            Back_Slash = false;
            break;
        }
    }
    if (Back_Slash) return true;

    //Check top right to bottom left diagonal
    bool ForwardSlash = true;
    for (int i = 0; i < N; ++i)//;loops though each index
    {
        if (board[i][N - 1 - i] != p)//checks if cells 02,11, and 20 are equal to the current player. 
        {
            ForwardSlash = false;
            break;
        }
    }
    if (ForwardSlash) return true;

    return false;
}

bool checkDraw(const array<array<char, N>, N>& board)//function to check for a draw
{
    for (int r = 0; r < N; ++r)//loops through each roww
        for (int c = 0; c < N; ++c)//loops through each column
            if (board[r][c] == '*') return false;//checks for empty spcase 
    return true;
}

void makeMove(array<array<char, N>, N>& board, int row, int col, char p)//function to place the X and O
{
    board[row][col] = p;//updates the board
}

char switchPlayer(char p)//switches between player
{
    return (p == 'X') ? 'O' : 'X';//if p is X, return O, otherwise retune X
}

int main()
{
    array<array<char, N>, N> board;//creates the board
    initializeBoard(board);//fills the empty space with *

    char current = 'X';//X goes first
    cout << "Tic-Tac-Toe (Player X vs Player O)\n";
    displayBoard(board);//prints board

    while (true)
    {
        int row, col;
        cout << "Player " << current << ", enter your move (row col, 1-3 1-3): ";
        if (!(cin >> row >> col))
        {
            cout << "Invalid input. Try again.\n";
            cin.clear();//clear the error state
            cin.ignore(1000, '\n');//throw away the bad input
            continue;//restart the loop
        }
        
        row -= 1; col -= 1;//convert to 0-based

        if (!isValidMove(board, row, col))
        {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        makeMove(board, row, col, current);//updates the board
        displayBoard(board);//prints updated board

        if (checkWin(board, current))//checks for win
        {
            cout << "Player " << current << " wins!\n";
            break;
        }
        if (checkDraw(board))//checks for draw
        {
            cout << "It's a draw!\n";
            break;
        }

        current = switchPlayer(current);//switches player
    }

    return 0;
}