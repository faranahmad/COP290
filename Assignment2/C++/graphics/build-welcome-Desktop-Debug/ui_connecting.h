/********************************************************************************
** Form generated from reading UI file 'connecting.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTING_H
#define UI_CONNECTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_connecting
{
public:
    QProgressBar *progressBar;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *connecting)
    {
        if (connecting->objectName().isEmpty())
            connecting->setObjectName(QStringLiteral("connecting"));
        connecting->resize(390, 207);
        progressBar = new QProgressBar(connecting);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 120, 311, 23));
        progressBar->setValue(24);
        label = new QLabel(connecting);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 60, 281, 31));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        pushButton = new QPushButton(connecting);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(130, 160, 99, 27));

        retranslateUi(connecting);

        QMetaObject::connectSlotsByName(connecting);
    } // setupUi

    void retranslateUi(QDialog *connecting)
    {
        connecting->setWindowTitle(QApplication::translate("connecting", "Dialog", 0));
        label->setText(QApplication::translate("connecting", "Connecting to Dead Drop.......", 0));
        pushButton->setText(QApplication::translate("connecting", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class connecting: public Ui_connecting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTING_H
