#include "score.h"

Score::Score(ChessBoard *parent, int number, bool color,int _row, int _col):QLabel((QWidget*)parent)
{
    row=_row;
    col=_col;
    setText(QString::number(number));
    setBaseSize(5,5);
//    setStyleSheet();
    QPalette palette;
    if(color)
    {
    palette.setColor(QPalette::WindowText, Qt::green);
    }
    else
    {
        palette.setColor(QPalette::WindowText, Qt::red);
    }
    setPalette(palette);
    alignToGrid();
    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

void Score::alignToGrid() {
  move(col * CELL+3, row * CELL+3);
}
