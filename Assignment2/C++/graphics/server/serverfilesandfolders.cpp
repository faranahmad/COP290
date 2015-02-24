#include "serverfilesandfolders.h"
#include "ui_serverfilesandfolders.h"


serverfilesandfolders::serverfilesandfolders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverfilesandfolders)
{
    ui->setupUi(this);
    QString sPath = "/home/faran/Desktop";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    QModelIndex index1 = dirmodel->index("/home/faran/Desktop");
    ui->treeView->setModel(dirmodel);
    //dirmodel->setReadOnly(false);
    ui->treeView->setRootIndex(index1);
}

serverfilesandfolders::~serverfilesandfolders()
{
    delete ui;
}
