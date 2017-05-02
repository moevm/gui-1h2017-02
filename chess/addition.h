#ifndef ADDITION
#define ADDITION

// Статус клетки:
//   ENABLE - можно ходить
//   DISABLE - нельзя ходить
//   ATTACK - можно ходить съев чужую фигуру
enum status {ENABLE = 0x00, DISABLE, ATTACK};
struct Area {
  int row;
  int col;
  status state;
};

#endif // ADDITION

