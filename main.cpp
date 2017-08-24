#include "snake.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    snake w;
    w.show();

    return a.exec();
}
