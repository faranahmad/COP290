#include "interface.h"
#include <QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interface w;
    w.show();
    return a.exec();
}
