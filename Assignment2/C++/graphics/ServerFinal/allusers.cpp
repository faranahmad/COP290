#include "allusers.h"
#include "ui_allusers.h"
#include <string>
#include <iostream>
#include <vector>
#include "UserBase.h"
//to display the list of all users 
// extern std::vector<std::string> listofitems;

allusers::allusers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::allusers)
{
    //constructor to set up this window
    ui->setupUi(this);
    this->setFixedSize(649,885);
    this->move(670,0);
    this->setStyleSheet("background-color:rgb(0,255,255);");
    ui->pushButton_2->setStyleSheet("background-color:light green;");
    ui->listWidget->setStyleSheet("background-color:white;");
    
    UserBase todisplaydatabase;
    todisplaydatabase.LoadFromFile("Database.txt");


    std::unordered_map<std::string, std::string> hashmap= todisplaydatabase.GetUsersList();  //getting the users list to display it 

    for (auto& x: hashmap)                                                                   //adding the name of all users to the list 
    {
        std::cout << x.first <<"\n";
        ui->listWidget->addItem((x.first).c_str());
    }

    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);                                           //pushbutton_2 is back button 
}

allusers::~allusers()
{
    delete ui;
}


void allusers::on_pushButton_2_clicked()
{
    //clicking on back button hides this to go back to main server window
    this->hide();
}
