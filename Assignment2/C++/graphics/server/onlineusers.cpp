#include "onlineusers.h"
#include "ui_onlineusers.h"

OnlineUsers::OnlineUsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlineUsers)
{
    ui->setupUi(this);
}

OnlineUsers::~OnlineUsers()
{
    delete ui;
}

void OnlineUsers::on_pushButton_clicked()
{
    this->hide();
}
