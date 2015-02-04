/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_interface
{
public:
    QLineEdit *usernametext;
    QLabel *label;
    QToolButton *quitButton;
    QPushButton *loginbutton;
    QLabel *label_2;
    QLineEdit *passwordtext;
    QLabel *label_3;

    void setupUi(QWidget *interface)
    {
        if (interface->objectName().isEmpty())
            interface->setObjectName(QStringLiteral("interface"));
        interface->resize(400, 300);
        usernametext = new QLineEdit(interface);
        usernametext->setObjectName(QStringLiteral("usernametext"));
        usernametext->setGeometry(QRect(170, 70, 113, 27));
        usernametext->setEchoMode(QLineEdit::Normal);
        label = new QLabel(interface);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 70, 71, 17));
        quitButton = new QToolButton(interface);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(210, 170, 111, 25));
        quitButton->setMinimumSize(QSize(24, 25));
        quitButton->setMaximumSize(QSize(111, 25));
        quitButton->setSizeIncrement(QSize(0, 0));
        quitButton->setIconSize(QSize(25, 16));
        loginbutton = new QPushButton(interface);
        loginbutton->setObjectName(QStringLiteral("loginbutton"));
        loginbutton->setGeometry(QRect(40, 170, 99, 27));
        label_2 = new QLabel(interface);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 110, 67, 17));
        passwordtext = new QLineEdit(interface);
        passwordtext->setObjectName(QStringLiteral("passwordtext"));
        passwordtext->setGeometry(QRect(170, 110, 113, 27));
        passwordtext->setEchoMode(QLineEdit::Password);
        label_3 = new QLabel(interface);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 30, 321, 17));

        retranslateUi(interface);

        QMetaObject::connectSlotsByName(interface);
    } // setupUi

    void retranslateUi(QWidget *interface)
    {
        interface->setWindowTitle(QApplication::translate("interface", "interface", 0));
        usernametext->setText(QApplication::translate("interface", "dfsfjhdsfjhgs", 0));
        label->setText(QApplication::translate("interface", "Username", 0));
        quitButton->setText(QApplication::translate("interface", "CANCEL", 0));
        loginbutton->setText(QApplication::translate("interface", "LOGIN", 0));
        label_2->setText(QApplication::translate("interface", "Password", 0));
        passwordtext->setText(QApplication::translate("interface", "ewurhuiwher", 0));
        label_3->setText(QApplication::translate("interface", "Please enter user name and password to login", 0));
    } // retranslateUi

};

namespace Ui {
    class interface: public Ui_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
