/********************************************************************************
** Form generated from reading UI file 'onlineusers.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLINEUSERS_H
#define UI_ONLINEUSERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OnlineUsers
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *OnlineUsers)
    {
        if (OnlineUsers->objectName().isEmpty())
            OnlineUsers->setObjectName(QStringLiteral("OnlineUsers"));
        OnlineUsers->resize(531, 665);
        layoutWidget = new QWidget(OnlineUsers);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 36, 441, 571));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);

        verticalLayout->addWidget(label);

        listWidget = new QListWidget(layoutWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        retranslateUi(OnlineUsers);

        QMetaObject::connectSlotsByName(OnlineUsers);
    } // setupUi

    void retranslateUi(QDialog *OnlineUsers)
    {
        OnlineUsers->setWindowTitle(QApplication::translate("OnlineUsers", "Dialog", 0));
        label->setText(QApplication::translate("OnlineUsers", "Online Users", 0));
        pushButton->setText(QApplication::translate("OnlineUsers", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class OnlineUsers: public Ui_OnlineUsers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLINEUSERS_H
