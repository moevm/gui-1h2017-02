#ifndef SCORE_H
#define SCORE_H
#include "game.h"
#include <QLabel>

class ChessBoard;

class Score : public QLabel
{
    Q_OBJECT
public:
    Score(ChessBoard* parent,int number, bool color,int _row, int _col);
    ~Score(){}
     int row, col;
     void alignToGrid();
};

#endif // SCORE_H
