#include "interface.h"
#include "ui_interface.h"
//#include "listoffiles.h"
#include "filelist.h"
#include "newuser.h"
#include <iostream>

interface::interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::interface)
{

    //std::cout <<text.string<<"\n";
    ui->setupUi(this);
}

interface::~interface()
{
    delete ui;
}


void interface::on_quitButton_clicked()
{
    qApp->quit();
}

void interface::on_loginbutton_clicked()
{
    QString x = ui->usernametext->text();
    std::string y = x.toUtf8().constData();
    std::cout << y<< std::endl;
    this->hide();
    filelist filelist1;
    filelist1.setModal(true);
    filelist1.exec();

}

void interface::on_signup_clicked()
{
    this->hide();
    newuser newuser1;
    newuser1.setModal(true);
    newuser1.exec();
}
