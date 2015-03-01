#include "connecting.h"
#include "file.h"
#include "ui_connecting.h"
#include <cstdlib>
#include <unistd.h>
#include <QMessageBox>
#include <iostream>

bool connection_complete = true;


connecting::connecting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connecting)
{
    ui->setupUi(this);
    this->setWindowTitle("Connecting");
    this->setObjectName("connecting");
    this->move(600,400);
    this->setStyleSheet("#connecting {background-color:springgreen;}");
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png")) ;
    this->setFixedSize(331,194);
}

connecting::~connecting()
{
    std::cout<<"Exiting ui\n";
    delete ui;
}

void connecting::on_okbutton_clicked()
{
    if(connection_complete)
    {
        this->hide();
        file file1;
        file1.setModal(true);
        file1.exec();
    }
    else
    {
        QMessageBox::information(this,tr("please wait"),tr("syncing is still in progress"));
    }

}
