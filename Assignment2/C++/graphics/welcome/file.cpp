#include "file.h"
#include "ui_file.h"

file::file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::file)
{
    ui->setupUi(this);

    QString sPath = "/Home";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    ui->treeView->setModel(dirmodel);
}

file::~file()
{
    delete ui;
}
