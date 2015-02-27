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
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png")) ;
    //connect(this, SIGNAL(valuechanged(bool &)), this, SLOT(setvalue(int)));
    //connect(ui->okbutton, SIGNAL(clicked(bool)), this, SLOT(slotButtonClicked(bool)));
    this->setFixedSize(289,155);
    //this->funccall();

}

connecting::~connecting()
{
    std::cout<<"Exiting ui\n";
    delete ui;

    //int x = 50;
    //for(int i = 0;i<100;i++)
    //{
    //    x = i;
      //  usleep(30);
    //}

    //
}
void connecting::funccall()
{
    {
        if(connection_complete == true)
        {
            this->hide();
            file file1;
            file1.setModal(true);
            file1.exec();
        }
    }
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
