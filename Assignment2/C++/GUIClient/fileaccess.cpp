#include "fileaccess.h"
#include "ui_fileaccess.h"

fileaccess::fileaccess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileaccess)
{
    ui->setupUi(this);
}

fileaccess::~fileaccess()
{
    delete ui;
}
