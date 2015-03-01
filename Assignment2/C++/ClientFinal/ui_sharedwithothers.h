/********************************************************************************
** Form generated from reading UI file 'sharedwithothers.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREDWITHOTHERS_H
#define UI_SHAREDWITHOTHERS_H

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

class Ui_sharedwithothers
{
public:
    QPushButton *backbutton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *sharedfileslist;

    void setupUi(QDialog *sharedwithothers)
    {
        if (sharedwithothers->objectName().isEmpty())
            sharedwithothers->setObjectName(QStringLiteral("sharedwithothers"));
        sharedwithothers->resize(500, 695);
        backbutton = new QPushButton(sharedwithothers);
        backbutton->setObjectName(QStringLiteral("backbutton"));
        backbutton->setGeometry(QRect(18, 640, 451, 27));
        widget = new QWidget(sharedwithothers);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 451, 601));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);

        verticalLayout->addWidget(label);

        sharedfileslist = new QListWidget(widget);
        sharedfileslist->setObjectName(QStringLiteral("sharedfileslist"));

        verticalLayout->addWidget(sharedfileslist);


        retranslateUi(sharedwithothers);

        QMetaObject::connectSlotsByName(sharedwithothers);
    } // setupUi

    void retranslateUi(QDialog *sharedwithothers)
    {
        sharedwithothers->setWindowTitle(QApplication::translate("sharedwithothers", "Dialog", 0));
        backbutton->setText(QApplication::translate("sharedwithothers", "Back", 0));
        label->setText(QApplication::translate("sharedwithothers", "Files Shared with Other users", 0));
    } // retranslateUi

};

namespace Ui {
    class sharedwithothers: public Ui_sharedwithothers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREDWITHOTHERS_H
