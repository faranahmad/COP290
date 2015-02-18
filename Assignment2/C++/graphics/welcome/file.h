#ifndef FILE_H
#define FILE_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
namespace Ui {
class file;
}

class file : public QDialog
{
    Q_OBJECT

public:
    explicit file(QWidget *parent = 0);
    ~file();

private:
    Ui::file *ui;
    QFileSystemModel *dirmodel;
};

#endif // FILE_H
