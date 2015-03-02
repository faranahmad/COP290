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
    QLabel *label_3;

    void setupUi(QDialog *connecting)
    {
        if (connecting->objectName().isEmpty())
            connecting->setObjectName(QStringLiteral("connecting"));
        connecting->resize(331, 194);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(connecting->sizePolicy().hasHeightForWidth());
        connecting->setSizePolicy(sizePolicy);
        label = new QLabel(connecting);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 291, 23));
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
        okbutton->setGeometry(QRect(120, 150, 85, 27));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(okbutton->sizePolicy().hasHeightForWidth());
        okbutton->setSizePolicy(sizePolicy2);
        label_2 = new QLabel(connecting);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 50, 211, 31));
        QFont font1;
        font1.setPointSize(14);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(connecting);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(36, 100, 261, 20));
        label_3->setAlignment(Qt::AlignCenter);

        retranslateUi(connecting);

        QMetaObject::connectSlotsByName(connecting);
    } // setupUi

    void retranslateUi(QDialog *connecting)
    {
        connecting->setWindowTitle(QApplication::translate("connecting", "Dialog", 0));
        label->setText(QApplication::translate("connecting", "Connected to Dead Drop ", 0));
        okbutton->setText(QApplication::translate("connecting", "OK", 0));
        label_2->setText(QApplication::translate("connecting", "All Files Synced", 0));
        label_3->setText(QApplication::translate("connecting", "Click OK to proceed to your account", 0));
    } // retranslateUi

};

namespace Ui {
    class connecting: public Ui_connecting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTING_H
