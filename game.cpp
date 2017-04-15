#include <QString>
#include "game.h"

// Макрос для удобной конвертации enum в строчки
#define CASE(x) case x: return #x;

// Цвета фигур: Чёрный / белый
QString playerSide2s(PlayerSide type) {
  switch(type) {
      CASE(BLACK)
      CASE(WHITE)

    default:
      throw QString("Unknown playerSide2s(%1)").arg(type);
  }
}

// Тип шахматной фигуры: пешка, ладья, конь, слон, ферзь, король
QString pieceType2s(PieceType type) {
  switch(type) {
      CASE(PAWN)
      CASE(ROOK)
      CASE(KNIGHT)
      CASE(BISHOP)
      CASE(QUEEN)
      CASE(KING)

    default:
      throw QString("Unknown pieceType2s(%1)").arg(type);
  }
}

PieceType char2pieceType(QChar c) {
  switch(c.toUpper().toLatin1()) {
    case 'P':
      return PAWN;

    case 'R':
      return ROOK;

    case 'H':
      return KNIGHT;

    case 'B':
      return BISHOP;

    case 'Q':
      return QUEEN;

    case 'K':
      return KING;

    default:
      throw QString("Не распознан символ: %1").arg(c);
  }
}

Game::Game() {
}

