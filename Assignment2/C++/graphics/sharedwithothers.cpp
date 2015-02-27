#include "sharedwithothers.h"
#include "ui_sharedwithothers.h"
#include <vector>
#include <string>

std::vector<std::string> sharedfiles;

sharedwithothers::sharedwithothers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sharedwithothers)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("/home/faran/Desktop/COP290/Assignment2/DesignDocument/ddlogo2.png")) ;
    this->setFixedSize(500,695);
    this->setWindowTitle("Shared Files");
    for(int i = 0;i<10;i++)
        sharedfiles.push_back("faran");
    for (unsigned int i = 0;i<sharedfiles.size();i++)
    {
        ui->sharedfileslist->addItem(sharedfiles.at(i).c_str());
    }

}

sharedwithothers::~sharedwithothers()
{
    delete ui;
}

void sharedwithothers::on_backbutton_clicked()
{
    this->hide();
}
