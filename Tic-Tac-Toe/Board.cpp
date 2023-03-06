#include "Board.hpp"
#include <iostream>
Board::Board()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

Board::Board(char board[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->board[i][j] = board[i][j];
        }
    }
}

bool Board::hasNoEmptyCells() const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isEmpty(i, j))
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::isEmpty(int i, int j) const
{
    return board[i][j] == ' ';
}

char* Board::operator[](int i)
{
    return board[i];
}

string Board::getRow(int row) const
{
    string value = string() + board[row][0] + board[row][1] + board[row][2];
    return value;
}

string Board::getCol(int col) const
{
    string value = string() + board[0][col] + board[1][col] + board[2][col];
    return value;
}

string Board::getMainDiagonal() const
{
    string value = string() + board[0][0] + board[1][1] + board[2][2];
    return value;
}

string Board::getSecondaryDiagonal() const
{
    string value = string() + board[0][2] + board[1][1] + board[2][0];
    return value;
}

void Board::print() const
{
    for (int i = 0; i < 3; i++)
    {
        std::cout << " | ";
        for (int j = 0; j < 3; j++)
        {
            std::cout << board[i][j] << " | ";
        }
        std::cout << std::endl;
    }
    printf("\n\n");
}

vector<Board> Board::getChildren(char player)
{
    vector<Board> children;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!isEmpty(i, j))
            {
                continue;
            }
            Board nextState = Board(this->board);
            nextState[i][j] = player;
            children.push_back(nextState);
        }
    }
    return children;
}