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
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_connecting
{
public:
    QLabel *label;
    QPushButton *okbutton;
    QLabel *label_2;

    void setupUi(QDialog *connecting)
    {
        if (connecting->objectName().isEmpty())
            connecting->setObjectName(QStringLiteral("connecting"));
        connecting->resize(303, 151);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(connecting->sizePolicy().hasHeightForWidth());
        connecting->setSizePolicy(sizePolicy);
        label = new QLabel(connecting);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 9, 265, 23));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        okbutton = new QPushButton(connecting);
        okbutton->setObjectName(QStringLiteral("okbutton"));
        okbutton->setGeometry(QRect(100, 90, 85, 27));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(okbutton->sizePolicy().hasHeightForWidth());
        okbutton->setSizePolicy(sizePolicy2);
        label_2 = new QLabel(connecting);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 261, 31));

        retranslateUi(connecting);

        QMetaObject::connectSlotsByName(connecting);
    } // setupUi

    void retranslateUi(QDialog *connecting)
    {
        connecting->setWindowTitle(QApplication::translate("connecting", "Dialog", 0));
        label->setText(QApplication::translate("connecting", "Connecting to Dead Drop.......", 0));
        okbutton->setText(QApplication::translate("connecting", "OK", 0));
        label_2->setText(QApplication::translate("connecting", "Syncing in Progress..........", 0));
    } // retranslateUi

};

namespace Ui {
    class connecting: public Ui_connecting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTING_H
