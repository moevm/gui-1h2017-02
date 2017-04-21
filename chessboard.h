#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QFrame>
#include "chesspiece.h"

#include "addition.h"
#include <QVector>
#include "score.h"
namespace Ui {
class ChessBoard;
}

// Шахматная доска - опредение
// ---------------------------
class ChessBoard : public QFrame {
  Q_OBJECT


 public:

  explicit ChessBoard(QWidget* parent = 0);
  ~ChessBoard();
  void addChessPieceInCell(int row, int column, QString name);
  void clearBoard();
  void convert();


 private:
  //соответствие клеткам и фигурам, которые ими заняты, тоесть расположение фигур на доске
  ChessPiece* boardMap[8][8];
  Score* arr[8][8];


  Ui::ChessBoard* ui;
};

#endif // CHESSBOARD_H
