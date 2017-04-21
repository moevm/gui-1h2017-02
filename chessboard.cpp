// Шахматная доска - реализация
// ----------------------------
#include <QtGui>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include "chessboard.h"
#include "ui_chessboard.h"
#include "chessmodel.h"




void ChessBoard::addChessPieceInCell(int row, int column, QString name)
{

    if(name.isEmpty())
    {
        if(boardMap[row][column]!=NULL)
        {

            boardMap[row][column]->deleteLater();
            boardMap[row][column]=NULL;
        }
    }
    else
    {
//        arr[row][column]=new Score(this,5,true,row,column);
        if(boardMap[row][column]==NULL)
        {
            boardMap[row][column]= new ChessPiece(this,color(name.constData()[0]),char2pieceType(name.constData()[1]), row,column);
        }
        else
        {
            boardMap[row][column]->deleteLater();
            boardMap[row][column]= new ChessPiece(this,color(name.constData()[0]),char2pieceType(name.constData()[1]), row,column);

        }
    }
}

void ChessBoard::clearBoard()
{


}

void ChessBoard::convert()
{

     ChessField::clearFigure();
    for(int i = 0; i <8;i++)
    {
        for(int j = 0; j < 8 ;j++)
        {
            if(arr[i][j]!=NULL)
            {
                arr[i][j]->deleteLater();
                arr[i][j]=NULL;
            }
            if(boardMap[i][j]!=NULL)
            {//, , , , , ,
                bool color = true;
                switch (boardMap[i][j]->side)
                {
                    case BLACK:
                    color = false;
                    break;
                    case WHITE:
                    color = true;
                    break;
                }

                switch (boardMap[i][j]->type) {
                case PAWN:
                    //Pawn *f(color,i,j);
                    ChessField::addFigure(new Pawn(color, i, j),i,j);
                    break;
                case ROOK:
//                    Rook *f(color,i,j);
                    ChessField::addFigure(new Rook(color, i, j),i,j);
                    break;
                case KNIGHT:
//                    Knight *f(color,i,j);
                    ChessField::addFigure(new Knight(color, i, j),i,j);
                    break;
                case BISHOP:
//                    Bishop *f(color,i,j);
                    ChessField::addFigure(new Bishop(color, i, j),i,j);
                    break;
                case QUEEN:
//                    Queen *f(color,i,j);
                    ChessField::addFigure(new Queen(color, i, j),i,j);
                    break;
                case KING:
//                    King *f(color,i,j);
                    ChessField::addFigure(new King(color, i, j),i,j);
                    break;
                default:
                    break;
                }

            }
        }
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



