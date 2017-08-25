#include "snake.h"
#include "ui_snake.h"
#include <QPainter>

int snake::DELAY = 600;


snake::snake(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::snake)
{
    ui->setupUi(this);
    setStyleSheet("background-color:black");
        resize(B_WIDTH, B_HEIGHT);
        setFixedSize(B_WIDTH, B_HEIGHT);

        inGame = false;
        isChangePaint = true;

        direction = right;

        dots = 0;

        loadImages();

        gameOverWin.exec();
        if(gameOverWin.exitFlag)
        {
            close();
        }
        if(gameOverWin.newGameFlag)
        {
            newGame();
        }
}

snake::~snake()
{
    delete ui;
}

void snake::loadImages()
{
    dot = new QImage(20, 20, QImage::Format_RGB32);
    dot->fill(Qt::green);

    food = new QImage(20, 20, QImage::Format_RGB32);
    food->fill(Qt::red);
}

void snake::initGame()
{
    dots = 3;
    for(int i = 0; i < dots; ++i)
    {
        coordinatesDots[i].first = 100 - i * DOT_SIZE;
        coordinatesDots[i].second = 100;
    }

    locateFood();

    timerId = startTimer(DELAY);
}

void snake::locateFood()
{

    coordinatesFood.first = (qrand() % RAND_POS) * DOT_SIZE;
    coordinatesFood.second = (qrand() % RAND_POS) * DOT_SIZE;
}

void snake::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    doDrawing();
}

void snake::doDrawing()
{
    QPainter qp(this);
    qp.drawImage(coordinatesFood.first, coordinatesFood.second, *food);
    for(int i = 0; i < dots; ++i)
        qp.drawImage(coordinatesDots[i].first, coordinatesDots[i].second, *dot);
}

void snake::checkFood()
{
    if(coordinatesDots[0].first == coordinatesFood.first && coordinatesDots[0].second == coordinatesFood.second)
    {
        ++dots;
        locateFood();
        speedUp();
    }
}

void snake::move()
{
    for(int i = dots; i > 0; i--)
    {
        coordinatesDots[i].first = coordinatesDots[i - 1].first;
        coordinatesDots[i].second = coordinatesDots[i - 1].second;
    }

    if(direction == left)
    {
        coordinatesDots[0].first -= DOT_SIZE;
    }

    if(direction == right)
    {
        coordinatesDots[0].first += DOT_SIZE;
    }

    if(direction == down)
    {
        coordinatesDots[0].second += DOT_SIZE;
    }

    if(direction == up)
    {
        coordinatesDots[0].second -= DOT_SIZE;
    }

    if(coordinatesDots[0].first < 0)
    {
        coordinatesDots[0].first = B_WIDTH - DOT_SIZE;
    }

    if(coordinatesDots[0].first > B_WIDTH)
    {
        coordinatesDots[0].first = DOT_SIZE;
    }

    if(coordinatesDots[0].second > B_HEIGHT)
    {
        coordinatesDots[0].second = DOT_SIZE;
    }

    if(coordinatesDots[0].second < 0)
    {
        coordinatesDots[0].second = B_HEIGHT - DOT_SIZE;
    }
}

void snake::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
     if(inGame)
     {
         move();
         checkFood();
         checkCollision();
         repaint();
         isChangePaint = true;
     }

}

void snake::checkCollision()
{
    /*if(coordinatesDots[0].first >= B_WIDTH || coordinatesDots[0].first <= 0)
    {
        gameOver();
    }

    if(coordinatesDots[0].second >= B_HEIGHT || coordinatesDots[0].second <= 0)
    {
        gameOver();
    }*/

    for(int i = dots; i > 0; --i)
    {
        if(coordinatesDots[0].first == coordinatesDots[i].first && coordinatesDots[0].second == coordinatesDots[i].second)
        {
            gameOver();
        }
    }
}

void snake::gameOver()
{
    inGame = false;
    killTimer(timerId);

    gameOverWin.setLabelVisible(true);
    gameOverWin.exec();
    if(gameOverWin.exitFlag)
    {
        close();
    }
    if(gameOverWin.newGameFlag)
    {
        newGame();
    }
}

void snake::keyPressEvent(QKeyEvent *e)
{

    int key = e->key();

    if(isChangePaint)
    {

    if( (key == Qt::Key_Right) && (direction != left) )
    {
        direction = right;
        isChangePaint = false;
    }

    if( (key == Qt::Key_Left) && (direction != right) )
    {
        direction = left;
        isChangePaint = false;
    }

    if( (key == Qt::Key_Up) && (direction != down) )
    {
        direction = up;
        isChangePaint = false;
    }

    if( (key == Qt::Key_Down) && (direction != up) )
    {
        direction = down;
        isChangePaint = false;
    }

    }

    if(key == Qt::Key_Enter || key == Qt::Key_Space || key == Qt::Key_Return)
    {
        if(inGame)
        {
            pause();
        }
        else
        {
            unpause();
        }
    }

    QWidget::keyPressEvent(e);
}

void snake::pause()
{
    inGame = false;
}

void snake::unpause()
{
    inGame = true;
}

void snake::newGame()
{
    initGame();
}

void snake::speedUp()
{
    if(DELAY <= 400) return;
    else DELAY -= 30;
    killTimer(timerId);
    timerId = startTimer(DELAY);
}
