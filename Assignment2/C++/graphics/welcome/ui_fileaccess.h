/********************************************************************************
** Form generated from reading UI file 'fileaccess.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEACCESS_H
#define UI_FILEACCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_fileaccess
{
public:
    QTableWidget *tableWidget_2;

    void setupUi(QDialog *fileaccess)
    {
        if (fileaccess->objectName().isEmpty())
            fileaccess->setObjectName(QStringLiteral("fileaccess"));
        fileaccess->resize(676, 451);
        tableWidget_2 = new QTableWidget(fileaccess);
        if (tableWidget_2->columnCount() < 1)
            tableWidget_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(90, 170, 256, 192));

        retranslateUi(fileaccess);

        QMetaObject::connectSlotsByName(fileaccess);
    } // setupUi

    void retranslateUi(QDialog *fileaccess)
    {
        fileaccess->setWindowTitle(QApplication::translate("fileaccess", "Dialog", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("fileaccess", "New Column", 0));
    } // retranslateUi

};

namespace Ui {
    class fileaccess: public Ui_fileaccess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEACCESS_H
