#ifndef BOARD
#define BOARD
#include <vector>
#include <limits>
#include <string>
using namespace std;
const int inf = (std::numeric_limits<int>::max());

class Board {
private:
    char board[3][3];
public:
    Board();
    Board(char board[][3]);
    bool hasNoEmptyCells() const;
    bool isEmpty(int i, int j) const;
    char* operator[](int i);
    string getRow(int row) const;
    string getCol(int col) const;
    string getMainDiagonal() const;
    string getSecondaryDiagonal() const;
    void print() const;
    vector<Board> getChildren(char player);
};

#endif
