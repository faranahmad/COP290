#include "onlineusers.h"
#include "ui_onlineusers.h"


extern std::vector<std::string> usersLog;

OnlineUsers::OnlineUsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlineUsers)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png")) ;
    this->setFixedSize(531,665);
    this->move(670,0);
    this->setObjectName("online");
    this->setStyleSheet("#online {background-color:lightgreen;}");
    this->setStyleSheet("background-color:rgb(0,255,255);");
    ui->pushButton->setStyleSheet("background-color:light green;");
    ui->listWidget->setStyleSheet("background-color:white;");
    ui->pushButton->setFocusPolicy(Qt::NoFocus);
    for (unsigned int i=0; i< usersLog.size(); i++)
    {
        ui->listWidget->addItem(usersLog[i].c_str());
    }
}

OnlineUsers::~OnlineUsers()
{
    delete ui;
}

void OnlineUsers::on_pushButton_clicked()
{
    this->hide();
}
