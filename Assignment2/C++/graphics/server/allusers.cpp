#include "allusers.h"
#include "ui_allusers.h"
#include <string>
#include <iostream>
#include <vector>

extern std::vector<std::string> listofitems;

allusers::allusers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::allusers)
{
    ui->setupUi(this);
    for (int i = 0;i<listofitems.size();i++)
        ui->listWidget->addItem(listofitems.at(i).c_str());
}

allusers::~allusers()
{
    delete ui;
}


void allusers::on_pushButton_clicked()
{
     int selected = ui->listWidget->row(ui->listWidget->currentItem());
     //QListWidgetItem *selecteditem = ui->listWidget->item(selected);
     listofitems.erase(listofitems.begin()+selected);
     ui->listWidget->clear();
     for (int i = 0;i<listofitems.size();i++)
         ui->listWidget->addItem(listofitems.at(i).c_str());
     //ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
}

void allusers::on_pushButton_2_clicked()
{
    this->hide();
}
