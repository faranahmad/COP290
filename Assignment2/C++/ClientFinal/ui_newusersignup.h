/********************************************************************************
** Form generated from reading UI file 'newusersignup.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWUSERSIGNUP_H
#define UI_NEWUSERSIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewUserSignup
{
public:
    QToolButton *toolButton;
    QLabel *label_5;
    QToolButton *toolButton_2;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *usernametext;
    QLineEdit *passwordtext;
    QLineEdit *confirmpasswordtext;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;

    void setupUi(QDialog *NewUserSignup)
    {
        if (NewUserSignup->objectName().isEmpty())
            NewUserSignup->setObjectName(QStringLiteral("NewUserSignup"));
        NewUserSignup->resize(680, 364);
        toolButton = new QToolButton(NewUserSignup);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(100, 280, 441, 25));
        label_5 = new QLabel(NewUserSignup);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(280, 10, 111, 31));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);
        toolButton_2 = new QToolButton(NewUserSignup);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setGeometry(QRect(270, 320, 101, 25));
        label_6 = new QLabel(NewUserSignup);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(450, 150, 121, 17));
        label_7 = new QLabel(NewUserSignup);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(440, 210, 221, 17));
        layoutWidget = new QWidget(NewUserSignup);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(230, 50, 201, 211));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        usernametext = new QLineEdit(layoutWidget);
        usernametext->setObjectName(QStringLiteral("usernametext"));

        verticalLayout->addWidget(usernametext);

        passwordtext = new QLineEdit(layoutWidget);
        passwordtext->setObjectName(QStringLiteral("passwordtext"));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        passwordtext->setFont(font1);
        passwordtext->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordtext);

        confirmpasswordtext = new QLineEdit(layoutWidget);
        confirmpasswordtext->setObjectName(QStringLiteral("confirmpasswordtext"));
        confirmpasswordtext->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(confirmpasswordtext);

        label_3 = new QLabel(NewUserSignup);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(70, 140, 65, 17));
        label_4 = new QLabel(NewUserSignup);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 210, 124, 17));
        label = new QLabel(NewUserSignup);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 80, 69, 17));

        retranslateUi(NewUserSignup);

        QMetaObject::connectSlotsByName(NewUserSignup);
    } // setupUi

    void retranslateUi(QDialog *NewUserSignup)
    {
        NewUserSignup->setWindowTitle(QApplication::translate("NewUserSignup", "Dialog", 0));
        toolButton->setText(QApplication::translate("NewUserSignup", "SignUp", 0));
        label_5->setText(QApplication::translate("NewUserSignup", "Sign Up", 0));
        toolButton_2->setText(QApplication::translate("NewUserSignup", "Cancel", 0));
        label_6->setText(QString());
        label_7->setText(QString());
        passwordtext->setText(QString());
        confirmpasswordtext->setText(QString());
        label_3->setText(QApplication::translate("NewUserSignup", "Password", 0));
        label_4->setText(QApplication::translate("NewUserSignup", "Confirm Password", 0));
        label->setText(QApplication::translate("NewUserSignup", "Username", 0));
    } // retranslateUi

};

namespace Ui {
    class NewUserSignup: public Ui_NewUserSignup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWUSERSIGNUP_H
