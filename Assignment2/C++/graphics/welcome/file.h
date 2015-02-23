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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void makechange();

    void on_pushButton_10_clicked();

private:
    Ui::file *ui;
    QFileSystemModel *dirmodel;
};

#endif // FILE_H
