#include "connecting.h"
#include "file.h"
#include "ui_connecting.h"
#include <cstdlib>
#include <unistd.h>
#include <iostream>


extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;



connecting::connecting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connecting)
{
    ui->setupUi(this);
    int x = 40;
    ui->progressBar->setRange(0,100);

        //for(int i = 0;;i++)
        //{
        //    x= i;
        //    usleep(100);
        //   std::cout << x <<"\n";
        ui->progressBar->setValue(x);
        //    i=i%100;
       // }

    //sleep(50);
    //this->hide();
    //file file1;
    //file1.setModal(true);
    //file1.exec();
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

void connecting::on_pushButton_clicked()
{
    this->hide();
    file file1;
    file1.setModal(true);
    file1.exec();

}
