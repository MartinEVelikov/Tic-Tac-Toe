#ifndef TIC_TAC_TOE
#define TIC_TAC_TOE
#include<string>
#include "Board.hpp"
class TicTacToe
{
private:
    std::string WIN_MAX = "XXX";
    std::string WIN_MIN = "OOO";
    char MAX_MOVE = 'X';
    char MIN_MOVE = 'O';

    bool isTerminalState(const Board& board) const;
    int getTerminalStateValue(const Board& board) const;
    int MaxValue(Board& board, int alpha, int beta, int& depth);
    int MinValue(Board& board, int alpha, int beta, int& depth);
    Board findBestMove(Board& board);

    enum class whoWillBeFirst { HUMAN, AI } firstPlayer;
public:
    void choosePlayer();
    void start();
};
#endif


