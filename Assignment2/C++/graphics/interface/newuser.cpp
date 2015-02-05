#include "newuser.h"
#include "ui_newuser.h"

newuser::newuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newuser)
{
    ui->setupUi(this);
}

newuser::~newuser()
{
    delete ui;
}
