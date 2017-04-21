#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QLabel>
#include <QMetaEnum>
#include <QStaticAssertFailure>
#include "game.h"
#include <QVector>

class ChessBoard;

// Шахматная фигура
class ChessPiece : public QLabel {
  Q_OBJECT

 public:

  ChessPiece(ChessBoard* parent, PlayerSide side, PieceType type,
             int row, int col);
  ~ChessPiece();
  // Выровнять фигуру по сетке
  void alignToGrid();
// public:
  // parent - шахматная доска
  // side - цвет: чёрный / белый
  // type - тип фигуры
  // row, col - строка и столбец 0..7
  PlayerSide side; // Белая / чёрная
  PieceType type;

  int row, col; // row - строка, col - столбец (0..7)

};



#endif // CHESSPIECE_H
