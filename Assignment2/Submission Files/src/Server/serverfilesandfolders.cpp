#include "serverfilesandfolders.h"
#include "ui_serverfilesandfolders.h"

//this displays the list of all files and folders stored in the server by all the users

//constructor
serverfilesandfolders::serverfilesandfolders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverfilesandfolders)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png"));//set window icon
    this->setFixedSize(828,695);
    this->setObjectName("allfiles");
    this->setStyleSheet("#allfiles {background-color:lightgreen;}");//set background color
    this->move(670,0);
    ui->treeView->setStyleSheet("background-color:white;");
    QString sPath = "/home/faran/Desktop/DeadDropServer/"; //providing path of where the files are stored 
    dirmodel = new QFileSystemModel(this);                 //making file system model which displays the files
    dirmodel->setRootPath(sPath);                          //setting the path in file system model to display the files and folders in that path
    QModelIndex index1 = dirmodel->index("/home/faran/Desktop/DeadDropServer/");
    ui->treeView->setModel(dirmodel);                      //displays the files in tree a tree like structure
    ui->treeView->setRootIndex(index1);
    ui->back->setFocusPolicy(Qt::NoFocus);                 //removing highlighting from back button 
}

//destructor
serverfilesandfolders::~serverfilesandfolders()
{
    delete ui;
}


//back button to go back to server main window
void serverfilesandfolders::on_back_clicked()
{
    this->hide();
}
