#ifndef CONNECTING_H
#define CONNECTING_H

#include <QDialog>

namespace Ui {
class connecting;
}

class connecting : public QDialog
{
    Q_OBJECT

public:
    explicit connecting(QWidget *parent = 0);

    void funccall();

    ~connecting();

private slots:
    //void on_progressBar_customContextMenuRequested(const QPoint &pos);

    void on_okbutton_clicked();


    //void slotButtonClicked(bool);

  //  void operate();

private:
    Ui::connecting *ui;

//signals:
//    void emitsignal();

};

#endif // CONNECTING_H
