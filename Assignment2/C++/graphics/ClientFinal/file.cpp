#include "file.h"
#include "ui_file.h"
#include <QDirModel>
#include <QTreeView>
#include <QInputDialog>
#include "share.h"
#include <QFileDialog>
#include <QTableWidgetItem>
#include <iostream>
#include <vector>
#include <string>
#include "filesonserver.h"
#include <stack>
#include "fileaccess.h"
#include <QMessageBox>
#include "sharedwithothers.h"
#include "SyncManager.h"

extern std::string inst,datafield1,datafield2,datafield3;
extern std::string reversedata1,reversedata2,reversedata3;
extern bool InstructionStarted, InstructionCompleted;
extern SyncManager MergedSyncManager;
extern std::vector<Data> ReverseDataFiles;

std::vector<Data> itemtobeadded;
std::vector<Data> presentdata;
std::stack<Data> fulldata;
std::stack<std::string> path;
std::string filepathtoshare;
std::string fileformovingtodrive;
std::string filetodelete;
std::string file_to_add_from_clientpc;
std::string path_to_get_from_drive;
std::string path_to_delete_from_drive;
std::vector<std::string> shared_with_me_list;

file::file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::file)
{
    ui->setupUi(this);
    //ui->filesonclientside->setFrameShadow(QFrame::Raised);
    this->setFixedSize(1800,950);
    this->setWindowIcon(QIcon("ddlogo2.png")) ;
    ui->treeView->header()->resizeSection(ui->treeView->header()->logicalIndexAt(51,91),400);
    ui->treeView->header()->setMinimumWidth(1000);
    this->setStyleSheet("background-color:rgb(0,255,255);");
    ui->changepassword->setStyleSheet("background-color:light green;");
    ui->openfile->setStyleSheet("background-color:light green;");
    ui->deletefile->setStyleSheet("background-color:light green;");
    ui->share->setStyleSheet("background-color:light green;");
    ui->AddFileInClientSide->setStyleSheet("background-color:light green;");
    ui->OpenFileInDrive->setStyleSheet("background-color:light green;");
    ui->GoingBackInDrive->setStyleSheet("background-color:light green;");
    ui->GetFromDrive->setStyleSheet("background-color:light green;");
    ui->logout->setStyleSheet("background-color:light green;");
    ui->movetodrive->setStyleSheet("background-color:light green;");
    ui->sync->setStyleSheet("background-color:light green;");
    ui->DeleteFromDrive->setStyleSheet("background-color:light green;");
    ui->GetFromDrive->setStyleSheet("background-color:light green;");
    ui->ViewSharedFiles->setStyleSheet("background-color:light green;");
    ui->listWidget->setStyleSheet("background-color:white;");
    ui->treeView->setStyleSheet("background-color:white;");
    ui->sharedwithme->setStyleSheet("background-color:white;");

    std::string mainpath(getenv("HOME")); 
    std::string foldername=mainpath + "/Desktop/DeadDrop/" + reversedata2  + "/";

    // QString sPath = "/home/faran/Desktop";
    QString sPath = foldername.c_str();
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    QModelIndex index1 = dirmodel->index(foldername.c_str());
    ui->treeView->setModel(dirmodel);
    dirmodel->setReadOnly(false);
    ui->treeView->setRootIndex(index1);

    MergedSyncManager.LoadFromDiskDB(mainpath+"/Desktop/DeadDrop");
    std::vector<Sharing> sharfiles = MergedSyncManager.GetReceivingFiles().GetSharingList();

    //adding file names to be displayed on shared with me list
    for(unsigned int i=0;i<sharfiles.size();i++)
    {
        shared_with_me_list.push_back(sharfiles[i].FilePath);
    }
    for (unsigned int i= 0;i<shared_with_me_list.size();i++)
    {
        ui->sharedwithme->addItem((shared_with_me_list.at(i)).c_str());
    }

    Data faran("faran", true);
    Data anu = Data("anu",true);
    Data kg = Data("kg", true);
    Data yomp4 =  Data("yo.mp4");
    Data yoyo = Data("yoyyo");
    Data ronak = Data("ronak",false);
    path.push("files/");
    ui->label->setText(path.top().c_str());
    anu.InsertData(yomp4);
    anu.InsertData(yoyo);
    faran.InsertData(anu);
    faran.InsertData(kg);
    Data pokemon = Data("pokemon");
    itemtobeadded.push_back(faran);
    itemtobeadded.push_back(ronak);
    itemtobeadded.push_back(pokemon);
    itemtobeadded=ReverseDataFiles;
    Data rootdata = Data("rootdata", true);
    rootdata.SetData(itemtobeadded);
    fulldata.push(rootdata);
    std::vector<Data> filesroot = fulldata.top().GetListFiles();
    
    for (unsigned int i = 0;i<filesroot.size();i++)
    {
        if (filesroot.at(i).IfFileFolder() == false)
        {
            ui->listWidget->addItem(("File\t\t\t" + filesroot.at(i).GetName()).c_str());
        }
        else
        {
            ui->listWidget->addItem(("Folder\t\t\t" + filesroot.at(i).GetName()).c_str());
        }
    }
        //ui->tableWidget->setItem(1,1,item);
    //faran.SetName("dude");
    //faran.SetFolder(true);


    //itemtobeadded.push_back(faran);
    //for(int i=0;i<itemtobeadded.size();i++)
    //{
    //    ui->listWidget->addItem(itemtobeadded.at(i).GetName().c_str());
    //}
    //ui->listWidget->addItem(x);
    //ui->listWidget->addItem(x);

}

