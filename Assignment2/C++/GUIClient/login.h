#ifndef LOGIN_H
#define LOGIN_H
#include <iostream>
#include <QMainWindow>


namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_quitapp_clicked();

    void on_login_2_clicked();

    void on_newuser_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
