/********************************************************************************
** Form generated from reading UI file 'FilterUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERUI_H
#define UI_FILTERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CFilterUI
{
public:
    QListWidget *lwFilter;
    QLineEdit *leFilterData;
    QLabel *lFilter;
    QCheckBox *cbActivated;
    QRadioButton *rbWhitelist;
    QRadioButton *rbBlacklist;
    QRadioButton *rbContains;
    QRadioButton *rbRegular;
    QRadioButton *rbBeginWith;
    QRadioButton *rbEndsWith;
    QRadioButton *rbPacketName;
    QPushButton *pbAdd;
    QPushButton *pbRemove;
    QButtonGroup *bg2;
    QButtonGroup *bg1;

    void setupUi(QWidget *CFilterUI)
    {
        if (CFilterUI->objectName().isEmpty())
            CFilterUI->setObjectName(QString::fromUtf8("CFilterUI"));
        CFilterUI->resize(328, 400);
        CFilterUI->setStyleSheet(QString::fromUtf8("\n"
"QTextEdit, QGroupBox, QListWidget, QLabel, QCheckBox, QRadioButton, QLineEdit {\n"
"    background-color: #2E2E2E; /* Darker background */\n"
"    font: 10pt \"Verdana\"; /* Consistent font size */\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #4B4B4B; /* Darker gray */\n"
"    border: 1px solid #555; /* Subtle border */\n"
"    color: white; /* Font color */\n"
"    padding: 5px; /* Padding for better interaction */\n"
"    border-radius: 5px; /* Rounded corners */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #666666; /* Lighter on hover */\n"
"}\n"
"\n"
"QListWidget {\n"
"    background-color: #1E1E1E; /* Dark background for list widget */\n"
"    color: white; /* Text color */\n"
"    border: 1px solid #444; /* Subtle border */\n"
"    padding: 5px; /* Padding for better spacing */\n"
"    border-radius: 5px; /* Rounded corners */\n"
"}\n"
"\n"
"#CFilterUI {\n"
"    background-color: #2E2E2E; /* Dark theme for the entire window */\n"
"}\n"
"   "));
        lwFilter = new QListWidget(CFilterUI);
        lwFilter->setObjectName(QString::fromUtf8("lwFilter"));
        lwFilter->setGeometry(QRect(0, -1, 161, 401));
        leFilterData = new QLineEdit(CFilterUI);
        leFilterData->setObjectName(QString::fromUtf8("leFilterData"));
        leFilterData->setGeometry(QRect(170, 50, 151, 30));
        lFilter = new QLabel(CFilterUI);
        lFilter->setObjectName(QString::fromUtf8("lFilter"));
        lFilter->setGeometry(QRect(170, 20, 47, 20));
        cbActivated = new QCheckBox(CFilterUI);
        cbActivated->setObjectName(QString::fromUtf8("cbActivated"));
        cbActivated->setGeometry(QRect(170, 20, 160, 20));
        cbActivated->setChecked(true);
        rbWhitelist = new QRadioButton(CFilterUI);
        bg1 = new QButtonGroup(CFilterUI);
        bg1->setObjectName(QString::fromUtf8("bg1"));
        bg1->addButton(rbWhitelist);
        rbWhitelist->setObjectName(QString::fromUtf8("rbWhitelist"));
        rbWhitelist->setGeometry(QRect(250, 250, 100, 20));
        rbWhitelist->setChecked(false);
        rbBlacklist = new QRadioButton(CFilterUI);
        bg1->addButton(rbBlacklist);
        rbBlacklist->setObjectName(QString::fromUtf8("rbBlacklist"));
        rbBlacklist->setGeometry(QRect(170, 250, 76, 20));
        rbBlacklist->setChecked(true);
        rbContains = new QRadioButton(CFilterUI);
        bg2 = new QButtonGroup(CFilterUI);
        bg2->setObjectName(QString::fromUtf8("bg2"));
        bg2->addButton(rbContains);
        rbContains->setObjectName(QString::fromUtf8("rbContains"));
        rbContains->setGeometry(QRect(170, 100, 100, 20));
        rbRegular = new QRadioButton(CFilterUI);
        bg2->addButton(rbRegular);
        rbRegular->setObjectName(QString::fromUtf8("rbRegular"));
        rbRegular->setGeometry(QRect(170, 130, 150, 20));
        rbBeginWith = new QRadioButton(CFilterUI);
        bg2->addButton(rbBeginWith);
        rbBeginWith->setObjectName(QString::fromUtf8("rbBeginWith"));
        rbBeginWith->setGeometry(QRect(170, 160, 100, 20));
        rbBeginWith->setChecked(true);
        rbEndsWith = new QRadioButton(CFilterUI);
        bg2->addButton(rbEndsWith);
        rbEndsWith->setObjectName(QString::fromUtf8("rbEndsWith"));
        rbEndsWith->setGeometry(QRect(170, 190, 100, 20));
        rbPacketName = new QRadioButton(CFilterUI);
        bg2->addButton(rbPacketName);
        rbPacketName->setObjectName(QString::fromUtf8("rbPacketName"));
        rbPacketName->setGeometry(QRect(170, 220, 120, 20));
        pbAdd = new QPushButton(CFilterUI);
        pbAdd->setObjectName(QString::fromUtf8("pbAdd"));
        pbAdd->setGeometry(QRect(177, 300, 141, 30));
        pbRemove = new QPushButton(CFilterUI);
        pbRemove->setObjectName(QString::fromUtf8("pbRemove"));
        pbRemove->setGeometry(QRect(177, 340, 141, 30));
        QWidget::setTabOrder(lwFilter, leFilterData);
        QWidget::setTabOrder(leFilterData, pbAdd);
        QWidget::setTabOrder(pbAdd, pbRemove);

        retranslateUi(CFilterUI);
        QObject::connect(leFilterData, SIGNAL(returnPressed()), CFilterUI, SLOT(onReturnPressed()));
        QObject::connect(pbAdd, SIGNAL(clicked()), CFilterUI, SLOT(onAddPressed()));
        QObject::connect(pbRemove, SIGNAL(clicked()), CFilterUI, SLOT(onRemovePressed()));

        QMetaObject::connectSlotsByName(CFilterUI);
    } // setupUi

    void retranslateUi(QWidget *CFilterUI)
    {
        CFilterUI->setWindowTitle(QCoreApplication::translate("CFilterUI", "Filter", nullptr));
        lFilter->setText(QCoreApplication::translate("CFilterUI", "Filter:", nullptr));
        cbActivated->setText(QCoreApplication::translate("CFilterUI", "Filter activated", nullptr));
        rbWhitelist->setText(QCoreApplication::translate("CFilterUI", "Whitelist", nullptr));
        rbBlacklist->setText(QCoreApplication::translate("CFilterUI", "Blacklist", nullptr));
        rbContains->setText(QCoreApplication::translate("CFilterUI", "Contains", nullptr));
        rbRegular->setText(QCoreApplication::translate("CFilterUI", "Regular Expression", nullptr));
        rbBeginWith->setText(QCoreApplication::translate("CFilterUI", "Begins with", nullptr));
        rbEndsWith->setText(QCoreApplication::translate("CFilterUI", "Ends with", nullptr));
        rbPacketName->setText(QCoreApplication::translate("CFilterUI", "Packet Name", nullptr));
        pbAdd->setText(QCoreApplication::translate("CFilterUI", "Add", nullptr));
        pbRemove->setText(QCoreApplication::translate("CFilterUI", "Remove Selected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CFilterUI: public Ui_CFilterUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERUI_H
