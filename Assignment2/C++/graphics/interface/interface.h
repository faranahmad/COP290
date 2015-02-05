#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>

namespace Ui {
class interface;
}

class interface : public QWidget
{
    Q_OBJECT

public:
    explicit interface(QWidget *parent = 0);
    ~interface();



private slots:
    void on_quitButton_clicked();

    void on_loginbutton_clicked();


    void on_signup_clicked();

private:
    Ui::interface *ui;
};

#endif // INTERFACE_H
