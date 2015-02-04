/********************************************************************************
** Form generated from reading UI file 'listoffiles.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTOFFILES_H
#define UI_LISTOFFILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListOfFiles
{
public:
    QScrollBar *verticalScrollBar;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;

    void setupUi(QWidget *ListOfFiles)
    {
        if (ListOfFiles->objectName().isEmpty())
            ListOfFiles->setObjectName(QStringLiteral("ListOfFiles"));
        ListOfFiles->resize(400, 300);
        verticalScrollBar = new QScrollBar(ListOfFiles);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(180, 39, 20, 191));
        verticalScrollBar->setOrientation(Qt::Vertical);
        scrollArea = new QScrollArea(ListOfFiles);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(-60, 10, 120, 191));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 118, 189));
        scrollArea->setWidget(scrollAreaWidgetContents);
        scrollArea_2 = new QScrollArea(ListOfFiles);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(210, 110, 120, 80));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 118, 78));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        retranslateUi(ListOfFiles);

        QMetaObject::connectSlotsByName(ListOfFiles);
    } // setupUi

    void retranslateUi(QWidget *ListOfFiles)
    {
        ListOfFiles->setWindowTitle(QApplication::translate("ListOfFiles", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ListOfFiles: public Ui_ListOfFiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTOFFILES_H
