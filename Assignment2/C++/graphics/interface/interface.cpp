#include "interface.h"
#include "ui_interface.h"
//#include <QlineEdit>
#include "listoffiles.h"
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
    QWidget listoffiles;
    listoffiles.show();
    hide();
}
