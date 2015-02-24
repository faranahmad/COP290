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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_file
{
public:
    QTreeView *treeView;
    QFrame *line;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QListWidget *listWidget;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;

    void setupUi(QDialog *file)
    {
        if (file->objectName().isEmpty())
            file->setObjectName(QStringLiteral("file"));
        file->resize(1725, 895);
        treeView = new QTreeView(file);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(40, 40, 671, 481));
        treeView->setSelectionMode(QAbstractItemView::MultiSelection);
        line = new QFrame(file);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(783, 20, 20, 731));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        widget = new QWidget(file);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(920, 580, 471, 141));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout_4->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(widget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout_4->addWidget(pushButton_7);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        pushButton_9 = new QPushButton(widget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        verticalLayout_5->addWidget(pushButton_9);

        pushButton_10 = new QPushButton(widget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        verticalLayout_5->addWidget(pushButton_10);


        horizontalLayout_2->addLayout(verticalLayout_5);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        widget1 = new QWidget(file);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(890, 10, 521, 521));
        verticalLayout_6 = new QVBoxLayout(widget1);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_6->addWidget(label);

        listWidget = new QListWidget(widget1);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout_6->addWidget(listWidget);

        widget2 = new QWidget(file);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(60, 570, 631, 231));
        verticalLayout_7 = new QVBoxLayout(widget2);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton_3 = new QPushButton(widget2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widget2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout_3->addWidget(pushButton_4);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(widget2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(widget2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton_8 = new QPushButton(widget2);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        verticalLayout_2->addWidget(pushButton_8);

        pushButton_11 = new QPushButton(widget2);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        verticalLayout_2->addWidget(pushButton_11);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_7->addLayout(horizontalLayout);

        pushButton_12 = new QPushButton(widget2);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));

        verticalLayout_7->addWidget(pushButton_12);


        retranslateUi(file);

        QMetaObject::connectSlotsByName(file);
    } // setupUi

    void retranslateUi(QDialog *file)
    {
        file->setWindowTitle(QApplication::translate("file", "Dialog", 0));
        pushButton_6->setText(QApplication::translate("file", "Get From Drive", 0));
        pushButton_7->setText(QApplication::translate("file", "Delete From Drive", 0));
        pushButton_9->setText(QApplication::translate("file", "Open", 0));
        pushButton_10->setText(QApplication::translate("file", "Back", 0));
        pushButton_2->setText(QApplication::translate("file", "display", 0));
        label->setText(QApplication::translate("file", "files/", 0));
        pushButton_3->setText(QApplication::translate("file", "Open", 0));
        pushButton_4->setText(QApplication::translate("file", "Delete", 0));
        pushButton->setText(QApplication::translate("file", "Move To Drive", 0));
        pushButton_5->setText(QApplication::translate("file", "Share", 0));
        pushButton_8->setText(QApplication::translate("file", "Add File", 0));
        pushButton_11->setText(QApplication::translate("file", "Sync", 0));
        pushButton_12->setText(QApplication::translate("file", "Log Out", 0));
    } // retranslateUi

};

namespace Ui {
    class file: public Ui_file {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_H
