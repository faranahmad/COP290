/********************************************************************************
** Form generated from reading UI file 'serverfilesandfolders.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERFILESANDFOLDERS_H
#define UI_SERVERFILESANDFOLDERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverfilesandfolders
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTreeView *treeView;

    void setupUi(QDialog *serverfilesandfolders)
    {
        if (serverfilesandfolders->objectName().isEmpty())
            serverfilesandfolders->setObjectName(QStringLiteral("serverfilesandfolders"));
        serverfilesandfolders->resize(972, 854);
        QFont font;
        font.setPointSize(16);
        serverfilesandfolders->setFont(font);
        widget = new QWidget(serverfilesandfolders);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 36, 901, 801));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        treeView = new QTreeView(widget);
        treeView->setObjectName(QStringLiteral("treeView"));

        verticalLayout->addWidget(treeView);


        retranslateUi(serverfilesandfolders);

        QMetaObject::connectSlotsByName(serverfilesandfolders);
    } // setupUi

    void retranslateUi(QDialog *serverfilesandfolders)
    {
        serverfilesandfolders->setWindowTitle(QApplication::translate("serverfilesandfolders", "Dialog", 0));
        label->setText(QApplication::translate("serverfilesandfolders", "ALL FILES AND FOLDERS", 0));
    } // retranslateUi

};

namespace Ui {
    class serverfilesandfolders: public Ui_serverfilesandfolders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERFILESANDFOLDERS_H
