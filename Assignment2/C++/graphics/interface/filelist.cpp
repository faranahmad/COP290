#include "filelist.h"
#include "ui_filelist.h"

filelist::filelist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filelist)
{
    ui->setupUi(this);
}

filelist::~filelist()
{
    delete ui;
}
