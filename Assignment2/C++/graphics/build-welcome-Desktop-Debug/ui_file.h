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
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_file
{
public:
    QTreeView *treeView;

    void setupUi(QDialog *file)
    {
        if (file->objectName().isEmpty())
            file->setObjectName(QStringLiteral("file"));
        file->resize(550, 512);
        treeView = new QTreeView(file);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(50, 40, 331, 421));

        retranslateUi(file);

        QMetaObject::connectSlotsByName(file);
    } // setupUi

    void retranslateUi(QDialog *file)
    {
        file->setWindowTitle(QApplication::translate("file", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class file: public Ui_file {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_H
