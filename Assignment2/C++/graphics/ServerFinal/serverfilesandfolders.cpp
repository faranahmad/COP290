#include "serverfilesandfolders.h"
#include "ui_serverfilesandfolders.h"


serverfilesandfolders::serverfilesandfolders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverfilesandfolders)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(0,255,255);");
    ui->back->setStyleSheet("background-color:light green;");
    ui->treeView->setStyleSheet("background-color:white;");
    QString sPath = "/home/soccer/Desktop/DeadDropServer";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    QModelIndex index1 = dirmodel->index("/home/soccer/Desktop/DeadDropServer");
    ui->treeView->setModel(dirmodel);
    //dirmodel->setReadOnly(false);
    ui->treeView->setRootIndex(index1);
    ui->back->setFocusPolicy(Qt::NoFocus);
}

serverfilesandfolders::~serverfilesandfolders()
{
    delete ui;
}

void serverfilesandfolders::on_back_clicked()
{
    this->hide();
}
