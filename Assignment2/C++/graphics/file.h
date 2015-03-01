#ifndef FILE_H
#define FILE_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
namespace Ui {
class file;
}

class file : public QDialog
{
    Q_OBJECT

public:
    explicit file(QWidget *parent = 0);
    ~file();

private slots:
    void on_movetodrive_clicked();

    //void on_pushButton_2_clicked();

    void on_openfile_clicked();

    void on_deletefile_clicked();

    void on_share_clicked();

    void on_AddFileInClientSide_clicked();

    void on_OpenFileInDrive_clicked();

    void makechange();

    void on_GoingBackInDrive_clicked();

    void on_GetFromDrive_clicked();

    void on_logout_clicked();

    void on_changepassword_clicked();

    void on_DeleteFromDrive_clicked();

    void on_ViewSharedFiles_clicked();

    void on_sync_clicked();


private:
    Ui::file *ui;
    QFileSystemModel *dirmodel;
};

#endif // FILE_H
