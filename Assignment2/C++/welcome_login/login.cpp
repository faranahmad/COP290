#include "login.h"
#include "ui_login.h"
#include "newusersignup.h"
#include <QtCore>
#include <QtGui>


extern std::string usname, passwd;
extern bool contains,buttonclicked;




login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    contains=false;
    buttonclicked=false;

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
    QString x = ui->usernametext->text();
    std::string y = x.toUtf8().constData();
    usname=y;
    //std::cout << y<< std::endl;
    QString b = ui->passwordtext->text();
    std::string a = b.toUtf8().constData();
    passwd=a;
    contains=true;
    // this->hide();
    //NewUserSignup newusersignup1;
    //newusersignup1.setModal(true);
    //newusersignup1.exec();
}

void login::on_newuser_clicked()
{
    // this->hide();
    buttonclicked=true;
    // NewUserSignup newusersignup1;
    // newusersignup1.setModal(true);
    // newusersignup1.exec();
}
