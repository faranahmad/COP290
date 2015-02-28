#ifndef ONLINEUSERS_H
#define ONLINEUSERS_H

#include <QDialog>

namespace Ui {
class OnlineUsers;
}

class OnlineUsers : public QDialog
{
    Q_OBJECT

public:
    explicit OnlineUsers(QWidget *parent = 0);
    ~OnlineUsers();

private slots:
    void on_pushButton_clicked();

private:
    Ui::OnlineUsers *ui;
};

#endif // ONLINEUSERS_H
