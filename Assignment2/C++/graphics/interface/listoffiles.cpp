#include "listoffiles.h"
#include "ui_listoffiles.h"

ListOfFiles::ListOfFiles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListOfFiles)
{
    ui->setupUi(this);
}

ListOfFiles::~ListOfFiles()
{
    delete ui;
}
