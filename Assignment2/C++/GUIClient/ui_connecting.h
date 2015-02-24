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
        connecting->resize(330, 190);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(connecting->sizePolicy().hasHeightForWidth());
        connecting->setSizePolicy(sizePolicy);
        progressBar = new QProgressBar(connecting);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 70, 271, 25));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignCenter);
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
        pushButton = new QPushButton(connecting);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 120, 85, 27));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        label->raise();
        pushButton->raise();
        progressBar->raise();

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
