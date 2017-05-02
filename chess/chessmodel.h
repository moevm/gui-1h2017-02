#ifndef CHESSMODAL_H
#define CHESSMODAL_H
#include <iostream>
#include <algorithm>

using namespace std;

//enum FigureName{K, Q, R, N, B, p};

class ChessFigure {

protected:
    bool isWhite;
    //FigureName figureName;
    int row;
    int column;

public:
    ChessFigure(bool color, int x, int y) {
        isWhite = color;
        row = x;
        column  = y;
    }

    virtual void updateField()=0;

    ChessFigure& operator=(const ChessFigure&);
};

ChessFigure& ChessFigure::operator=(const ChessFigure& figure)
    {
    isWhite = (figure.isWhite);
    // figureName = (figure.figureName);
     row = (figure.row);
     column = (figure.column);
    return *this;
    }

class FieldCell {

public:
    ChessFigure* figure;
    int beatenByWhiteFigures;
    int beatenByBlackFigures;

public:
    FieldCell() {}

    ChessFigure* getFigure() {
        return figure;
    }

    bool isOccupiedByFigure() {
        return (figure != NULL);
    }

    void beatByWhite () {
        beatenByWhiteFigures++;
    }

    void beatByBlack () {
        beatenByBlackFigures++;
    }

    void addFigure(ChessFigure *newFigure) {
        figure = newFigure;
    }
};

class Rook;

class ChessField {
    private:
        static FieldCell arr[8][8];
    public:
        friend class Rook;
        friend class King;
        friend class Queen;
        friend class Bishop;
        friend class Pawn;
        friend class Knight;
        static const int tableSizeWidth;
        static const int tableSizeHeight;

        ChessField(){}

        static void beatCell(bool isBeatenByWhite, int i, int j) {
            if (isBeatenByWhite) {
                arr[i][j].beatByWhite();
            } else {
                arr[i][j].beatByBlack();
            }
        }

        static bool containsFigure(int i, int j) {
            return arr[i][j].isOccupiedByFigure();
        }

        static void updateField() {
            for (int i = 0; i < tableSizeHeight; i++) {
                for (int j = 0; j < tableSizeWidth; j++) {
                    if (arr[i][j].isOccupiedByFigure())
                        arr[i][j].getFigure()->updateField();
                }
            }
        }

        static void addFigure(ChessFigure *newFigure, int x, int y) {
            arr[x][y].addFigure(newFigure);
        }

        static void clearFigure()
        {

            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    arr[i][j].beatenByBlackFigures=0;
                    arr[i][j].beatenByWhiteFigures=0;
                    arr[i][j].figure=NULL;
//                    delete &arr[i][j];
                }
            }
        }

        static bool areCorrectCoordinates(int i, int j) {
            return (i >= 0 && j >= 0 && i < tableSizeHeight && j < tableSizeWidth);
        }
        static int numOfWhiteBeaters(int i, int j) {
                    return arr[i][j].beatenByWhiteFigures;
                }

                static int numOfBlackBeaters(int i, int j) {
                    return arr[i][j].beatenByBlackFigures;
                }
};

FieldCell ChessField::arr[8][8] = {FieldCell()};
const int ChessField::tableSizeHeight = 8;
const int ChessField::tableSizeWidth  = 8;

class Rook: public ChessFigure {
public:
    Rook (bool color, int x, int y):ChessFigure(color, x, y){}
    void updateField() {
        bool dir1 = true, dir2 = true, dir3 = true, dir4 = true;

        for (int i = 1; i < ChessField::tableSizeWidth && dir1; i++) {
            if (column + i < ChessField::tableSizeWidth) {
                if (isWhite)
                    ChessField::arr[row][column + i].beatByWhite();
                else
                    ChessField::arr[row][column + i].beatByBlack();

                if (ChessField::arr[row][column + i].isOccupiedByFigure())
                    dir1 = false;
            }
        }

        for (int i = 1; (i < ChessField::tableSizeWidth) && dir2; i++) {
            if (column - i >= 0) {
                if (isWhite)
                    ChessField::arr[row][column - i].beatByWhite();
                else
                    ChessField::arr[row][column - i].beatByBlack();

                if (ChessField::arr[row][column - i].isOccupiedByFigure())
                    dir2 = false;
            }
        }

        for (int i = 1; (i < ChessField::tableSizeHeight) && dir3; i++) {
            if (row + i < ChessField::tableSizeHeight) {
                if (isWhite)
                    ChessField::arr[row + i][column].beatByWhite();
                else
                    ChessField::arr[row + i][column].beatByBlack();

                if (ChessField::arr[row + i][column].isOccupiedByFigure())
                    dir3 = false;
            }
        }

        for (int i = 1; (i < ChessField::tableSizeHeight) && dir4; i++) {
            if (row - i >= 0) {
                if (isWhite)
                    ChessField::arr[row - i][column].beatByWhite();
                else
                    ChessField::arr[row - i][column].beatByBlack();

                if (ChessField::arr[row - i][column].isOccupiedByFigure())
                    dir4 = false;
            }
        }
    }
};

