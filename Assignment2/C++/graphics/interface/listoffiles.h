#ifndef LISTOFFILES_H
#define LISTOFFILES_H

#include <QWidget>

namespace Ui {
class ListOfFiles;
}

class ListOfFiles : public QWidget
{
    Q_OBJECT

public:
    explicit ListOfFiles(QWidget *parent = 0);
    ~ListOfFiles();

private:
    Ui::ListOfFiles *ui;
};

#endif // LISTOFFILES_H
