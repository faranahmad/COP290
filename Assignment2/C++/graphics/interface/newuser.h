#ifndef NEWUSER_H
#define NEWUSER_H

#include <QDialog>

namespace Ui {
class newuser;
}

class newuser : public QDialog
{
    Q_OBJECT

public:
    explicit newuser(QWidget *parent = 0);
    ~newuser();

private:
    Ui::newuser *ui;
};

#endif // NEWUSER_H
