#include "login.h"
#include "ui_login.h"
#include "connecting.h"
#include "newusersignup.h"
#include "file.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <unistd.h>

extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;


login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    inst="";
    InstructionStarted=false;
    InstructionCompleted=false;
    ui->setupUi(this);
}

login::~login()
{
	inst = "e";
	usleep(20);
	if (InstructionStarted)
	{
		while (!InstructionCompleted)
		{
			// Keep waiting for the instruction to complete
		}
		InstructionCompleted=false;
		InstructionStarted=false;
	}
	delete ui;
}

void login::on_quitapp_clicked()
{
    inst = "e";
	usleep(20);
	if (InstructionStarted)
	{
		while (!InstructionCompleted)
		{
			// Keep waiting for the instruction to complete
		}
		InstructionCompleted=false;
		InstructionStarted=false;
	}
	qApp->quit();
}



void login::on_login_2_clicked()
{
    QString user_name = ui->usernametext->text();
    datafield1 = user_name.toUtf8().constData();
    std::cout << datafield1<< std::endl;
    QString password = ui->passwordtext->text();
    datafield2 = password.toUtf8().constData();
    inst="1";
    
    std::cout << datafield2 <<std::endl;
    ui->usernametext->setText("");
    ui->passwordtext->setText("");

    usleep(100);
    while (InstructionStarted)
    {
        while (!InstructionCompleted)
        {        
        	// Keep waiting for instruction to get completed
        }
        if (reversedata1=="NO")
        {
        	QMessageBox::warning(this,tr("Please Re-Enter"),tr("Username or Password is Wrong"));
        }
        else if (reversedata1=="YES")
        {
			reversedata1="";
			InstructionCompleted=false;
			InstructionStarted=false;
			this->hide();
			connecting connecting1;
			connecting1.setModal(true);
			connecting1.exec();
		}
	}
}

void login::on_newuser_clicked()
{
	//this->hide();
	NewUserSignup newusersignup1;
	newusersignup1.setModal(true);
	newusersignup1.exec();
}

