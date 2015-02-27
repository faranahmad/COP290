#ifndef FILEACCESS_H
#define FILEACCESS_H

#include <QDialog>

namespace Ui {
class fileaccess;
}

class fileaccess : public QDialog
{
    Q_OBJECT

public:
    explicit fileaccess(QWidget *parent = 0);
    ~fileaccess();

private:
    Ui::fileaccess *ui;

private slots:

    void customSlot2(const QString&);

    void customSlot3(const QString&);
    void on_applychange_clicked();
    void on_cancel_clicked();
};

#endif // FILEACCESS_H
