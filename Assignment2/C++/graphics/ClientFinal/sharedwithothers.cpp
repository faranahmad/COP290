#include "sharedwithothers.h"
#include "ui_sharedwithothers.h"
#include <vector>
#include <string>
#include "SyncManager.h"

extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;
extern SyncManager MergedSyncManager;

std::vector<std::string> sharedfiles;

sharedwithothers::sharedwithothers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sharedwithothers)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("ddlogo2.png")) ;
    this->setFixedSize(500,695);
    this->setWindowTitle("Shared Files With Others");
    
    std::vector<SharingGiver> v1=  MergedSyncManager.GetGivingFiles().GetGivingList();


    for(unsigned int i = 0;i<v1.size();i++)
    {
        sharedfiles.push_back(v1[i].FilePath);
    }
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
