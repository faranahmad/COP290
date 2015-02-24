#include "server.h"
#include <QApplication>
#include <vector>
#include <string>
 std::vector<std::string> listofitems;

 int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    server w;
    w.show();
    for (int i = 0;i<100;i++)
         listofitems.push_back(std::to_string(i));

    return a.exec();
}
