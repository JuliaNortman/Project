/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *checkerBoard;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *layout1;
    QHBoxLayout *layout2;
    QHBoxLayout *layout3;
    QHBoxLayout *layout4;
    QHBoxLayout *layout5;
    QHBoxLayout *layout6;
    QHBoxLayout *layout7;
    QHBoxLayout *layout8;
    QTextBrowser *debug;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 600);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(0, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        MainWindow->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(180, 90, 401, 401));
        checkerBoard = new QGridLayout(gridLayoutWidget);
        checkerBoard->setSpacing(0);
        checkerBoard->setContentsMargins(11, 11, 11, 11);
        checkerBoard->setObjectName(QStringLiteral("checkerBoard"));
        checkerBoard->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        layout1 = new QHBoxLayout();
        layout1->setSpacing(0);
        layout1->setObjectName(QStringLiteral("layout1"));

        verticalLayout->addLayout(layout1);

        layout2 = new QHBoxLayout();
        layout2->setSpacing(0);
        layout2->setObjectName(QStringLiteral("layout2"));

        verticalLayout->addLayout(layout2);

        layout3 = new QHBoxLayout();
        layout3->setSpacing(0);
        layout3->setObjectName(QStringLiteral("layout3"));

        verticalLayout->addLayout(layout3);

        layout4 = new QHBoxLayout();
        layout4->setSpacing(0);
        layout4->setObjectName(QStringLiteral("layout4"));

        verticalLayout->addLayout(layout4);

        layout5 = new QHBoxLayout();
        layout5->setSpacing(0);
        layout5->setObjectName(QStringLiteral("layout5"));

        verticalLayout->addLayout(layout5);

        layout6 = new QHBoxLayout();
        layout6->setSpacing(0);
        layout6->setObjectName(QStringLiteral("layout6"));

        verticalLayout->addLayout(layout6);

        layout7 = new QHBoxLayout();
        layout7->setSpacing(0);
        layout7->setObjectName(QStringLiteral("layout7"));

        verticalLayout->addLayout(layout7);

        layout8 = new QHBoxLayout();
        layout8->setSpacing(0);
        layout8->setObjectName(QStringLiteral("layout8"));

        verticalLayout->addLayout(layout8);


        checkerBoard->addLayout(verticalLayout, 0, 0, 1, 1);

        debug = new QTextBrowser(centralWidget);
        debug->setObjectName(QStringLiteral("debug"));
        debug->setGeometry(QRect(10, 200, 151, 261));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
