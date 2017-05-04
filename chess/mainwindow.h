#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

  // Игра
  Game game;

  // Нарисовать букву или цифру рядом с доской
  void boardLabel(char letter, int left, int top, int width);

 protected:
  // Отрисовка поля игры
  void paintEvent(QPaintEvent*);

 private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

private:
  Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
