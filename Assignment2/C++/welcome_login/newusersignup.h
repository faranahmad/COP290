#ifndef NEWUSERSIGNUP_H
#define NEWUSERSIGNUP_H
//#include "login.h"
#include <QDialog>

namespace Ui {
class NewUserSignup;
}

class NewUserSignup : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserSignup(QWidget *parent = 0);
    ~NewUserSignup();

private slots:
    void on_toolButton_2_clicked();

private:
    Ui::NewUserSignup *ui;
};

#endif // NEWUSERSIGNUP_H
