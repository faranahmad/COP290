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

    void funccall();

    ~connecting();

private slots:

    void on_okbutton_clicked();

private:
    Ui::connecting *ui;

};

#endif // CONNECTING_H
