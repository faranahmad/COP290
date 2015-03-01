#include "fileaccess.h"
#include "ui_fileaccess.h"
#include <string>
#include <QMessageBox>
#include <iostream>
#include "SyncManager.h"

//window for changing password

extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;
extern SyncManager MergedSyncManager;

std::string previouspassword;
std::string getting_password;
fileaccess::fileaccess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileaccess)
{
    //constructor for setting up the window
    ui->setupUi(this);
    this->setWindowTitle("changepassword");
    this->setFixedSize(568,344);
    this->setWindowIcon(QIcon("ddlogo2.png")) ;

    ui->oldpassword->setEchoMode(QLineEdit::Password);
    ui->newpassword->setEchoMode(QLineEdit::Password);
    ui->confirmpassword->setEchoMode(QLineEdit::Password);

    //connect signal with the slot.when ever text is changed in the newpassword or confirm password signal is emitted
    //which calls the respective functions in the slot
    connect(ui->newpassword, SIGNAL(textChanged(const QString &)), this, SLOT(customSlot3(const QString &)));
    connect(ui->confirmpassword, SIGNAL(textChanged(const QString &)), this, SLOT(customSlot2(const QString &)));
}

fileaccess::~fileaccess()
{
    delete ui;
}

//function called when there is a change in the text of confirm password text. 
//It checks at each stage that whether it is
//matching with the the new password text
void fileaccess::customSlot2(const QString &y)
{
    if( y != ui->newpassword->text())
    {
        ui->matching->setStyleSheet("QLabel {color : red; }");
        ui->matching->setText("passwords dont match");
    }
    else
    {
        ui->matching->setStyleSheet("QLabel {color : green; }");
        ui->matching->setText("passwords are matching");

    }
}

//function called when there is a change in newpassword text 
//does not accept password less than 6 characters
void fileaccess::customSlot3(const QString &x)
{
    if(x.size() < 6)
    {
        ui->passlength->setStyleSheet("QLabel {color : red; }");
        ui->passlength->setText("tooshort");

    }
    else if(x.size() == 6)
    {
        ui->passlength->setStyleSheet("QLabel {color : blue; }");
        ui->passlength->setText("weak");

    }
    else if(x.size() < 9)
    {
        ui->passlength->setStyleSheet("QLabel {color : yellow; }");
        ui->passlength->setText("medium");

    }
    else
    {
        ui->passlength->setStyleSheet("QLabel {color : green; }");
        ui->passlength->setText("strong");

    }
}

//apply change button. when this button is clicked password is changed
void fileaccess::on_applychange_clicked()
{
    if(ui->newpassword->text().size() < 6) //cannot accept a password less than 6 characters
    {
        QMessageBox::information(this,tr("Too Short"),tr("password is too short"));
    }
    else if (ui->newpassword->text() != ui->confirmpassword->text())
    {
        ui->newpassword->setText("");
        ui->confirmpassword->setText("");
        QMessageBox::information(this,tr("Please Re-Enter"),tr("please enter correct old password"));
    }
    else
    {
        QString gettingpassword = ui->newpassword->text();      
        getting_password = gettingpassword.toUtf8().constData();
        std::cout << getting_password << std::endl;
        
        datafield2 = getting_password;                                  //storing new password
        datafield1 = (ui->oldpassword->text()).toUtf8().constData();    //taking in old password
        inst="6";
        usleep(20);
        if (InstructionStarted)                                         
        {
            while (!InstructionCompleted)
            {
                // Keep waiting for it to be completed
            }
            InstructionCompleted=false;
            InstructionStarted=false;    
        }
        if (reversedata1=="YES")                                        //if old password entered matches with the user's password it would be changed successfully
        {
            QMessageBox::information(this,tr("Password changed"),tr("Password changed successfully"));  
            this->hide();
        }
        else                                                            //if it does not match re-enter it again
        {
            ui->oldpassword->setText("");
            ui->newpassword->setText("");
            ui->confirmpassword->setText("");
            QMessageBox::information(this,tr("Please Re-Enter"),tr("please enter correct old password"));
        }
    }
}

//cancel changing password
void fileaccess::on_cancel_clicked()
{
    this->hide();
}
