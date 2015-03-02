#include "allusers.h"
#include "ui_allusers.h"
#include <string>
#include <iostream>
#include <vector>
#include "UserBase.h"

//this window displays the list of all the users

//constructor
allusers::allusers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::allusers)
{
    ui->setupUi(this);
    this->setObjectName("allusers");
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png")) ;//providing icons to the window
    this->setFixedSize(527,720);        
    this->move(670,0);
    this->setStyleSheet("#allusers {background-color:lightgreen;}"); //seting background color
    ui->listWidget->setStyleSheet("background-color:white;");
    UserBase todisplaydatabase;
    todisplaydatabase.LoadFromFile("Database.txt"); //obtains the data base that contains the list of users and their password


    std::unordered_map<std::string, std::string> hashmap= todisplaydatabase.GetUsersList();   

    for (auto& x: hashmap)                                                                   //adding the name of all users to the list 
    {
        std::cout << x.first <<"\n";
        ui->listWidget->addItem((x.first).c_str());
    }

    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);                                           //pushbutton_2 is back button 
}

//destructor
allusers::~allusers()
{
    delete ui;
}

//back button to go back to main window
void allusers::on_pushButton_2_clicked()
{
    this->hide();
}
