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

QT_BEGIN_NAMESPACE

class Ui_fileaccess
{
public:

    void setupUi(QDialog *fileaccess)
    {
        if (fileaccess->objectName().isEmpty())
            fileaccess->setObjectName(QStringLiteral("fileaccess"));
        fileaccess->resize(1226, 701);

        retranslateUi(fileaccess);

        QMetaObject::connectSlotsByName(fileaccess);
    } // setupUi

    void retranslateUi(QDialog *fileaccess)
    {
        fileaccess->setWindowTitle(QApplication::translate("fileaccess", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class fileaccess: public Ui_fileaccess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEACCESS_H
