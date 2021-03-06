#include "server.h"
#include "allusers.h"
#include "ui_server.h"
#include "onlineusers.h"
#include "serverfilesandfolders.h"
server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    this->setFixedSize(608,661);
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png")) ;
    this->setStyleSheet("background-color:rgb(0,255,255);");
    ui->allusers->setStyleSheet("background-color:light green;");
    ui->shutdown->setStyleSheet("background-color:light green;");
    ui->filesandfolders->setStyleSheet("background-color:light green;");
    ui->onlineusers->setStyleSheet("background-color:light green;");
}

server::~server()
{
    delete ui;
}

void server::on_shutdown_clicked()
{
    qApp->quit();
}


void server::on_allusers_clicked()
{
    allusers allusers1;
    allusers1.setModal(true);
    allusers1.exec();
}

void server::on_filesandfolders_clicked()
{
    serverfilesandfolders serverfilesandfolders1;
    serverfilesandfolders1.setModal(true);
    serverfilesandfolders1.exec();

}

void server::on_onlineusers_clicked()
{
    OnlineUsers onlineusers1;
    onlineusers1.setModal(true);
    onlineusers1.exec();
}
