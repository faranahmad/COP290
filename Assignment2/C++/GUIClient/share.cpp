#include "share.h"
#include "ui_share.h"
#include "file.h"

extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;
extern SyncManager MergedSyncManager;

share::share(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::share)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(true);
}

share::~share()
{
    delete ui;
}


void share::on_pushButton_clicked()
{
    QString username1 = ui->lineEdit->text();
    ui->lineEdit->setText("");

}

void share::on_pushButton_2_clicked()
{
    this->hide();
    file share1;
    share1.setModal(true);
    share1.exec();
}
