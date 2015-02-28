#ifndef SHAREDWITHOTHERS_H
#define SHAREDWITHOTHERS_H

#include <QDialog>

namespace Ui {
class sharedwithothers;
}

class sharedwithothers : public QDialog
{
    Q_OBJECT

public:
    explicit sharedwithothers(QWidget *parent = 0);
    ~sharedwithothers();

private slots:
    void on_backbutton_clicked();

private:
    Ui::sharedwithothers *ui;
};

#endif // SHAREDWITHOTHERS_H
