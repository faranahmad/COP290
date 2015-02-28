#include "server.h"
#include "allusers.h"
#include "ui_server.h"
#include "onlineusers.h"
#include "serverfilesandfolders.h"
#include <iostream>
#include <string>

extern std::string iptodisplay; 
extern std::string porttodisplay;

server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    //constructor to set up the server side main window
    ui->setupUi(this);
    this->move(0,0);
    this->setFixedSize(608,661);
    this->setStyleSheet("background-color:rgb(0,255,255);");
    ui->allusers->setStyleSheet("background-color:light green;");
    ui->shutdown->setStyleSheet("background-color:light green;");
    ui->filesandfolders->setStyleSheet("background-color:light green;");
    ui->onlineusers->setStyleSheet("background-color:light green;");
    ui->label_2->setText(iptodisplay.c_str());    //displays the ip address
    ui->label_4->setText(porttodisplay.c_str());  // displays the port with which it is connected to client
    ui->label_5->setText("Dead Drop");
}

server::~server()
{
    delete ui;
}

void server::on_shutdown_clicked()
{
    //to shut down the window
    qApp->quit();
}


void server::on_allusers_clicked()
{
    //displays the list of all users 
    allusers allusers1;            //opens a new window that displays the list of all users     
    allusers1.setModal(true);      
    allusers1.exec();
}

void server::on_filesandfolders_clicked()
{
    //displays the list of all files and folders stored on the server
    serverfilesandfolders serverfilesandfolders1; //opens a new window that displays the list all files and folders storesd on the server
    serverfilesandfolders1.setModal(true);
    serverfilesandfolders1.exec();

}

void server::on_onlineusers_clicked()
{
    //displays the list of all online users 
    OnlineUsers onlineusers1;                     //opens a new window that displays the list of all users that are online
    onlineusers1.setModal(true);                 
    onlineusers1.exec();
}
