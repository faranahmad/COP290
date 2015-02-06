#include "newusersignup.h"
#include "ui_newusersignup.h"
#include "login.h"
NewUserSignup::NewUserSignup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserSignup)
{
    ui->setupUi(this);
}

NewUserSignup::~NewUserSignup()
{
    delete ui;
}

void NewUserSignup::on_toolButton_2_clicked()
{
    this->hide();
    login login1;
    login1.show();

}
