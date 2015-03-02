#include "serverfilesandfolders.h"
#include "ui_serverfilesandfolders.h"


serverfilesandfolders::serverfilesandfolders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverfilesandfolders)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png")) ;
    this->setFixedSize(828,695);
    this->setObjectName("allfiles");
    this->setStyleSheet("#allfiles {background-color:lightgreen;}");
    this->move(670,0);
    ui->treeView->setStyleSheet("background-color:white;");
    QString sPath = "/home/faran/Desktop/DeadDropServer/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    QModelIndex index1 = dirmodel->index("/home/faran/Desktop/DeadDropServer/");
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
