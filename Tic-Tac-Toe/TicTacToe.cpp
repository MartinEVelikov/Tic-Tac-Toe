#include "TicTacToe.hpp"
#include<iostream>
#include<vector>
//Private function definitions:
using namespace std;
bool TicTacToe::isTerminalState(const Board& board) const
{
    if (board.hasNoEmptyCells())
    {
        return true;
    }

    string mainDiagonal = board.getMainDiagonal();
    string secondaryDiagonal = board.getSecondaryDiagonal();

    if (mainDiagonal == WIN_MAX || secondaryDiagonal == WIN_MAX ||
        mainDiagonal == WIN_MIN || secondaryDiagonal == WIN_MIN)
    {
        return true;
    }

    for (int i = 0; i < 3; i++)
    {
        string row = board.getRow(i);
        string col = board.getCol(i);
        if (row == WIN_MAX || col == WIN_MAX ||
            row == WIN_MIN || col == WIN_MIN)
        {
            return true;
        }
    }
    return false;
}

int TicTacToe::getTerminalStateValue(const Board& board) const
{
    string mainDiagonal = board.getMainDiagonal();
    string secondaryDiagonal = board.getSecondaryDiagonal();

    if (mainDiagonal == WIN_MAX || secondaryDiagonal == WIN_MAX)
    {
        return 1;
    }

    if (mainDiagonal == WIN_MIN || secondaryDiagonal == WIN_MIN)
    {
        return -1;
    }

    for (int i = 0; i < 3; i++)
    {
        string row = board.getRow(i);
        string col = board.getCol(i);
        if (row == WIN_MAX || col == WIN_MAX)
        {
            return 1;
        }
        if (row == WIN_MIN ||
            col == WIN_MIN)
        {
            return -1;
        }
    }
    return 0;
}

int TicTacToe::MaxValue(Board& board, int alpha, int beta, int& depth)
{
    depth++;

    if (isTerminalState(board))
    {
        return getTerminalStateValue(board);
    }

    int best = -inf;
    vector<Board> children = board.getChildren(MAX_MOVE);
    for (auto& child : children)
    {
        best = std::max(best, MinValue(child, alpha, beta, depth));

        if (best >= beta)
        {
            return best;
        }

        alpha = std::max(alpha, best);
    }
    return best;
}

int TicTacToe::MinValue(Board& board, int alpha, int beta, int& depth)
{
    depth++;
    if (isTerminalState(board))
    {
        return getTerminalStateValue(board);
    }

    int best = inf;
    vector<Board> children = board.getChildren(MIN_MOVE);

    for (auto& child : children)
    {
        best = std::min(best, MaxValue(child, alpha, beta, depth));

        if (best <= alpha)
        {
            return best;
        }

        beta = std::min(beta, best);
    }
    return best;
}

Board TicTacToe::findBestMove(Board& board)
{
    int maxValue = -1;
    int bestDepth = inf;
    Board bestBoard = board;
    vector<Board> children = board.getChildren(MAX_MOVE);

    for (auto& child : children)
    {
        int depth = 0;
        int value = MinValue(child, -inf, inf, depth);

        if (value > maxValue)
        {
            maxValue = value;
            bestBoard = child;
            bestDepth = depth;
        }
        else if (value == maxValue && depth < bestDepth)
        {
            bestDepth = depth;
            bestBoard = child;
        }
    }
    return bestBoard;
}

//Public function definitions:

void TicTacToe::choosePlayer()
{   
    cout << "Do you want to be the first player? [y/n]: ";
    char c;
    cin >> c;
    firstPlayer = (c == 'y') ? whoWillBeFirst::HUMAN : whoWillBeFirst::AI;
}
void TicTacToe::start()
{
    Board board;
    if (firstPlayer == whoWillBeFirst::HUMAN)
    {
        board.print();
        int i, j;
        std::cout << "Type row(0-2) and col(0-2)\n";
        do
        {
            std::cin >> i >> j;
            if (i < 0 || i>2 || j < 0 || j>2)
            {
                std::cout << "Coordinates have to be in the range [0,2]!\nTry with correct coordinates!\n";
            }
        } while (i < 0 || i>2 || j < 0 || j>2);
        board[i][j] = MIN_MOVE;
        board.print();
    }
    int i, j;
    while (!isTerminalState(board))
    {
        board = findBestMove(board);
        board.print();
        if (isTerminalState(board))
        {
            break;
        }
        std::cout << "Type row(0-2) and col(0-2)\n";
        do
        {
            std::cin >> i >> j;
            if (i < 0 || i>2 || j < 0 || j>2)
            {
                std::cout << "Coordinates have to be in the range [0,2]!\nTry with correct coordinates!\n";
            }
            if (board[i][j] == 'X' || board[i][j] == 'O')
            {
                cout << "The slot is not empty!\n Please try again with different coordinates!\n";
            }
        } while (board[i][j] == 'X' || board[i][j] == 'O' || i < 0 || i>2 || j < 0 || j>2);
        board[i][j] = MIN_MOVE;
        board.print();
    }
}