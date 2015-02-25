#ifndef NEWUSERSIGNUP_H
#define NEWUSERSIGNUP_H
//#include "login.h"
#include <QDialog>

//void *threading(void*);

namespace Ui {
class NewUserSignup;
}

class NewUserSignup : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserSignup(QWidget *parent = 0);

    ~NewUserSignup();
//    void *display(void*);


private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

    void customSlot(const QString&);

    void customSlot1(const QString&);

private:
    Ui::NewUserSignup *ui;
};

#endif // NEWUSERSIGNUP_H