class King: public ChessFigure {
public:
   King(bool color, int i, int j): ChessFigure(color, i, j) {}
    void updateField() {
        for (int i = row - 1; i <= row + 1; i++){
            for (int j = column - 1; j <= column + 1; j++) {
                if (i >= 0 && j >= 0 && i < ChessField::tableSizeWidth && j < ChessField::tableSizeHeight) {
                    if (isWhite) {
                        ChessField::arr[i][j].beatByWhite();
                    } else {
                        ChessField::arr[i][j].beatByBlack();
                    }
                }
            }
        }
    }
};

class Queen: public ChessFigure {
public:
    Queen(bool color, int i, int j): ChessFigure(color, i, j) {}
    void updateField() {
        bool dir1 = true, dir2 = true, dir3 = true, dir4 = true;

        for (int i = 1; (i < max(ChessField::tableSizeHeight, ChessField::tableSizeWidth)) && dir1; i++) {
            if (row + i < ChessField::tableSizeHeight && column + i < ChessField::tableSizeWidth) {
                if (isWhite)
                    ChessField::arr[row + i][column + i].beatByWhite();
                else
                    ChessField::arr[row + i][column + i].beatByBlack();

                if (ChessField::arr[row + i][column + i].isOccupiedByFigure())
                    dir1 = false;
            }
        }

        for (int i = 1; (i < max(ChessField::tableSizeHeight, ChessField::tableSizeWidth)) && dir2; i++) {
            if (row - i >= 0 && column - i >= 0) {
                if (isWhite)
                    ChessField::arr[row - i][column - i].beatByWhite();
                else
                    ChessField::arr[row - i][column - i].beatByBlack();

                if (ChessField::arr[row - i][column - i].isOccupiedByFigure())
                    dir2 = false;
            }
        }

        for (int i = 1; (i < max(ChessField::tableSizeHeight, ChessField::tableSizeWidth)) && dir3; i++) {
            if (row + i < ChessField::tableSizeHeight && column - i >= 0) {
                if (isWhite)
                    ChessField::arr[row + i][column - i].beatByWhite();
                else
                    ChessField::arr[row + i][column - i].beatByBlack();

                if (ChessField::arr[row + i][column - i].isOccupiedByFigure())
                    dir3 = false;
            }
        }

        for (int i = 1; (i < max(ChessField::tableSizeHeight, ChessField::tableSizeWidth)) && dir4; i++) {
            if (row - i >= 0 && column + i < ChessField::tableSizeWidth)
            {
                if (isWhite)
                    ChessField::arr[row - i][column + i].beatByWhite();
                else
                    ChessField::arr[row - i][column + i].beatByBlack();

                if (ChessField::arr[row - i][column + i].isOccupiedByFigure())
                    dir4 = false;
            }
        }

        dir1 = true, dir2 = true, dir3 = true, dir4 = true;

        for (int i = 1; i < ChessField::tableSizeWidth && dir1; i++) {
            if (column + i < ChessField::tableSizeWidth) {
                if (isWhite)
                    ChessField::arr[row][column + i].beatByWhite();
                else
                    ChessField::arr[row][column + i].beatByBlack();

                if (ChessField::arr[row][column + i].isOccupiedByFigure())
                    dir1 = false;
            }
        }

        for (int i = 1; (i < ChessField::tableSizeWidth) && dir2; i++) {
            if (column - i >= 0) {
                if (isWhite)
                    ChessField::arr[row][column - i].beatByWhite();
                else
                    ChessField::arr[row][column - i].beatByBlack();

                if (ChessField::arr[row][column - i].isOccupiedByFigure())
                    dir2 = false;
            }
        }

        for (int i = 1; (i < ChessField::tableSizeHeight) && dir3; i++) {
            if (row + i < ChessField::tableSizeHeight) {
                if (isWhite)
                    ChessField::arr[row + i][column].beatByWhite();
                else
                    ChessField::arr[row + i][column].beatByBlack();

                if (ChessField::arr[row + i][column].isOccupiedByFigure())
                    dir3 = false;
            }
        }

        for (int i = 1; (i < ChessField::tableSizeHeight) && dir4; i++) {
            if (row - i >= 0) {
                if (isWhite)
                    ChessField::arr[row - i][column].beatByWhite();
                else
                    ChessField::arr[row - i][column].beatByBlack();

                if (ChessField::arr[row - i][column].isOccupiedByFigure())
                    dir4 = false;
            }
        }
    }
};

