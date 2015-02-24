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

std::vector<Data> itemtobeadded;
std::vector<Data> presentdata;
std::stack<Data> fulldata;
std::stack<std::string> path;
file::file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::file)
{
    ui->setupUi(this);

    QString sPath = "/home/faran/Desktop";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    QModelIndex index1 = dirmodel->index("/home/faran/Desktop");
    ui->treeView->setModel(dirmodel);
    dirmodel->setReadOnly(false);
    ui->treeView->setRootIndex(index1);
    QString x = "faran";

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
    Data rootdata = Data("rootdata", true);
    rootdata.SetData(itemtobeadded);
    fulldata.push(rootdata);
    std::vector<Data> filesroot = fulldata.top().GetListFiles();
    for (int i = 0;i<filesroot.size();i++)
    {
        if (filesroot.at(i).IfFileFolder() == false)
        {
            ui->listWidget->addItem(("File\t" + filesroot.at(i).GetName()).c_str());
        }
        else
        {
            ui->listWidget->addItem(("Folder\t" + filesroot.at(i).GetName()).c_str());
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

void file::makechange()
{
    //presentitem
    int selected = ui->listWidget->row(ui->listWidget->currentItem());
    ui->listWidget->clear();
    Data nextfolder = fulldata.top().GetListFiles().at(selected);
    fulldata.push(nextfolder);
    path.push((path.top()+nextfolder.GetName()+"/"));
    ui->label->setText(path.top().c_str());
    std::vector<Data> filesroot1 = fulldata.top().GetListFiles();
    for (int i = 0;i<filesroot1.size();i++)
    {
        if (filesroot1.at(i).IfFileFolder() == false)
        {
            ui->listWidget->addItem(("File\t" + filesroot1.at(i).GetName()).c_str());
        }
        else
        {
            ui->listWidget->addItem(("Folder\t" + filesroot1.at(i).GetName()).c_str());
        }
    }
}

file::~file()
{
    delete ui;
}



void file::on_pushButton_clicked()
{
    QModelIndex index2 = ui->treeView->currentIndex();

        if(!index2.isValid()) return;

        if(dirmodel->fileInfo(index2).isDir())
        {
            // directory
            std::cout<<"yo\n";
            QString filepath1 = dirmodel->filePath(index2);
            std::string y = filepath1.toUtf8().constData();
            std::cout << y<< std::endl;

        }
        else
        {
            // file
            QString filepath1 = dirmodel->filePath(index2);
            std::string y = filepath1.toUtf8().constData();
            std::cout << y<< std::endl;

        }

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




void file::on_pushButton_2_clicked()
{
    QListWidgetItem* x = ui->listWidget->currentItem();
    QString y = x->text();
    std::string y1 = y.toUtf8().constData();
    std::cout << y1<< std::endl;
}

void file::on_pushButton_3_clicked()
{
    QModelIndex index2 = ui->treeView->currentIndex();
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

            //std::string y = filepath1.toUtf8().constData();
            //std::cout << y<< std::endl;

        }
        QDesktopServices::openUrl(QUrl(filepath1, QUrl::TolerantMode));

}

void file::on_pushButton_4_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();
       //if(!index.isValid()) return;

       if(dirmodel->fileInfo(index).isDir())
       {
           // directory
           dirmodel->rmdir(index);
       }
       else
       {
           // file
           dirmodel->remove(index);

       }
}

void file::on_pushButton_5_clicked()
{
    this->hide();
    share share1;
    share1.setModal(true);
    share1.exec();

}

void file::on_pushButton_8_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("open file"), "/home", "All files(*.*)");
    std::string filename1 = filename.toUtf8().constData();
    std::cout << filename1 << std::endl;
}

void file::on_pushButton_9_clicked()
{
    QListWidgetItem* x = (ui->listWidget->currentItem());
    QString y = x->text();
    if (y[1] == 'o')
    {
        makechange();
    }
    //presentdata = itemtobeadded;
    //int selected = ui->listWidget->row(ui->listWidget->currentItem());
    //std::cout << selected << std::endl;
    //itemtobeadded = presentdata.at(selected).GetListFiles();
}


void file::on_pushButton_10_clicked()
{
    if(fulldata.size()-1 > 0)
    {
        path.pop();
        ui->label->setText(path.top().c_str());
        fulldata.pop();
        ui->listWidget->clear();
        std::vector<Data> files = fulldata.top().GetListFiles();
        for(int i = 0;i<files.size();i++)
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


void file::on_pushButton_6_clicked()
{
    QListWidgetItem* gettingitem = ui->listWidget->currentItem();
    QString gettingtext = gettingitem->text();
    std::string path = (ui->label->text() + gettingtext).toUtf8().constData();
    std::cout << path << std::endl;
}

void file::on_pushButton_12_clicked()
{
    qApp->quit();
}
