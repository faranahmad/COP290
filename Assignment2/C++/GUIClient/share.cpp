#include "share.h"
#include "ui_share.h"
#include "file.h"
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
