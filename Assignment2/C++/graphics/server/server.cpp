#include "server.h"
#include "allusers.h"
#include "ui_server.h"
#include "serverfilesandfolders.h"
server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
}

server::~server()
{
    delete ui;
}

void server::on_pushButton_4_clicked()
{
    qApp->quit();
}


void server::on_pushButton_2_clicked()
{
    allusers allusers1;
    allusers1.setModal(true);
    allusers1.exec();
}

void server::on_pushButton_5_clicked()
{
    serverfilesandfolders serverfilesandfolders1;
    serverfilesandfolders1.setModal(true);
    serverfilesandfolders1.exec();

}
