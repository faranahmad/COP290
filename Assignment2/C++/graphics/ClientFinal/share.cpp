#include "share.h"
#include "ui_share.h"
#include "file.h"
#include <string>
#include <QMessageBox>
#include "SyncManager.h"

extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;
extern SyncManager MergedSyncManager;
bool readonly;
std::string getting_username;
bool existingusername;

share::share(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::share)
{
    ui->setupUi(this);
    this->setFixedSize(508,342);
    this->setWindowIcon(QIcon("ddlogo2.png")) ;

    ui->radioButton->setChecked(true);
}

share::~share()
{
    delete ui;
}


void share::on_pushButton_clicked()
{
    QString username1 = ui->lineEdit->text();
    getting_username = username1.toUtf8().constData();
    if(ui->radioButton->isChecked() == true)
    {
        readonly = true;
    }
    else
    {
        readonly = false;
    }
    std::string fname=datafield1;
    datafield1=getting_username;
    inst="2";
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
    datafield1=fname;

    if (reversedata3=="YES")
    {
        existingusername=true;
    }
    else
    {
        existingusername=false;
    }

    if(existingusername)
    {
        datafield2=getting_username;
        if (readonly)
        {
            datafield3="1";
        }
        else
        {
            datafield3="0";
        }

        inst="5";
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

        ui->lineEdit->setText("");
        QMessageBox::information(this,tr("successfully shared"),tr("your file is successfully shared"));
        this->hide();
    }
    else
    {
        ui->lineEdit->setText("");
        QMessageBox::information(this,tr("Please Re-Enter"),tr("Username doesnot exist"));
    }


}

void share::on_pushButton_2_clicked()
{
    this->hide();
    file share1;
    share1.setModal(true);
    share1.exec();

}
