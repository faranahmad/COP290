#ifndef CONNECTING_H
#define CONNECTING_H

#include <QDialog>

namespace Ui {
class connecting;
}

class connecting : public QDialog
{
    Q_OBJECT

public:
    explicit connecting(QWidget *parent = 0);

    ~connecting();

private slots:
    //void on_progressBar_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_clicked();

private:
    Ui::connecting *ui;

signals:
    void valuechanged(int value);
};

#endif // CONNECTING_H
