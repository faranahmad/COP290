/********************************************************************************
** Form generated from reading UI file 'fileaccess.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEACCESS_H
#define UI_FILEACCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fileaccess
{
public:
    QLineEdit *oldpassword;
    QLineEdit *newpassword;
    QLineEdit *confirmpassword;
    QLabel *matching;
    QLabel *passlength;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *applychange;
    QPushButton *cancel;

    void setupUi(QDialog *fileaccess)
    {
        if (fileaccess->objectName().isEmpty())
            fileaccess->setObjectName(QStringLiteral("fileaccess"));
        fileaccess->resize(568, 344);
        oldpassword = new QLineEdit(fileaccess);
        oldpassword->setObjectName(QStringLiteral("oldpassword"));
        oldpassword->setGeometry(QRect(190, 60, 221, 27));
        newpassword = new QLineEdit(fileaccess);
        newpassword->setObjectName(QStringLiteral("newpassword"));
        newpassword->setGeometry(QRect(190, 120, 221, 27));
        confirmpassword = new QLineEdit(fileaccess);
        confirmpassword->setObjectName(QStringLiteral("confirmpassword"));
        confirmpassword->setGeometry(QRect(190, 180, 221, 27));
        matching = new QLabel(fileaccess);
        matching->setObjectName(QStringLiteral("matching"));
        matching->setGeometry(QRect(290, 210, 211, 17));
        passlength = new QLabel(fileaccess);
        passlength->setObjectName(QStringLiteral("passlength"));
        passlength->setGeometry(QRect(310, 150, 121, 17));
        widget = new QWidget(fileaccess);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 40, 171, 191));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        widget1 = new QWidget(fileaccess);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(80, 270, 371, 29));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        applychange = new QPushButton(widget1);
        applychange->setObjectName(QStringLiteral("applychange"));

        horizontalLayout->addWidget(applychange);

        cancel = new QPushButton(widget1);
        cancel->setObjectName(QStringLiteral("cancel"));

        horizontalLayout->addWidget(cancel);


        retranslateUi(fileaccess);

        QMetaObject::connectSlotsByName(fileaccess);
    } // setupUi

    void retranslateUi(QDialog *fileaccess)
    {
        fileaccess->setWindowTitle(QApplication::translate("fileaccess", "Dialog", 0));
        matching->setText(QString());
        passlength->setText(QString());
        label->setText(QApplication::translate("fileaccess", "Old Password", 0));
        label_2->setText(QApplication::translate("fileaccess", "New Password", 0));
        label_3->setText(QApplication::translate("fileaccess", "Confirm Password", 0));
        applychange->setText(QApplication::translate("fileaccess", "Apply Change", 0));
        cancel->setText(QApplication::translate("fileaccess", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class fileaccess: public Ui_fileaccess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEACCESS_H
