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
};

#endif // FILEACCESS_H
