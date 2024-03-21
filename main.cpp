#include "filemovedemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fileMoveDemo w;
    w.show();
    return a.exec();
}
