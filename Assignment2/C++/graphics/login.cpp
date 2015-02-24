#include "login.h"
#include "ui_login.h"
#include "connecting.h"
#include "newusersignup.h"
#include "file.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <unistd.h>
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //ui->passwordtext->setEchoMode(QLineEdit::Password);
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
    bool if_user_valid = false;
    QString user_name = ui->usernametext->text();
    std::string user_name_text = user_name.toUtf8().constData();
    std::cout << user_name_text<< std::endl;
    QString password = ui->passwordtext->text();
    std::string password_text = password.toUtf8().constData();
    std::cout <<password_text<<std::endl;
    ui->usernametext->setText("");
    ui->passwordtext->setText("");
    if (if_user_valid == true)
    {
        QMessageBox::warning(this,tr("Please Re-Enter"),tr("Username or Password is Wrong"));
    }
    else
    {
        this->hide();
        connecting connecting1;
        connecting1.setModal(true);
        connecting1.exec();
        //sleep(5);
        //connecting1.hide();
        //file file1;
        //file1.setModal(true);
        //file1.exec();
    }
        //NewUserSignup newusersignup1;
        //newusersignup1.setModal(true);
        //newusersignup1.exec();
}

void login::on_newuser_clicked()
{
    //this->hide();
    NewUserSignup newusersignup1;
    newusersignup1.setModal(true);
    newusersignup1.exec();
}

