#include "server.h"
#include "allusers.h"
#include "ui_server.h"
#include "onlineusers.h"
#include "serverfilesandfolders.h"
#include <unistd.h>

//this displays the sever side main window

extern std::string iptodisplay; 
extern std::string porttodisplay;
extern std::vector<std::string> usersLog;
extern char input;


//constructor for server side main window
server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    this->move(0,0);
    this->setFixedSize(608,661);
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png"));//providing icon to the window
    this->setStyleSheet("background-color:rgb(0,255,255);");              //for background color
    ui->allusers->setStyleSheet("background-color:light green;");
    ui->shutdown->setStyleSheet("background-color:light green;");
    ui->filesandfolders->setStyleSheet("background-color:light green;");
    ui->onlineusers->setStyleSheet("background-color:light green;");
    ui->label_2->setText(iptodisplay.c_str());      //to display the ip address on the main window
    ui->label_4->setText(porttodisplay.c_str());    //to display the port n the main window

}

//destructor 
server::~server()
{
    input='q';
    usleep(1000);
    delete ui;
}

//shutdown button to close the sever
void server::on_shutdown_clicked()
{
    input='q';
    usleep(1000);
    qApp->quit();
}


//all user button to display the list of all users
void server::on_allusers_clicked()
{
    allusers allusers1;         //opens a new window which displays the list of all users
    allusers1.setModal(true);
    allusers1.exec();
}

//to show all files and foldersstored in the server
void server::on_filesandfolders_clicked()
{
    serverfilesandfolders serverfilesandfolders1; //opens a new window that shows the list of all files and folders
    serverfilesandfolders1.setModal(true);
    serverfilesandfolders1.exec();

}

//list of online users button
void server::on_onlineusers_clicked()
{
    OnlineUsers onlineusers1;           //opens a new window that displays the list of all users connected to the sever
    onlineusers1.setModal(true);
    onlineusers1.exec();
}
