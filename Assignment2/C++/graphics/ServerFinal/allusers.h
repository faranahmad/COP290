#ifndef ALLUSERS_H
#define ALLUSERS_H

#include <QDialog>

namespace Ui {
class allusers;
}

class allusers : public QDialog
{
    Q_OBJECT

public:
    explicit allusers(QWidget *parent = 0);
    ~allusers();

private slots:
    //void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::allusers *ui;
};

#endif // ALLUSERS_H
