#include "gameoverwindow.h"
#include "ui_gameoverwindow.h"

gameOverWindow::gameOverWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameOverWindow)
{
    ui->setupUi(this);

    setStyleSheet("background-color : black");
    ui->label->setStyleSheet("background-color : black");
    ui->label->setVisible(false);

    ui->exitButton->setStyleSheet("background-color : green");
    ui->newGameButton->setStyleSheet("background-color : green");

    connect(ui->newGameButton, SIGNAL(clicked(bool)), this, SLOT(newGame()) );
    connect(ui->exitButton, SIGNAL(clicked(bool)), this, SLOT(exitGame()) );
}


gameOverWindow::~gameOverWindow()
{
    delete ui;
}

void gameOverWindow::exitGame()
{
    exitFlag = true;
    close();
}

void gameOverWindow::newGame()
{
    newGameFlag = true;
    close();
}

void gameOverWindow::setLabelVisible(bool state)
{
    ui->label->setVisible(state);
}
