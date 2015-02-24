#include "newusersignup.h"
#include "ui_newusersignup.h"
#include "login.h"
#include <unistd.h>
#include <pthread.h>
#include <QMessageBox>

bool show1;
bool xyz;

NewUserSignup::NewUserSignup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserSignup)
{
    ui->setupUi(this);
    connect(ui->passwordtext, SIGNAL(textChanged(const QString &)), this, SLOT(customSlot(const QString &)));
    connect(ui->confirmpasswordtext, SIGNAL(textChanged(const QString &)), this, SLOT(customSlot1(const QString &)));
}

void NewUserSignup::customSlot1(const QString &y)
{
    if( y != ui->passwordtext->text())
    {
        ui->label_7->setStyleSheet("QLabel {color : red; }");
        ui->label_7->setText("passwords dont match");
    }
    else
    {
        ui->label_7->setStyleSheet("QLabel {color : green; }");
        ui->label_7->setText("passwords are matching");

    }
}

void NewUserSignup::customSlot(const QString &x)
{
    if(x.size() < 6)
    {
        ui->label_6->setStyleSheet("QLabel {color : red; }");
        ui->label_6->setText("tooshort");

    }
    else if(x.size() == 6)
    {
        ui->label_6->setStyleSheet("QLabel {color : blue; }");
        ui->label_6->setText("weak");

    }
    else if(x.size() < 9)
    {
        ui->label_6->setStyleSheet("QLabel {color : yellow; }");
        ui->label_6->setText("medium");

    }
    else
    {
        ui->label_6->setStyleSheet("QLabel {color : green; }");
        ui->label_6->setText("strong");

    }
}


NewUserSignup::~NewUserSignup()
{
    xyz =false;
    delete ui;
}

void NewUserSignup::on_toolButton_2_clicked()
{
    this->hide();
}

void NewUserSignup::on_toolButton_clicked()
{
    if (ui->passwordtext->text() != ui->confirmpasswordtext->text())
    {
        ui->passwordtext->setText("");
        ui->confirmpasswordtext->setText("");
        QMessageBox::information(this,tr("Please Re-Enter"),tr("confirm password is different"));
    }
    else
    {
        QString gotusername  = ui->usernametext->text();
        std::string Gotusername = gotusername.toUtf8().constData();
        QString gotpassword = ui->passwordtext->text();
        std::string Gotpassword = gotpassword.toUtf8().constData();
        QMessageBox::information(this,tr("successful"),tr("newusersuccessfully created"));
        this->hide();
    }
}
