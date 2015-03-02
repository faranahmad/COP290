#include "newusersignup.h"
#include "ui_newusersignup.h"
#include "login.h"
#include <unistd.h>
#include <pthread.h>
#include <QMessageBox>

bool show1;
bool xyz;

extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;

NewUserSignup::NewUserSignup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserSignup)
{
    ui->setupUi(this);
    this->setWindowTitle("Sign Up");
    this->setObjectName("newuser");
    this->move(100,200);
    this->setWindowIcon(QIcon("ddlogo2.png"));
    this->setStyleSheet("#newuser {background-color:lightcoral;}");
    this->setFixedSize(680,364);
    ui->toolButton_2->setFocusPolicy(Qt::NoFocus);

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
        ui->label_6->setText("");
        ui->label_7->setText("");
        QMessageBox::information(this,tr("Please Re-Enter"),tr("confirm password is different"));
    }
    else if(ui->passwordtext->text().size() < 6)
    {
        ui->passwordtext->setText("");
        ui->confirmpasswordtext->setText("");
        ui->label_6->setText("");
        ui->label_7->setText("");
        QMessageBox::information(this,tr("Too Short"),tr("password is too short please re-enter"));
    }
    else
    {
        QString gotusername  = ui->usernametext->text();
        std::string Gotusername = gotusername.toUtf8().constData();
        QString gotpassword = ui->passwordtext->text();
        std::string Gotpassword = gotpassword.toUtf8().constData();
        

        datafield1=Gotusername;
        datafield2=Gotpassword;
        inst="0";

        usleep(100);
        while (InstructionStarted)
        {
            while (!InstructionCompleted)
            {
            
            }
            if (reversedata3=="YES")
            {
                QMessageBox::information(this,tr("successful"),tr("new user successfully created"));
                InstructionCompleted=false;
                InstructionStarted=false;
                // reversedata3 = "";
            }
            else
            {
                ui->usernametext->setText("");
                ui->passwordtext->setText("");
                ui->confirmpasswordtext->setText("");
                ui->label_6->setText("");
                ui->label_7->setText("");
                QMessageBox::warning(this,tr("Error"),tr("Username already exists"));
                // reversedata3 ="";
                InstructionCompleted=false;
                InstructionStarted=false;
            }    
        }
        if (reversedata3 == "YES")
        {
            datafield1="";
            datafield2="";
            reversedata3="";
            inst="";
            this->hide();
        }
        else
        {
            datafield1="";
            datafield2="";
            reversedata3="";
            inst="";
        }
    }
}
