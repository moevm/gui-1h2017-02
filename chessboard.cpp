// Шахматная доска - реализация
// ----------------------------
#include <QtGui>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include "chessboard.h"
#include "ui_chessboard.h"




void ChessBoard::addChessPieceInCell(int row, int column, QString name)
{
    if(name.isEmpty())
    {
        if(boardMap[row][column]!=NULL)
        {
            boardMap[row][column]->deleteLater();

        }
    }
    else
    {
        boardMap[row][column]= new ChessPiece(this,BLACK,ROOK, row,column);
    }
}

ChessBoard::ChessBoard(QWidget* parent) :
  QFrame(parent),
  ui(new Ui::ChessBoard) {
  ui->setupUi(this);
  setAcceptDrops(true);

}

ChessBoard::~ChessBoard() {
  delete ui;
}



const char* mimeFormat = "application/x-chesspiece";



