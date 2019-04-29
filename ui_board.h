/********************************************************************************
** Form generated from reading UI file 'board.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOARD_H
#define UI_BOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Board
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridChBoard;
    QLabel *whiteNumber;
    QLabel *blackNuber;
    QTextBrowser *debug;

    void setupUi(QDialog *Board)
    {
        if (Board->objectName().isEmpty())
            Board->setObjectName(QString::fromUtf8("Board"));
        Board->setEnabled(true);
        Board->resize(802, 685);
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
        Board->setPalette(palette);
        gridLayoutWidget = new QWidget(Board);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(350, 190, 281, 271));
        gridChBoard = new QGridLayout(gridLayoutWidget);
        gridChBoard->setSpacing(0);
        gridChBoard->setObjectName(QString::fromUtf8("gridChBoard"));
        gridChBoard->setContentsMargins(0, 0, 0, 0);
        whiteNumber = new QLabel(Board);
        whiteNumber->setObjectName(QString::fromUtf8("whiteNumber"));
        whiteNumber->setGeometry(QRect(70, 30, 91, 21));
        blackNuber = new QLabel(Board);
        blackNuber->setObjectName(QString::fromUtf8("blackNuber"));
        blackNuber->setGeometry(QRect(610, 30, 121, 21));
        debug = new QTextBrowser(Board);
        debug->setObjectName(QString::fromUtf8("debug"));
        debug->setGeometry(QRect(10, 70, 311, 411));

        retranslateUi(Board);

        QMetaObject::connectSlotsByName(Board);
    } // setupUi

    void retranslateUi(QDialog *Board)
    {
        Board->setWindowTitle(QApplication::translate("Board", "Dialog", nullptr));
        whiteNumber->setText(QApplication::translate("Board", "White: 12", nullptr));
        blackNuber->setText(QApplication::translate("Board", "Black: 12", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Board: public Ui_Board {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOARD_H
