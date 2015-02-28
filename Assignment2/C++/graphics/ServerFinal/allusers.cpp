#include "allusers.h"
#include "ui_allusers.h"
#include <string>
#include <iostream>
#include <vector>
#include "UserBase.h"

// extern std::vector<std::string> listofitems;

allusers::allusers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::allusers)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(0,255,255);");
    ui->pushButton_2->setStyleSheet("background-color:light green;");
    ui->listWidget->setStyleSheet("background-color:white;");
    
    UserBase todisplaydatabase;
    todisplaydatabase.LoadFromFile("Database.txt");


    std::unordered_map<std::string, std::string> hashmap= todisplaydatabase.GetUsersList();

    for (auto& x: hashmap) 
    {
        std::cout << x.first <<"\n";
        ui->listWidget->addItem((x.first).c_str());
    }

    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);
}

allusers::~allusers()
{
    delete ui;
}


//void allusers::on_pushButton_clicked()
//{
//     int selected = ui->listWidget->row(ui->listWidget->currentItem());
//     //QListWidgetItem *selecteditem = ui->listWidget->item(selected);
//     listofitems.erase(listofitems.begin()+selected);
//     ui->listWidget->clear();
//     for (unsigned int i = 0;i<listofitems.size();i++)
//         ui->listWidget->addItem(listofitems.at(i).c_str());
//     //ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
//}

void allusers::on_pushButton_2_clicked()
{
    this->hide();
}
