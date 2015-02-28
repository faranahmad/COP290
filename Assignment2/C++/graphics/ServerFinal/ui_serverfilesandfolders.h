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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverfilesandfolders
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTreeView *treeView;
    QPushButton *back;

    void setupUi(QDialog *serverfilesandfolders)
    {
        if (serverfilesandfolders->objectName().isEmpty())
            serverfilesandfolders->setObjectName(QStringLiteral("serverfilesandfolders"));
        serverfilesandfolders->resize(972, 894);
        QFont font;
        font.setPointSize(16);
        serverfilesandfolders->setFont(font);
        layoutWidget = new QWidget(serverfilesandfolders);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 36, 901, 801));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        treeView = new QTreeView(layoutWidget);
        treeView->setObjectName(QStringLiteral("treeView"));

        verticalLayout->addWidget(treeView);

        back = new QPushButton(serverfilesandfolders);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(38, 850, 901, 27));

        retranslateUi(serverfilesandfolders);

        QMetaObject::connectSlotsByName(serverfilesandfolders);
    } // setupUi

    void retranslateUi(QDialog *serverfilesandfolders)
    {
        serverfilesandfolders->setWindowTitle(QApplication::translate("serverfilesandfolders", "Dialog", 0));
        label->setText(QApplication::translate("serverfilesandfolders", "All Files and Folders", 0));
        back->setText(QApplication::translate("serverfilesandfolders", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class serverfilesandfolders: public Ui_serverfilesandfolders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERFILESANDFOLDERS_H
