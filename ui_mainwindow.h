/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
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
    QLabel *whiteNumber;
    QLabel *blackNuber;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridChBoard;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(650, 650);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(255, 255, 197, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        MainWindow->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 320, 221, 221));
        checkerBoard = new QGridLayout(gridLayoutWidget);
        checkerBoard->setSpacing(0);
        checkerBoard->setContentsMargins(11, 11, 11, 11);
        checkerBoard->setObjectName(QString::fromUtf8("checkerBoard"));
        checkerBoard->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        layout1 = new QHBoxLayout();
        layout1->setSpacing(0);
        layout1->setObjectName(QString::fromUtf8("layout1"));

        verticalLayout->addLayout(layout1);

        layout2 = new QHBoxLayout();
        layout2->setSpacing(0);
        layout2->setObjectName(QString::fromUtf8("layout2"));

        verticalLayout->addLayout(layout2);

        layout3 = new QHBoxLayout();
        layout3->setSpacing(0);
        layout3->setObjectName(QString::fromUtf8("layout3"));

        verticalLayout->addLayout(layout3);

        layout4 = new QHBoxLayout();
        layout4->setSpacing(0);
        layout4->setObjectName(QString::fromUtf8("layout4"));

        verticalLayout->addLayout(layout4);

        layout5 = new QHBoxLayout();
        layout5->setSpacing(0);
        layout5->setObjectName(QString::fromUtf8("layout5"));

        verticalLayout->addLayout(layout5);

        layout6 = new QHBoxLayout();
        layout6->setSpacing(0);
        layout6->setObjectName(QString::fromUtf8("layout6"));

        verticalLayout->addLayout(layout6);

        layout7 = new QHBoxLayout();
        layout7->setSpacing(0);
        layout7->setObjectName(QString::fromUtf8("layout7"));

        verticalLayout->addLayout(layout7);

        layout8 = new QHBoxLayout();
        layout8->setSpacing(0);
        layout8->setObjectName(QString::fromUtf8("layout8"));

        verticalLayout->addLayout(layout8);


        checkerBoard->addLayout(verticalLayout, 0, 0, 1, 1);

        whiteNumber = new QLabel(centralWidget);
        whiteNumber->setObjectName(QString::fromUtf8("whiteNumber"));
        whiteNumber->setGeometry(QRect(40, 20, 81, 41));
        blackNuber = new QLabel(centralWidget);
        blackNuber->setObjectName(QString::fromUtf8("blackNuber"));
        blackNuber->setGeometry(QRect(530, 20, 81, 41));
        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(250, 120, 251, 251));
        gridChBoard = new QGridLayout(gridLayoutWidget_2);
        gridChBoard->setSpacing(0);
        gridChBoard->setContentsMargins(11, 11, 11, 11);
        gridChBoard->setObjectName(QString::fromUtf8("gridChBoard"));
        gridChBoard->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 650, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        whiteNumber->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">White: 12</span></p></body></html>", nullptr));
        blackNuber->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Black: 12</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
