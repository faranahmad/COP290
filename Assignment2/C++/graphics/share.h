#ifndef SHARE_H
#define SHARE_H

#include <QDialog>

namespace Ui {
class share;
}

class share : public QDialog
{
    Q_OBJECT

public:
    explicit share(QWidget *parent = 0);
    ~share();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::share *ui;
};

#endif // SHARE_H
