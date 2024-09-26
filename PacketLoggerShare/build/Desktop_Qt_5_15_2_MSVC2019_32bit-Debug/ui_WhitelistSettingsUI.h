/********************************************************************************
** Form generated from reading UI file 'WhitelistSettingsUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHITELISTSETTINGSUI_H
#define UI_WHITELISTSETTINGSUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WhitelistSettingsUI
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *whitelistWidget;
    QPushButton *addButton;
    QPushButton *removeButton;

    void setupUi(QDialog *WhitelistSettingsUI)
    {
        if (WhitelistSettingsUI->objectName().isEmpty())
            WhitelistSettingsUI->setObjectName(QString::fromUtf8("WhitelistSettingsUI"));
        WhitelistSettingsUI->resize(300, 400);
        verticalLayout = new QVBoxLayout(WhitelistSettingsUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        whitelistWidget = new QListWidget(WhitelistSettingsUI);
        whitelistWidget->setObjectName(QString::fromUtf8("whitelistWidget"));

        verticalLayout->addWidget(whitelistWidget);

        addButton = new QPushButton(WhitelistSettingsUI);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout->addWidget(addButton);

        removeButton = new QPushButton(WhitelistSettingsUI);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout->addWidget(removeButton);


        retranslateUi(WhitelistSettingsUI);

        QMetaObject::connectSlotsByName(WhitelistSettingsUI);
    } // setupUi

    void retranslateUi(QDialog *WhitelistSettingsUI)
    {
        WhitelistSettingsUI->setWindowTitle(QCoreApplication::translate("WhitelistSettingsUI", "Whitelist Settings", nullptr));
        addButton->setText(QCoreApplication::translate("WhitelistSettingsUI", "Add Character", nullptr));
        removeButton->setText(QCoreApplication::translate("WhitelistSettingsUI", "Remove Character", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WhitelistSettingsUI: public Ui_WhitelistSettingsUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHITELISTSETTINGSUI_H
