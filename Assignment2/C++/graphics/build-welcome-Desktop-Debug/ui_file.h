/********************************************************************************
** Form generated from reading UI file 'file.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_H
#define UI_FILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_file
{
public:
    QTreeView *treeView;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QLabel *label;
    QTableWidget *tableWidget;

    void setupUi(QDialog *file)
    {
        if (file->objectName().isEmpty())
            file->setObjectName(QStringLiteral("file"));
        file->resize(1725, 895);
        treeView = new QTreeView(file);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(50, 40, 671, 481));
        pushButton = new QPushButton(file);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(320, 570, 99, 27));
        listWidget = new QListWidget(file);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(900, 60, 501, 481));
        pushButton_2 = new QPushButton(file);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(1150, 580, 99, 27));
        pushButton_3 = new QPushButton(file);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 570, 99, 27));
        pushButton_4 = new QPushButton(file);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(60, 630, 99, 27));
        pushButton_5 = new QPushButton(file);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(320, 630, 99, 27));
        pushButton_6 = new QPushButton(file);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(770, 580, 99, 27));
        pushButton_7 = new QPushButton(file);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(770, 630, 171, 27));
        pushButton_8 = new QPushButton(file);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(510, 570, 99, 27));
        pushButton_9 = new QPushButton(file);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(990, 580, 99, 27));
        pushButton_10 = new QPushButton(file);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(1000, 640, 99, 27));
        label = new QLabel(file);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(900, 20, 501, 31));
        tableWidget = new QTableWidget(file);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(1420, 60, 281, 461));
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setFrameShadow(QFrame::Plain);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setColumnCount(2);

        retranslateUi(file);

        QMetaObject::connectSlotsByName(file);
    } // setupUi

    void retranslateUi(QDialog *file)
    {
        file->setWindowTitle(QApplication::translate("file", "Dialog", 0));
        pushButton->setText(QApplication::translate("file", "movetodrive", 0));
        pushButton_2->setText(QApplication::translate("file", "display", 0));
        pushButton_3->setText(QApplication::translate("file", "Open", 0));
        pushButton_4->setText(QApplication::translate("file", "Delete", 0));
        pushButton_5->setText(QApplication::translate("file", "Share", 0));
        pushButton_6->setText(QApplication::translate("file", "Get", 0));
        pushButton_7->setText(QApplication::translate("file", "Delete From Drive", 0));
        pushButton_8->setText(QApplication::translate("file", "Add File", 0));
        pushButton_9->setText(QApplication::translate("file", "Open", 0));
        pushButton_10->setText(QApplication::translate("file", "Back", 0));
        label->setText(QApplication::translate("file", "files/", 0));
    } // retranslateUi

};

namespace Ui {
    class file: public Ui_file {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_H
