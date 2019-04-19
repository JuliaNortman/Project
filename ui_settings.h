/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QPushButton *okButton;
    QLabel *label;
    QLabel *label_2;
    QRadioButton *botRadioButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QRadioButton *whiteRadioButton;
    QRadioButton *blackRadioButton;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(320, 240);
        Settings->setModal(true);
        okButton = new QPushButton(Settings);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(230, 210, 75, 23));
        label = new QLabel(Settings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 40, 41, 16));
        label_2 = new QLabel(Settings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 120, 61, 16));
        botRadioButton = new QRadioButton(Settings);
        botRadioButton->setObjectName(QString::fromUtf8("botRadioButton"));
        botRadioButton->setGeometry(QRect(150, 120, 82, 17));
        botRadioButton->setChecked(true);
        widget = new QWidget(Settings);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(120, 40, 84, 42));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        whiteRadioButton = new QRadioButton(widget);
        whiteRadioButton->setObjectName(QString::fromUtf8("whiteRadioButton"));
        whiteRadioButton->setChecked(true);

        verticalLayout->addWidget(whiteRadioButton);

        blackRadioButton = new QRadioButton(widget);
        blackRadioButton->setObjectName(QString::fromUtf8("blackRadioButton"));

        verticalLayout->addWidget(blackRadioButton);


        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Dialog", nullptr));
        okButton->setText(QApplication::translate("Settings", "OK", nullptr));
        label->setText(QApplication::translate("Settings", "Color:", nullptr));
        label_2->setText(QApplication::translate("Settings", "Opponent:", nullptr));
        botRadioButton->setText(QApplication::translate("Settings", "Bot", nullptr));
        whiteRadioButton->setText(QApplication::translate("Settings", "White", nullptr));
        blackRadioButton->setText(QApplication::translate("Settings", "Black", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
