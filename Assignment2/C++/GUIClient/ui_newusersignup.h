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
    QLineEdit *nametext;
    QLineEdit *usernametext;
    QLineEdit *passwordtext;
    QToolButton *toolButton;
    QLineEdit *confirmpasswordtext;
    QLabel *label_5;
    QToolButton *toolButton_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QDialog *NewUserSignup)
    {
        if (NewUserSignup->objectName().isEmpty())
            NewUserSignup->setObjectName(QStringLiteral("NewUserSignup"));
        NewUserSignup->resize(687, 359);
        nametext = new QLineEdit(NewUserSignup);
        nametext->setObjectName(QStringLiteral("nametext"));
        nametext->setGeometry(QRect(220, 50, 201, 27));
        usernametext = new QLineEdit(NewUserSignup);
        usernametext->setObjectName(QStringLiteral("usernametext"));
        usernametext->setGeometry(QRect(220, 100, 201, 27));
        passwordtext = new QLineEdit(NewUserSignup);
        passwordtext->setObjectName(QStringLiteral("passwordtext"));
        passwordtext->setGeometry(QRect(220, 150, 201, 27));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        passwordtext->setFont(font);
        passwordtext->setEchoMode(QLineEdit::Password);
        toolButton = new QToolButton(NewUserSignup);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(100, 280, 401, 25));
        confirmpasswordtext = new QLineEdit(NewUserSignup);
        confirmpasswordtext->setObjectName(QStringLiteral("confirmpasswordtext"));
        confirmpasswordtext->setGeometry(QRect(220, 200, 201, 27));
        confirmpasswordtext->setEchoMode(QLineEdit::Password);
        label_5 = new QLabel(NewUserSignup);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(240, 10, 61, 20));
        toolButton_2 = new QToolButton(NewUserSignup);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setGeometry(QRect(250, 320, 101, 25));
        layoutWidget = new QWidget(NewUserSignup);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 40, 131, 191));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        label_6 = new QLabel(NewUserSignup);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(440, 150, 67, 17));
        label_7 = new QLabel(NewUserSignup);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(430, 200, 221, 17));

        retranslateUi(NewUserSignup);

        QMetaObject::connectSlotsByName(NewUserSignup);
    } // setupUi

    void retranslateUi(QDialog *NewUserSignup)
    {
        NewUserSignup->setWindowTitle(QApplication::translate("NewUserSignup", "Dialog", 0));
        passwordtext->setText(QString());
        toolButton->setText(QApplication::translate("NewUserSignup", "SignUp", 0));
        confirmpasswordtext->setText(QString());
        label_5->setText(QApplication::translate("NewUserSignup", "SIGNUP", 0));
        toolButton_2->setText(QApplication::translate("NewUserSignup", "Cancel", 0));
        label_2->setText(QApplication::translate("NewUserSignup", "Name ", 0));
        label->setText(QApplication::translate("NewUserSignup", "Username", 0));
        label_3->setText(QApplication::translate("NewUserSignup", "Password", 0));
        label_4->setText(QApplication::translate("NewUserSignup", "Confirm Password", 0));
        label_6->setText(QString());
        label_7->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NewUserSignup: public Ui_NewUserSignup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWUSERSIGNUP_H
