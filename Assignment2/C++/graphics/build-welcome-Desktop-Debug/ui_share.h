/********************************************************************************
** Form generated from reading UI file 'share.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHARE_H
#define UI_SHARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_share
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *share)
    {
        if (share->objectName().isEmpty())
            share->setObjectName(QStringLiteral("share"));
        share->resize(508, 342);
        label = new QLabel(share);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 110, 81, 17));
        lineEdit = new QLineEdit(share);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(200, 110, 211, 27));
        label_2 = new QLabel(share);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 50, 421, 16));
        radioButton = new QRadioButton(share);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(60, 170, 117, 22));
        radioButton_2 = new QRadioButton(share);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(240, 170, 151, 22));
        pushButton = new QPushButton(share);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 250, 99, 27));
        pushButton_2 = new QPushButton(share);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(280, 250, 99, 27));

        retranslateUi(share);

        QMetaObject::connectSlotsByName(share);
    } // setupUi

    void retranslateUi(QDialog *share)
    {
        share->setWindowTitle(QApplication::translate("share", "Dialog", 0));
        label->setText(QApplication::translate("share", "Username", 0));
        label_2->setText(QApplication::translate("share", "Enter the name of the user you want to share file/folder with", 0));
        radioButton->setText(QApplication::translate("share", "Read Only ", 0));
        radioButton_2->setText(QApplication::translate("share", "Read and Write", 0));
        pushButton->setText(QApplication::translate("share", "Share", 0));
        pushButton_2->setText(QApplication::translate("share", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class share: public Ui_share {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHARE_H
