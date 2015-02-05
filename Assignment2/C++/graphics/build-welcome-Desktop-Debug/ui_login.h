/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLineEdit *usernametext;
    QLabel *label_2;
    QLineEdit *passwordtext;
    QLabel *label_3;
    QLabel *label_4;
    QToolButton *login_2;
    QToolButton *quitapp;
    QToolButton *newuser;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(424, 309);
        centralWidget = new QWidget(login);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 70, 71, 17));
        usernametext = new QLineEdit(centralWidget);
        usernametext->setObjectName(QStringLiteral("usernametext"));
        usernametext->setGeometry(QRect(140, 70, 113, 27));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 130, 71, 17));
        passwordtext = new QLineEdit(centralWidget);
        passwordtext->setObjectName(QStringLiteral("passwordtext"));
        passwordtext->setGeometry(QRect(140, 130, 113, 27));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 30, 311, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 240, 111, 17));
        login_2 = new QToolButton(centralWidget);
        login_2->setObjectName(QStringLiteral("login_2"));
        login_2->setGeometry(QRect(50, 180, 111, 25));
        quitapp = new QToolButton(centralWidget);
        quitapp->setObjectName(QStringLiteral("quitapp"));
        quitapp->setGeometry(QRect(200, 180, 111, 25));
        newuser = new QToolButton(centralWidget);
        newuser->setObjectName(QStringLiteral("newuser"));
        newuser->setGeometry(QRect(200, 240, 111, 25));
        login->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(login);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        login->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(login);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        login->setStatusBar(statusBar);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QApplication::translate("login", "login", 0));
        label->setText(QApplication::translate("login", "Username", 0));
        label_2->setText(QApplication::translate("login", "Password", 0));
        label_3->setText(QApplication::translate("login", "Enter Username and Password", 0));
        label_4->setText(QApplication::translate("login", "New User...?", 0));
        login_2->setText(QApplication::translate("login", "Login", 0));
        quitapp->setText(QApplication::translate("login", "Cancel", 0));
        newuser->setText(QApplication::translate("login", "SignUp", 0));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
