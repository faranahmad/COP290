#include "login.h"
#include "ui_login.h"
#include "newusersignup.h"
#include "file.h"
#include <QtCore>
#include <QtGui>
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_quitapp_clicked()
{
    qApp->quit();
}



void login::on_login_2_clicked()
{
    this->hide();
    QString x = ui->usernametext->text();
    std::string y = x.toUtf8().constData();
    //std::cout << y<< std::endl;
    QString b = ui->passwordtext->text();
    std::string a = b.toUtf8().constData();

    file file1;
    file1.setModal(true);
    file1.exec();
    //NewUserSignup newusersignup1;
    //newusersignup1.setModal(true);
    //newusersignup1.exec();
}

void login::on_newuser_clicked()
{
    this->hide();
    NewUserSignup newusersignup1;
    newusersignup1.setModal(true);
    newusersignup1.exec();
}
