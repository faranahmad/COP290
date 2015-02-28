#include "serverfilesandfolders.h"
#include "ui_serverfilesandfolders.h"
//to display the list of all files and folders stors on the server

serverfilesandfolders::serverfilesandfolders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverfilesandfolders)
{
    ui->setupUi(this);
    this->setFixedSize(972,894);
    this->move(670,0);
    this->setStyleSheet("background-color:rgb(0,255,255);");
    ui->back->setStyleSheet("background-color:light green;");
    ui->treeView->setStyleSheet("background-color:white;");
    QString sPath = "/home/soccer/Desktop/DeadDropServer";
    dirmodel = new QFileSystemModel(this);                                                  
    dirmodel->setRootPath(sPath);
    QModelIndex index1 = dirmodel->index("/home/soccer/Desktop/DeadDropServer");          //displaying a folder in a tree style by giving a path
    ui->treeView->setModel(dirmodel);                                                     //setting to file and folder model      
    //dirmodel->setReadOnly(false);
    ui->treeView->setRootIndex(index1);
    ui->back->setFocusPolicy(Qt::NoFocus);                                                //removing focus from back button else it would be highlighted              
}

serverfilesandfolders::~serverfilesandfolders()
{
    delete ui;
}


void serverfilesandfolders::on_back_clicked()
{
    //button to go back to main server window
    this->hide();
}
