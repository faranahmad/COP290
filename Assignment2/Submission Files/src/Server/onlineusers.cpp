#include "onlineusers.h"
#include "ui_onlineusers.h"

//this displays the window consisiting the list of online users

extern std::vector<std::string> usersLog; //stores the list of all online users

//constructor
OnlineUsers::OnlineUsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlineUsers)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png")) ;
    this->setFixedSize(531,665);
    this->move(670,0);
    this->setObjectName("online");
    this->setStyleSheet("#online {background-color:lightgreen;}");
    ui->pushButton->setStyleSheet("background-color:light green;");
    ui->listWidget->setStyleSheet("background-color:white;"); //listwidget displays the list of all online users
    ui->pushButton->setFocusPolicy(Qt::NoFocus);              //removing highlight from back button
    for (unsigned int i=0; i< usersLog.size(); i++)           //adding username to the list to display it
    {
        ui->listWidget->addItem(usersLog[i].c_str());
    }
}

//destructor
OnlineUsers::~OnlineUsers()
{
    delete ui;
}

//back button to go back to main window
void OnlineUsers::on_pushButton_clicked()
{
    this->hide();
}
