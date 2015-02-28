#include "login.h"
#include "ui_login.h"
#include "connecting.h"
#include "newusersignup.h"
#include "file.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <unistd.h>
#include <QProgressDialog>
#include <unistd.h>
#include "SyncManager.h"

extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;
extern SyncManager MergedSyncManager;

extern bool ifconnected;
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->move(0,400);
    QString x = "Dead Drop";
    inst="";
    InstructionStarted=false;
    InstructionCompleted=false;
    this->setWindowTitle(x);
    this->setFixedSize(670,576);
    this->setWindowIcon(QIcon("ddlogo2.png")) ;
    this->setStyleSheet("background-color:rgb(135,206,250);");
    ui->pic->setStyleSheet("background-color:rgb(135,206,250);");
    ui->usernametext->setStyleSheet("background-color:white;");
    ui->passwordtext->setStyleSheet("background-color:white;");
    connect(ui->usernametext, SIGNAL(textChanged(const QString &)), this, SLOT(customSlot4()));
    QPixmap photo("ddlogo2.png");
    photo = photo.scaled(ui->pic->size(), Qt::IgnoreAspectRatio);
    ui->pic->setPixmap(photo);
    ui->login_2->setStyleSheet("background-color:light green;");
    ui->quitapp->setStyleSheet("background-color:light green;");
    ui->newuser->setStyleSheet("background-color:light green;");
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

void login::customSlot4()
{
    if(ifconnected == true)
    {
        ui->frame->setStyleSheet("background-color:green;");
    }
    else
    {
        ui->frame->setStyleSheet("background-color:red;");
    }
}

void login::on_quitapp_clicked()
{
    inst = "e";
	usleep(100);
	if (InstructionStarted)
	{
		while (!InstructionCompleted)
		{
			// Keep waiting for the instruction to complete
		}
		InstructionCompleted=false;
		InstructionStarted=false;
	}
    // this->hide();   
    // this->~login();
    qApp->quit();
}


void login::on_login_2_clicked()
{
    // bool if_user_valid = false;
    QString user_name = ui->usernametext->text();
    std::string user_name_text = user_name.toUtf8().constData();
    std::cout << user_name_text<< std::endl;
    QString password = ui->passwordtext->text();
    std::string password_text = password.toUtf8().constData();
	std::cout <<password_text<<std::endl;
    ui->usernametext->setText("");
    ui->passwordtext->setText("");

    datafield1=user_name_text;
    datafield2=password_text;

    inst="1";

    usleep(100);

    while (InstructionStarted)
    {
    	while (!InstructionCompleted)
    	{

    	}
    	if (reversedata1=="NO")
    	{
    		QMessageBox::warning(this,tr("Please Re-Enter"),tr("Username or Password is Wrong"));
        	reversedata1="";
        	InstructionCompleted=false;
			InstructionStarted=false;
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

    // else
    // {
    //     int numFiles  = 10;
    //     QProgressDialog progress("Copying files...", "Abort Copy", 0, numFiles, this);
    //          progress.setWindowModality(Qt::WindowModal);
    //          progress.setWindowFlags( ( (progress.windowFlags() | Qt::CustomizeWindowHint)
    //                                 & ~Qt::WindowCloseButtonHint & ~Qt::WindowMaximizeButtonHint) );
    //          progress.setCancelButton(0);
    //          //progress.setAutoClose(false);

    //          for (int i = 0; i < numFiles; i++) {
    //              progress.setValue(i);
    //              sleep(1);

    //              if (progress.wasCanceled())
    //                  break;
    //              //... copy one file
    //          }
    //          progress.setValue(numFiles);
    //     this->hide();
    //     connecting connecting1;
    //     connecting1.setModal(true);
    //     connecting1.exec();
}

void login::on_newuser_clicked()
{
    //this->hide();
    NewUserSignup newusersignup1;
    newusersignup1.setModal(true);
    newusersignup1.exec();
}

