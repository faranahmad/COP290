/********************************************************************************
** Form generated from reading UI file 'allusers.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLUSERS_H
#define UI_ALLUSERS_H

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

class Ui_allusers
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *allusers)
    {
        if (allusers->objectName().isEmpty())
            allusers->setObjectName(QStringLiteral("allusers"));
        allusers->resize(649, 885);
        widget = new QWidget(allusers);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 30, 551, 821));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);

        verticalLayout->addWidget(label);

        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        verticalLayout_3->addLayout(verticalLayout_2);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_3->addWidget(pushButton_2);


        retranslateUi(allusers);

        QMetaObject::connectSlotsByName(allusers);
    } // setupUi

    void retranslateUi(QDialog *allusers)
    {
        allusers->setWindowTitle(QApplication::translate("allusers", "Dialog", 0));
        label->setText(QApplication::translate("allusers", "ALL USERS", 0));
        pushButton->setText(QApplication::translate("allusers", "Remove Users", 0));
        pushButton_2->setText(QApplication::translate("allusers", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class allusers: public Ui_allusers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLUSERS_H
