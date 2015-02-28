#include "onlineusers.h"
#include "ui_onlineusers.h"

OnlineUsers::OnlineUsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlineUsers)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png")) ;
    this->setStyleSheet("background-color:rgb(0,255,255);");
    ui->pushButton->setStyleSheet("background-color:light green;");
    ui->listWidget->setStyleSheet("background-color:white;");
    ui->pushButton->setFocusPolicy(Qt::NoFocus);
}

OnlineUsers::~OnlineUsers()
{
    delete ui;
}

void OnlineUsers::on_pushButton_clicked()
{
    this->hide();
}
