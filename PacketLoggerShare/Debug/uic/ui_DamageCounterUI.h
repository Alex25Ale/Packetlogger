/********************************************************************************
** Form generated from reading UI file 'DamageCounterUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DAMAGECOUNTERUI_H
#define UI_DAMAGECOUNTERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDamageCounterUI
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *currentRaidTab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *currentRaidTable;
    QHBoxLayout *horizontalLayout_1;
    QPushButton *exportCurrentRaidButton;
    QPushButton *resetCurrentRaidButton;
    QWidget *allRaidsTab;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *allRaidsTable;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *exportAllRaidsButton;
    QPushButton *resetAllRaidsButton;
    QWidget *landOfLifeTab;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *landOfLifeTable;
    QWidget *instantCombatTab;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *instantCombatTable;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *whitelistToggleButton;
    QPushButton *whitelistSettingsButton;

    void setupUi(QWidget *CDamageCounterUI)
    {
        if (CDamageCounterUI->objectName().isEmpty())
            CDamageCounterUI->setObjectName(QString::fromUtf8("CDamageCounterUI"));
        CDamageCounterUI->resize(1000, 600);
        verticalLayout = new QVBoxLayout(CDamageCounterUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(CDamageCounterUI);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        currentRaidTab = new QWidget();
        currentRaidTab->setObjectName(QString::fromUtf8("currentRaidTab"));
        verticalLayout_2 = new QVBoxLayout(currentRaidTab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        currentRaidTable = new QTableWidget(currentRaidTab);
        if (currentRaidTable->columnCount() < 13)
            currentRaidTable->setColumnCount(13);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        currentRaidTable->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        currentRaidTable->setObjectName(QString::fromUtf8("currentRaidTable"));
        currentRaidTable->setColumnCount(13);
        currentRaidTable->horizontalHeader()->setVisible(true);
        currentRaidTable->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(currentRaidTable);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        exportCurrentRaidButton = new QPushButton(currentRaidTab);
        exportCurrentRaidButton->setObjectName(QString::fromUtf8("exportCurrentRaidButton"));

        horizontalLayout_1->addWidget(exportCurrentRaidButton);

        resetCurrentRaidButton = new QPushButton(currentRaidTab);
        resetCurrentRaidButton->setObjectName(QString::fromUtf8("resetCurrentRaidButton"));

        horizontalLayout_1->addWidget(resetCurrentRaidButton);


        verticalLayout_2->addLayout(horizontalLayout_1);

        tabWidget->addTab(currentRaidTab, QString());
        allRaidsTab = new QWidget();
        allRaidsTab->setObjectName(QString::fromUtf8("allRaidsTab"));
        verticalLayout_3 = new QVBoxLayout(allRaidsTab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        allRaidsTable = new QTableWidget(allRaidsTab);
        if (allRaidsTable->columnCount() < 13)
            allRaidsTable->setColumnCount(13);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(3, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(4, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(5, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(6, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(7, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(8, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(9, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(10, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(11, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        allRaidsTable->setHorizontalHeaderItem(12, __qtablewidgetitem25);
        allRaidsTable->setObjectName(QString::fromUtf8("allRaidsTable"));
        allRaidsTable->setColumnCount(13);
        allRaidsTable->horizontalHeader()->setVisible(true);
        allRaidsTable->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(allRaidsTable);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        exportAllRaidsButton = new QPushButton(allRaidsTab);
        exportAllRaidsButton->setObjectName(QString::fromUtf8("exportAllRaidsButton"));

        horizontalLayout_2->addWidget(exportAllRaidsButton);

        resetAllRaidsButton = new QPushButton(allRaidsTab);
        resetAllRaidsButton->setObjectName(QString::fromUtf8("resetAllRaidsButton"));

        horizontalLayout_2->addWidget(resetAllRaidsButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tabWidget->addTab(allRaidsTab, QString());
        landOfLifeTab = new QWidget();
        landOfLifeTab->setObjectName(QString::fromUtf8("landOfLifeTab"));
        verticalLayout_4 = new QVBoxLayout(landOfLifeTab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        landOfLifeTable = new QTableWidget(landOfLifeTab);
        landOfLifeTable->setObjectName(QString::fromUtf8("landOfLifeTable"));
        landOfLifeTable->setColumnCount(0);
        landOfLifeTable->horizontalHeader()->setVisible(true);
        landOfLifeTable->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(landOfLifeTable);

        tabWidget->addTab(landOfLifeTab, QString());
        instantCombatTab = new QWidget();
        instantCombatTab->setObjectName(QString::fromUtf8("instantCombatTab"));
        verticalLayout_5 = new QVBoxLayout(instantCombatTab);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        instantCombatTable = new QTableWidget(instantCombatTab);
        if (instantCombatTable->columnCount() < 5)
            instantCombatTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        instantCombatTable->setHorizontalHeaderItem(0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        instantCombatTable->setHorizontalHeaderItem(1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        instantCombatTable->setHorizontalHeaderItem(2, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        instantCombatTable->setHorizontalHeaderItem(3, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        instantCombatTable->setHorizontalHeaderItem(4, __qtablewidgetitem30);
        instantCombatTable->setObjectName(QString::fromUtf8("instantCombatTable"));
        instantCombatTable->setColumnCount(5);
        instantCombatTable->horizontalHeader()->setVisible(true);
        instantCombatTable->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(instantCombatTable);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        whitelistToggleButton = new QPushButton(instantCombatTab);
        whitelistToggleButton->setObjectName(QString::fromUtf8("whitelistToggleButton"));

        horizontalLayout_3->addWidget(whitelistToggleButton);

        whitelistSettingsButton = new QPushButton(instantCombatTab);
        whitelistSettingsButton->setObjectName(QString::fromUtf8("whitelistSettingsButton"));

        horizontalLayout_3->addWidget(whitelistSettingsButton);


        verticalLayout_5->addLayout(horizontalLayout_3);

        tabWidget->addTab(instantCombatTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(CDamageCounterUI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CDamageCounterUI);
    } // setupUi

    void retranslateUi(QWidget *CDamageCounterUI)
    {
        CDamageCounterUI->setWindowTitle(QCoreApplication::translate("CDamageCounterUI", "Damage Counter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = currentRaidTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CDamageCounterUI", "Level", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = currentRaidTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CDamageCounterUI", "Character Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = currentRaidTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CDamageCounterUI", "Boss Damage", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = currentRaidTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CDamageCounterUI", "Average Boss", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = currentRaidTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CDamageCounterUI", "Max Hit", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = currentRaidTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("CDamageCounterUI", "Hits", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = currentRaidTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("CDamageCounterUI", "Miss", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = currentRaidTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("CDamageCounterUI", "Crit", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = currentRaidTable->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("CDamageCounterUI", "All Hits", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = currentRaidTable->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("CDamageCounterUI", "Total Damage", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = currentRaidTable->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("CDamageCounterUI", "Average Total", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = currentRaidTable->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("CDamageCounterUI", "Gold", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = currentRaidTable->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("CDamageCounterUI", "Deaths", nullptr));
        exportCurrentRaidButton->setText(QCoreApplication::translate("CDamageCounterUI", "Export Table", nullptr));
        resetCurrentRaidButton->setText(QCoreApplication::translate("CDamageCounterUI", "Reset", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(currentRaidTab), QCoreApplication::translate("CDamageCounterUI", "Current Raid", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = allRaidsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("CDamageCounterUI", "Level", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = allRaidsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("CDamageCounterUI", "Character Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = allRaidsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("CDamageCounterUI", "Boss Damage", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = allRaidsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("CDamageCounterUI", "Average Boss", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = allRaidsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("CDamageCounterUI", "Max Hit", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = allRaidsTable->horizontalHeaderItem(5);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("CDamageCounterUI", "Hits", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = allRaidsTable->horizontalHeaderItem(6);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("CDamageCounterUI", "Miss", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = allRaidsTable->horizontalHeaderItem(7);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("CDamageCounterUI", "Crit", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = allRaidsTable->horizontalHeaderItem(8);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("CDamageCounterUI", "All Hits", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = allRaidsTable->horizontalHeaderItem(9);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("CDamageCounterUI", "Total Damage", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = allRaidsTable->horizontalHeaderItem(10);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("CDamageCounterUI", "Average Total", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = allRaidsTable->horizontalHeaderItem(11);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("CDamageCounterUI", "Gold", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = allRaidsTable->horizontalHeaderItem(12);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("CDamageCounterUI", "Deaths", nullptr));
        exportAllRaidsButton->setText(QCoreApplication::translate("CDamageCounterUI", "Export Table", nullptr));
        resetAllRaidsButton->setText(QCoreApplication::translate("CDamageCounterUI", "Reset", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(allRaidsTab), QCoreApplication::translate("CDamageCounterUI", "All Raids", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(landOfLifeTab), QCoreApplication::translate("CDamageCounterUI", "Land of Life", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = instantCombatTable->horizontalHeaderItem(0);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("CDamageCounterUI", "Level", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = instantCombatTable->horizontalHeaderItem(1);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("CDamageCounterUI", "Character Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = instantCombatTable->horizontalHeaderItem(2);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("CDamageCounterUI", "Damage Dealt", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = instantCombatTable->horizontalHeaderItem(3);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("CDamageCounterUI", "Damage Remaining", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = instantCombatTable->horizontalHeaderItem(4);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("CDamageCounterUI", "Damage Required This Round", nullptr));
        whitelistToggleButton->setText(QCoreApplication::translate("CDamageCounterUI", "Activate Whitelist", nullptr));
        whitelistSettingsButton->setText(QCoreApplication::translate("CDamageCounterUI", "Whitelist Settings", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(instantCombatTab), QCoreApplication::translate("CDamageCounterUI", "Instant Combat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDamageCounterUI: public Ui_CDamageCounterUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DAMAGECOUNTERUI_H