class Bishop: public ChessFigure {
public:
    Bishop(bool color, int i, int j): ChessFigure(color, i, j) {}
    void updateField() {
        bool dir1 = true, dir2 = true, dir3 = true, dir4 = true;

        for (int i = 1; (i < max(ChessField::tableSizeHeight, ChessField::tableSizeWidth)) && dir1; i++) {
            if (row + i < ChessField::tableSizeHeight && column + i < ChessField::tableSizeWidth) {
                if (isWhite)
                    ChessField::arr[row + i][column + i].beatByWhite();
                else
                    ChessField::arr[row + i][column + i].beatByBlack();

                if (ChessField::arr[row + i][column + i].isOccupiedByFigure())
                    dir1 = false;
            }
        }

        for (int i = 1; (i < max(ChessField::tableSizeHeight, ChessField::tableSizeWidth)) && dir2; i++) {
            if (row - i >= 0 && column - i >= 0) {
                if (isWhite)
                    ChessField::arr[row - i][column - i].beatByWhite();
                else
                    ChessField::arr[row - i][column - i].beatByBlack();

                if (ChessField::arr[row - i][column - i].isOccupiedByFigure())
                    dir2 = false;
            }
        }

        for (int i = 1; (i < max(ChessField::tableSizeHeight, ChessField::tableSizeWidth)) && dir3; i++) {
            if (row + i < ChessField::tableSizeHeight && column - i >= 0) {
                if (isWhite)
                    ChessField::arr[row + i][column - i].beatByWhite();
                else
                    ChessField::arr[row + i][column - i].beatByBlack();

                if (ChessField::arr[row + i][column - i].isOccupiedByFigure())
                    dir3 = false;
            }
        }

        for (int i = 1; (i < max(ChessField::tableSizeHeight, ChessField::tableSizeWidth)) && dir4; i++) {
            if (row - i >= 0 && column + i < ChessField::tableSizeWidth)
            {
                if (isWhite)
                    ChessField::arr[row - i][column + i].beatByWhite();
                else
                    ChessField::arr[row - i][column + i].beatByBlack();

                if (ChessField::arr[row - i][column + i].isOccupiedByFigure())
                    dir4 = false;
            }
        }
    }
};

class Knight: public ChessFigure {
public:
    Knight(bool color, int i, int j): ChessFigure(color, i, j) {}
    void updateField() {
        if (ChessField::areCorrectCoordinates(row + 1, column + 2))
            if (isWhite)
                ChessField::arr[row + 1][column + 2].beatByWhite();
            else
                ChessField::arr[row + 1][column + 2].beatByBlack();

        if (ChessField::areCorrectCoordinates(row + 1, column - 2))
            if (isWhite)
                ChessField::arr[row + 1][column - 2].beatByWhite();
            else
                ChessField::arr[row + 1][column - 2].beatByBlack();

        if (ChessField::areCorrectCoordinates(row - 1, column + 2))
            if (isWhite)
                ChessField::arr[row - 1][column + 2].beatByWhite();
            else
                ChessField::arr[row - 1][column + 2].beatByBlack();

        if (ChessField::areCorrectCoordinates(row - 1, column - 2))
            if (isWhite)
                ChessField::arr[row - 1][column - 2].beatByWhite();
            else
                ChessField::arr[row - 1][column - 2].beatByBlack();


        if (ChessField::areCorrectCoordinates(row + 2, column + 1))
            if (isWhite)
                ChessField::arr[row + 2][column + 1].beatByWhite();
            else
                ChessField::arr[row + 2][column + 1].beatByBlack();

        if (ChessField::areCorrectCoordinates(row + 2, column - 1))
            if (isWhite)
                ChessField::arr[row + 2][column - 1].beatByWhite();
            else
                ChessField::arr[row + 2][column - 1].beatByBlack();

        if (ChessField::areCorrectCoordinates(row - 2, column + 1))
            if (isWhite)
                ChessField::arr[row - 2][column + 1].beatByWhite();
            else
                ChessField::arr[row - 2][column + 1].beatByBlack();

        if (ChessField::areCorrectCoordinates(row - 2, column - 1))
            if (isWhite)
                ChessField::arr[row - 2][column - 1].beatByWhite();
            else
                ChessField::arr[row - 2][column - 1].beatByBlack();
    }
};

class Pawn: public ChessFigure {
public:
    Pawn(bool color, int i, int j): ChessFigure(color, i, j) {}
    void updateField() {
        if (isWhite)
        {
            if (row - 1 >= 0) {
                if (column - 1 >= 0)
                    ChessField::arr[row - 1][column - 1].beatByWhite();
                if (column + 1 < ChessField::tableSizeWidth)
                    ChessField::arr[row - 1][column + 1].beatByWhite();
            }
        }
        else
        {
            if (row + 1 < ChessField::tableSizeHeight) {
                if (column - 1 >= 0)
                    ChessField::arr[row + 1][column - 1].beatByBlack();
                if (column + 1 < ChessField::tableSizeWidth)
                    ChessField::arr[row + 1][column + 1].beatByBlack();
            }
        }
    }
};

//int main() {
//    Rook *rook(true, 0, 0);
//    ChessField::addFigure(rook, 0, 0);
//    return 0;
//}

#endif // CHESSMODAL_H
