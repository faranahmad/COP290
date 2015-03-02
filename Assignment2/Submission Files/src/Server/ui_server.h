/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_server
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *onlineusers;
    QPushButton *allusers;
    QPushButton *filesandfolders;
    QPushButton *shutdown;
    QLabel *label_5;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *server)
    {
        if (server->objectName().isEmpty())
            server->setObjectName(QStringLiteral("server"));
        server->resize(608, 661);
        centralWidget = new QWidget(server);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 90, 561, 491));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        onlineusers = new QPushButton(layoutWidget);
        onlineusers->setObjectName(QStringLiteral("onlineusers"));

        verticalLayout->addWidget(onlineusers);

        allusers = new QPushButton(layoutWidget);
        allusers->setObjectName(QStringLiteral("allusers"));

        verticalLayout->addWidget(allusers);

        filesandfolders = new QPushButton(layoutWidget);
        filesandfolders->setObjectName(QStringLiteral("filesandfolders"));

        verticalLayout->addWidget(filesandfolders);

        shutdown = new QPushButton(layoutWidget);
        shutdown->setObjectName(QStringLiteral("shutdown"));

        verticalLayout->addWidget(shutdown);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(240, 9, 131, 31));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 60, 491, 28));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        horizontalLayout_2->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        horizontalLayout_2->addWidget(label_4);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        server->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(server);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        server->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(server);

        QMetaObject::connectSlotsByName(server);
    } // setupUi

    void retranslateUi(QMainWindow *server)
    {
        server->setWindowTitle(QApplication::translate("server", "server", 0));
        onlineusers->setText(QApplication::translate("server", "List Of Online Users", 0));
        allusers->setText(QApplication::translate("server", "All Users", 0));
        filesandfolders->setText(QApplication::translate("server", "All Files and Folders", 0));
        shutdown->setText(QApplication::translate("server", "Shut Down ", 0));
        label_5->setText(QApplication::translate("server", "WELCOME", 0));
        label->setText(QApplication::translate("server", "IP : ", 0));
        label_2->setText(QApplication::translate("server", "10.10.192.1", 0));
        label_3->setText(QApplication::translate("server", "Port : ", 0));
        label_4->setText(QApplication::translate("server", "3564", 0));
    } // retranslateUi

};

namespace Ui {
    class server: public Ui_server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