//function used in opening a folder on server side manually triggerd when "open" on serer side is clickes
void file::makechange()
{
    int selected = ui->listWidget->row(ui->listWidget->currentItem());
    ui->listWidget->clear();
    Data nextfolder = fulldata.top().GetListFiles().at(selected);
    fulldata.push(nextfolder);
    path.push((path.top()+nextfolder.GetName()+"/"));
    ui->label->setText(path.top().c_str());
    std::vector<Data> filesroot1 = fulldata.top().GetListFiles();
    for (unsigned int i = 0;i<filesroot1.size();i++)
    {
        if (filesroot1.at(i).IfFileFolder() == false)
        {
            ui->listWidget->addItem(("File\t\t\t" + filesroot1.at(i).GetName()).c_str());
        }
        else
        {
            ui->listWidget->addItem(("Folder\t\t\t" + filesroot1.at(i).GetName()).c_str());
        }
    }
}

file::~file()
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



void file::on_movetodrive_clicked()
{
    QModelIndex index2 = ui->treeView->currentIndex();

        if(!index2.isValid()) return;

        if(dirmodel->fileInfo(index2).isDir())
        {
            // directory
            QString filepath1 = dirmodel->filePath(index2);
            fileformovingtodrive = filepath1.toUtf8().constData();
            std::cout << fileformovingtodrive<< std::endl;

        }
        else
        {
            // file
            QString filepath1 = dirmodel->filePath(index2);
            fileformovingtodrive = filepath1.toUtf8().constData();
            std::cout << fileformovingtodrive<< std::endl;

        }
        ui->treeView->clearSelection();

        // for multiple file transfer.............................

//    QModelIndexList indexes2 = ui->treeView->selectedIndexes();
//    for (int i = 0;i<indexes2.size();i++)
//    {
//        if(dirmodel->fileInfo(indexes2[i]).isDir())
//        {
//            // directory
//            std::cout<<"yo\n";
//            QString filepath1 = dirmodel->filePath(indexes2[i]);
//            std::string y = filepath1.toUtf8().constData();
//            std::cout << y<< std::endl;

//        }
//        else
//        {
//            // file
//            QString filepath1 = dirmodel->filePath(indexes2[i]);
//            std::string y = filepath1.toUtf8().constData();
//            std::cout << y<< std::endl;

//        }
//    }
}




/*void file::on_pushButton_2_clicked()
{
    QListWidgetItem* x = ui->listWidget->currentItem();
    QString y = x->text();
    std::string y1 = y.toUtf8().constData();
    std::cout << y1<< std::endl;
}
*/
void file::on_openfile_clicked()
{
    QModelIndex index2 = ui->treeView->currentIndex();
    ui->treeView->clearSelection();
    QString filepath1;
        if(!index2.isValid()) return;

        if(dirmodel->fileInfo(index2).isDir())
        {
            // directory
            filepath1 = dirmodel->filePath(index2);
        }
        else
        {
            // file
            filepath1 = dirmodel->filePath(index2);
        }
        QDesktopServices::openUrl(QUrl(filepath1, QUrl::TolerantMode));

}

