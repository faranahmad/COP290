#include "connecting.h"
#include "file.h"
#include "ui_connecting.h"
#include <cstdlib>
#include <unistd.h>
#include <QMessageBox>
#include <iostream>

//window showing that user is connected to the server

//constructor
connecting::connecting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connecting)
{
    ui->setupUi(this);
    this->setWindowTitle("Connecting");
    this->setObjectName("connecting");
    this->move(600,400);
    this->setStyleSheet("#connecting {background-color:springgreen;}");
    this->setWindowIcon(QIcon("ddlogo2.png")) ;
    this->setFixedSize(331,194);
}

//destructor
connecting::~connecting()
{
    delete ui;
}

//ok button
void connecting::on_okbutton_clicked()
{
    this->hide();
    file file1;             //to open user account window
    file1.setModal(true);
    file1.exec();
}
