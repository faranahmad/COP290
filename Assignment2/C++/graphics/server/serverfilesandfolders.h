#ifndef SERVERFILESANDFOLDERS_H
#define SERVERFILESANDFOLDERS_H

#include <QDialog>
#include <QFileSystemModel>
#include <QtCore>
#include <QtGui>

namespace Ui {
class serverfilesandfolders;
}

class serverfilesandfolders : public QDialog
{
    Q_OBJECT

public:
    explicit serverfilesandfolders(QWidget *parent = 0);
    ~serverfilesandfolders();

private:
    Ui::serverfilesandfolders *ui;
    QFileSystemModel *dirmodel;
};

#endif // SERVERFILESANDFOLDERS_H
