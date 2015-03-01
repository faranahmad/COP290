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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *GetFromDrive;
    QPushButton *DeleteFromDrive;
    QVBoxLayout *verticalLayout_5;
    QPushButton *OpenFileInDrive;
    QPushButton *GoingBackInDrive;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *openfile;
    QPushButton *deletefile;
    QVBoxLayout *verticalLayout;
    QPushButton *movetodrive;
    QPushButton *share;
    QVBoxLayout *verticalLayout_2;
    QPushButton *AddFileInClientSide;
    QPushButton *sync;
    QLabel *filesonclientside;
    QLabel *label_2;
    QFrame *line;
    QFrame *line_2;
    QLabel *label_3;
    QListWidget *listWidget;
    QLabel *label;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *logout;
    QPushButton *changepassword;
    QPushButton *ViewSharedFiles;
    QListWidget *sharedwithme;
    QLabel *sharedwithmetext;

    void setupUi(QDialog *file)
    {
        if (file->objectName().isEmpty())
            file->setObjectName(QStringLiteral("file"));
        file->resize(1800, 950);
        treeView = new QTreeView(file);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(50, 90, 991, 651));
        treeView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        treeView->setDragEnabled(false);
        treeView->setDragDropMode(QAbstractItemView::InternalMove);
        treeView->setSelectionMode(QAbstractItemView::SingleSelection);
        layoutWidget = new QWidget(file);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(1120, 790, 601, 141));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        GetFromDrive = new QPushButton(layoutWidget);
        GetFromDrive->setObjectName(QStringLiteral("GetFromDrive"));

        verticalLayout_4->addWidget(GetFromDrive);

        DeleteFromDrive = new QPushButton(layoutWidget);
        DeleteFromDrive->setObjectName(QStringLiteral("DeleteFromDrive"));

        verticalLayout_4->addWidget(DeleteFromDrive);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        OpenFileInDrive = new QPushButton(layoutWidget);
        OpenFileInDrive->setObjectName(QStringLiteral("OpenFileInDrive"));

        verticalLayout_5->addWidget(OpenFileInDrive);

        GoingBackInDrive = new QPushButton(layoutWidget);
        GoingBackInDrive->setObjectName(QStringLiteral("GoingBackInDrive"));

        verticalLayout_5->addWidget(GoingBackInDrive);


        horizontalLayout_2->addLayout(verticalLayout_5);

        layoutWidget1 = new QWidget(file);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(80, 750, 921, 111));
        verticalLayout_7 = new QVBoxLayout(layoutWidget1);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        openfile = new QPushButton(layoutWidget1);
        openfile->setObjectName(QStringLiteral("openfile"));

        verticalLayout_3->addWidget(openfile);

        deletefile = new QPushButton(layoutWidget1);
        deletefile->setObjectName(QStringLiteral("deletefile"));

        verticalLayout_3->addWidget(deletefile);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        movetodrive = new QPushButton(layoutWidget1);
        movetodrive->setObjectName(QStringLiteral("movetodrive"));

        verticalLayout->addWidget(movetodrive);

        share = new QPushButton(layoutWidget1);
        share->setObjectName(QStringLiteral("share"));

        verticalLayout->addWidget(share);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        AddFileInClientSide = new QPushButton(layoutWidget1);
        AddFileInClientSide->setObjectName(QStringLiteral("AddFileInClientSide"));

        verticalLayout_2->addWidget(AddFileInClientSide);

        sync = new QPushButton(layoutWidget1);
        sync->setObjectName(QStringLiteral("sync"));

        verticalLayout_2->addWidget(sync);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_7->addLayout(horizontalLayout);

        filesonclientside = new QLabel(file);
        filesonclientside->setObjectName(QStringLiteral("filesonclientside"));
        filesonclientside->setGeometry(QRect(50, 50, 301, 31));
        QFont font;
        font.setPointSize(16);
        filesonclientside->setFont(font);
        label_2 = new QLabel(file);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1120, 50, 231, 17));
        label_2->setFont(font);
        line = new QFrame(file);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(1070, 50, 20, 891));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(file);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 30, 1861, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(file);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(800, 0, 141, 31));
        QFont font1;
        font1.setPointSize(18);
        label_3->setFont(font1);
        listWidget = new QListWidget(file);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(1120, 90, 601, 331));
        listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        label = new QLabel(file);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1120, 70, 631, 17));
        label->setWordWrap(true);
        layoutWidget2 = new QWidget(file);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(70, 910, 901, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        logout = new QPushButton(layoutWidget2);
        logout->setObjectName(QStringLiteral("logout"));

        horizontalLayout_3->addWidget(logout);

        changepassword = new QPushButton(layoutWidget2);
        changepassword->setObjectName(QStringLiteral("changepassword"));

        horizontalLayout_3->addWidget(changepassword);

        ViewSharedFiles = new QPushButton(file);
        ViewSharedFiles->setObjectName(QStringLiteral("ViewSharedFiles"));
        ViewSharedFiles->setGeometry(QRect(390, 860, 301, 27));
        sharedwithme = new QListWidget(file);
        sharedwithme->setObjectName(QStringLiteral("sharedwithme"));
        sharedwithme->setGeometry(QRect(1120, 470, 601, 271));
        sharedwithmetext = new QLabel(file);
        sharedwithmetext->setObjectName(QStringLiteral("sharedwithmetext"));
        sharedwithmetext->setGeometry(QRect(1120, 436, 171, 21));
        sharedwithmetext->setFont(font);
        treeView->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        filesonclientside->raise();
        listWidget->raise();
        label->raise();
        label_2->raise();
        line->raise();
        line_2->raise();
        label_3->raise();
        ViewSharedFiles->raise();
        sharedwithme->raise();
        sharedwithmetext->raise();

        retranslateUi(file);

        QMetaObject::connectSlotsByName(file);
    } // setupUi

    void retranslateUi(QDialog *file)
    {
        file->setWindowTitle(QApplication::translate("file", "Dialog", 0));
        GetFromDrive->setText(QApplication::translate("file", "Get From Drive", 0));
        DeleteFromDrive->setText(QApplication::translate("file", "Delete From Drive", 0));
        OpenFileInDrive->setText(QApplication::translate("file", "Open", 0));
        GoingBackInDrive->setText(QApplication::translate("file", "Back", 0));
        openfile->setText(QApplication::translate("file", "Open", 0));
        deletefile->setText(QApplication::translate("file", "Delete", 0));
        movetodrive->setText(QApplication::translate("file", "Move To Drive", 0));
        share->setText(QApplication::translate("file", "Share", 0));
        AddFileInClientSide->setText(QApplication::translate("file", "Add File", 0));
        sync->setText(QApplication::translate("file", "Sync", 0));
        filesonclientside->setText(QApplication::translate("file", "Files On PC", 0));
        label_2->setText(QApplication::translate("file", "Files On Server", 0));
        label_3->setText(QApplication::translate("file", "WELCOME", 0));
        label->setText(QApplication::translate("file", "files/", 0));
        logout->setText(QApplication::translate("file", "Log Out", 0));
        changepassword->setText(QApplication::translate("file", "Change Password", 0));
        ViewSharedFiles->setText(QApplication::translate("file", "View Shared Files", 0));
        sharedwithmetext->setText(QApplication::translate("file", "Shared With Me", 0));
    } // retranslateUi

};

namespace Ui {
    class file: public Ui_file {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_H
