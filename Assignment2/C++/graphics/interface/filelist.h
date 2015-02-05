#ifndef FILELIST_H
#define FILELIST_H

#include <QDialog>

namespace Ui {
class filelist;
}

class filelist : public QDialog
{
    Q_OBJECT

public:
    explicit filelist(QWidget *parent = 0);
    ~filelist();

private:
    Ui::filelist *ui;
};

#endif // FILELIST_H
