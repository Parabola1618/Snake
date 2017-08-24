#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QDialog>

namespace Ui {
class gameOverWindow;
}

class gameOverWindow : public QDialog
{
    Q_OBJECT

public:
    explicit gameOverWindow(QWidget *parent = 0);
    ~gameOverWindow();

    bool newGameFlag, exitFlag;

private:
    Ui::gameOverWindow *ui;

private slots:
    void exitGame();
    void newGame();
};

#endif // GAMEOVERWINDOW_H
