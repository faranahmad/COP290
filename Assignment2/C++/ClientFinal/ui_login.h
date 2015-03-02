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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
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
    QToolButton *login_2;
    QToolButton *quitapp;
    QToolButton *newuser;
    QFrame *frame;
    QLabel *pic;
    QLabel *label_4;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(670, 576);
        login->setLayoutDirection(Qt::LeftToRight);
        login->setAutoFillBackground(false);
        centralWidget = new QWidget(login);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 250, 71, 17));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        usernametext = new QLineEdit(centralWidget);
        usernametext->setObjectName(QStringLiteral("usernametext"));
        usernametext->setGeometry(QRect(280, 250, 251, 27));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 300, 71, 17));
        label_2->setFont(font);
        passwordtext = new QLineEdit(centralWidget);
        passwordtext->setObjectName(QStringLiteral("passwordtext"));
        passwordtext->setGeometry(QRect(280, 300, 251, 27));
        passwordtext->setEchoMode(QLineEdit::Password);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(170, 190, 311, 17));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        login_2 = new QToolButton(centralWidget);
        login_2->setObjectName(QStringLiteral("login_2"));
        login_2->setGeometry(QRect(140, 380, 111, 25));
        quitapp = new QToolButton(centralWidget);
        quitapp->setObjectName(QStringLiteral("quitapp"));
        quitapp->setGeometry(QRect(390, 380, 111, 25));
        newuser = new QToolButton(centralWidget);
        newuser->setObjectName(QStringLiteral("newuser"));
        newuser->setGeometry(QRect(360, 460, 111, 25));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(630, 10, 21, 20));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pic = new QLabel(centralWidget);
        pic->setObjectName(QStringLiteral("pic"));
        pic->setGeometry(QRect(230, 0, 165, 165));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(126, 460, 131, 20));
        QFont font2;
        font2.setPointSize(16);
        label_4->setFont(font2);
        login->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(login);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        login->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QApplication::translate("login", "login", 0));
        label->setText(QApplication::translate("login", "Username", 0));
        label_2->setText(QApplication::translate("login", "Password", 0));
        label_3->setText(QApplication::translate("login", "Enter Username and Password", 0));
        login_2->setText(QApplication::translate("login", "Login", 0));
        quitapp->setText(QApplication::translate("login", "Cancel", 0));
        newuser->setText(QApplication::translate("login", "SignUp", 0));
        pic->setText(QString());
        label_4->setText(QApplication::translate("login", "New User....?", 0));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
