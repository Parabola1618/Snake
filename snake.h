#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include "gameoverwindow.h"

namespace Ui {
class snake;
}

class snake : public QWidget
{
    Q_OBJECT

public:
    explicit snake(QWidget *parent = 0);
    ~snake();

private:
    Ui::snake *ui;

    gameOverWindow gameOverWin;

    QImage* dot;
    QImage* food;

    int timerId;
    int dots;

    static const int B_WIDTH = 600;
    static const int B_HEIGHT = 600;
    static const int DOT_SIZE = 25;
    static const int ALL_DOTS = 14400;
    static const int DELAY = 500;
    static const int RAND_POS = 24;
    enum e_direction{ left, right, down, up};
    e_direction direction;

    bool inGame;
    bool isChangePaint;

    QPair<int, int> coordinatesDots[ALL_DOTS];
    QPair<int, int> coordinatesFood;

    void loadImages();
    void initGame();
    void locateFood();
    void doDrawing();
    void move();
    void checkFood();
    void checkCollision();
    void gameOver();
    void pause();
    void unpause();
    void newGame();

    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
    void keyPressEvent(QKeyEvent *e);
};

#endif // SNAKE_H