void file::on_deletefile_clicked()
{
    QModelIndex index2 = ui->treeView->currentIndex();
       //if(!index.isValid()) return;

//       if(dirmodel->fileInfo(index).isDir())
//       {
//           // directory
//           dirmodel->rmdir(index);
//       }
//       else
//       {
//           // file
//           dirmodel->remove(index);

//       }
    if(dirmodel->fileInfo(index2).isDir())
    {
        // directory
        QString filepath2 = dirmodel->filePath(index2);
        filetodelete = filepath2.toUtf8().constData();
    }
    else
    {
        // file
        QString filepath2 = dirmodel->filePath(index2);
        filetodelete = filepath2.toUtf8().constData();
    }
    ui->treeView->clearSelection();
}

void file::on_share_clicked()
{
    QModelIndex index2 = ui->treeView->currentIndex();

        if(!index2.isValid())
        {
            QMessageBox::information(this,tr("please select"),tr("select a file to share"));
        }

        else if(dirmodel->fileInfo(index2).isDir())
        {
            QMessageBox::information(this,tr("Folder"),tr("Please select a file"));

        }
        else
        {
            QString filepath2 = dirmodel->filePath(index2);
            filepathtoshare = filepath2.toUtf8().constData();
            datafield1=filepathtoshare;
            share share1;
            share1.setModal(true);
            share1.exec();

        }
        ui->treeView->clearSelection();

}

void file::on_AddFileInClientSide_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("open file"), "/home", "All files(*.*)");
    file_to_add_from_clientpc = filename.toUtf8().constData();
    std::cout << file_to_add_from_clientpc << std::endl;
}

void file::on_OpenFileInDrive_clicked()
{
    QListWidgetItem* x = (ui->listWidget->currentItem());
    if (x !=NULL)
    {
        QString y = x->text();
        if (y[1] == 'o')
        {
            makechange();
        }
    }
    //presentdata = itemtobeadded;
    //int selected = ui->listWidget->row(ui->listWidget->currentItem());
    //std::cout << selected << std::endl;
    //itemtobeadded = presentdata.at(selected).GetListFiles();
}


void file::on_GoingBackInDrive_clicked()
{
    if(fulldata.size()-1 > 0)
    {
        path.pop();
        ui->label->setText(path.top().c_str());
        fulldata.pop();
        ui->listWidget->clear();
        std::vector<Data> files = fulldata.top().GetListFiles();
        for(unsigned int i = 0;i<files.size();i++)
        {
            if (files.at(i).IfFileFolder() == false)
            {
                ui->listWidget->addItem(("File\t" + files.at(i).GetName()).c_str());
            }
            else
            {
                ui->listWidget->addItem(("Folder\t" + files.at(i).GetName()).c_str());
            }
        }
    }
}


void file::on_GetFromDrive_clicked()
{
    QListWidgetItem* gettingitem = ui->listWidget->currentItem();
    if (gettingitem != NULL)
    {
        QString gettingtext = gettingitem->text();
        path_to_get_from_drive = (ui->label->text() + gettingtext).toUtf8().constData();
        std::cout << path_to_get_from_drive << std::endl;
        ui->sharedwithme->clearSelection();
    }
    else
    {
        QListWidgetItem* gettingitem1 = ui->sharedwithme->currentItem();
        if(gettingitem1 != NULL)
        {
            QString gettingtext1 = gettingitem1->text();
            path_to_get_from_drive = (gettingtext1).toUtf8().constData();
            std::cout << path_to_get_from_drive << std::endl;
            ui->sharedwithme->clearSelection();
        }
    }
}

void file::on_logout_clicked()
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

void file::on_changepassword_clicked()
{
    fileaccess fileaccess1;
    fileaccess1.setModal(true);
    fileaccess1.exec();
}

void file::on_DeleteFromDrive_clicked()
{
    QListWidgetItem* gettingitem = ui->listWidget->currentItem();
    if(gettingitem != NULL)
    {
        QString gettingtext = gettingitem->text();
        path_to_delete_from_drive = (ui->label->text() + gettingtext).toUtf8().constData();
        std::cout << path_to_delete_from_drive << std::endl;
        ui->sharedwithme->clearSelection();
    }
}

void file::on_ViewSharedFiles_clicked()
{
    sharedwithothers sharedwithothers1;
    sharedwithothers1.setModal(true);
    sharedwithothers1.exec();
}

void file::on_sync_clicked()
{
    inst="4";
    usleep(20);
    while (InstructionStarted)
    {
        while (!InstructionCompleted)
        {

        }
        InstructionStarted=false;
        InstructionCompleted=false;
    }
    std::cout<<"prateek chutiya hai"<<std::endl;
}
