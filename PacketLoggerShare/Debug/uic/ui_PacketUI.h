/********************************************************************************
** Form generated from reading UI file 'PacketUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKETUI_H
#define UI_PACKETUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "AdvancedGroupBox.h"
#include "AdvancedListWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CPacketUI
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    CAdvancedGroupBox *gbLoggerSettings;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pbSendFilter;
    QPushButton *pbRecvFilter;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pbSendBlocker;
    QPushButton *pbRecvBlocker;
    QPushButton *pbSender;
    QPushButton *pbDamageCounter;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer1;
    QCheckBox *cbAutoScroll;
    QSpacerItem *horizontalSpacer2;
    QCheckBox *cbLogSendPackets;
    QSpacerItem *horizontalSpacer3;
    QCheckBox *cbLogReceivePackets;
    QSpacerItem *horizontalSpacer4;
    CAdvancedListWidget *lwPacketList;
    QPushButton *pbClearLog;

    void setupUi(QMainWindow *CPacketUI)
    {
        if (CPacketUI->objectName().isEmpty())
            CPacketUI->setObjectName(QString::fromUtf8("CPacketUI"));
        CPacketUI->resize(800, 600);
        centralWidget = new QWidget(CPacketUI);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 800, 600));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gbLoggerSettings = new CAdvancedGroupBox(centralWidget);
        gbLoggerSettings->setObjectName(QString::fromUtf8("gbLoggerSettings"));
        verticalLayout_3 = new QVBoxLayout(gbLoggerSettings);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pbSendFilter = new QPushButton(gbLoggerSettings);
        pbSendFilter->setObjectName(QString::fromUtf8("pbSendFilter"));

        horizontalLayout_3->addWidget(pbSendFilter);

        pbRecvFilter = new QPushButton(gbLoggerSettings);
        pbRecvFilter->setObjectName(QString::fromUtf8("pbRecvFilter"));

        horizontalLayout_3->addWidget(pbRecvFilter);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pbSendBlocker = new QPushButton(gbLoggerSettings);
        pbSendBlocker->setObjectName(QString::fromUtf8("pbSendBlocker"));

        horizontalLayout_4->addWidget(pbSendBlocker);

        pbRecvBlocker = new QPushButton(gbLoggerSettings);
        pbRecvBlocker->setObjectName(QString::fromUtf8("pbRecvBlocker"));

        horizontalLayout_4->addWidget(pbRecvBlocker);


        verticalLayout_3->addLayout(horizontalLayout_4);

        pbSender = new QPushButton(gbLoggerSettings);
        pbSender->setObjectName(QString::fromUtf8("pbSender"));

        verticalLayout_3->addWidget(pbSender);

        pbDamageCounter = new QPushButton(gbLoggerSettings);
        pbDamageCounter->setObjectName(QString::fromUtf8("pbDamageCounter"));

        verticalLayout_3->addWidget(pbDamageCounter);


        verticalLayout->addWidget(gbLoggerSettings);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer1);

        cbAutoScroll = new QCheckBox(centralWidget);
        cbAutoScroll->setObjectName(QString::fromUtf8("cbAutoScroll"));
        cbAutoScroll->setChecked(true);

        horizontalLayout_2->addWidget(cbAutoScroll);

        horizontalSpacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer2);

        cbLogSendPackets = new QCheckBox(centralWidget);
        cbLogSendPackets->setObjectName(QString::fromUtf8("cbLogSendPackets"));
        cbLogSendPackets->setChecked(true);

        horizontalLayout_2->addWidget(cbLogSendPackets);

        horizontalSpacer3 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer3);

        cbLogReceivePackets = new QCheckBox(centralWidget);
        cbLogReceivePackets->setObjectName(QString::fromUtf8("cbLogReceivePackets"));
        cbLogReceivePackets->setChecked(true);

        horizontalLayout_2->addWidget(cbLogReceivePackets);

        horizontalSpacer4 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer4);


        verticalLayout->addLayout(horizontalLayout_2);

        lwPacketList = new CAdvancedListWidget(centralWidget);
        lwPacketList->setObjectName(QString::fromUtf8("lwPacketList"));
        lwPacketList->setLineWidth(1);
        lwPacketList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        lwPacketList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lwPacketList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        lwPacketList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lwPacketList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        lwPacketList->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        lwPacketList->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        lwPacketList->setWordWrap(false);
        lwPacketList->setSelectionRectVisible(false);

        verticalLayout->addWidget(lwPacketList);

        pbClearLog = new QPushButton(centralWidget);
        pbClearLog->setObjectName(QString::fromUtf8("pbClearLog"));

        verticalLayout->addWidget(pbClearLog);

        CPacketUI->setCentralWidget(centralWidget);
        QWidget::setTabOrder(cbLogSendPackets, pbSendFilter);
        QWidget::setTabOrder(pbSendFilter, cbLogReceivePackets);
        QWidget::setTabOrder(cbLogReceivePackets, pbRecvFilter);
        QWidget::setTabOrder(pbRecvFilter, cbAutoScroll);
        QWidget::setTabOrder(cbAutoScroll, pbClearLog);
        QWidget::setTabOrder(pbClearLog, lwPacketList);

        retranslateUi(CPacketUI);
        QObject::connect(lwPacketList, SIGNAL(mouseMoveEvent(QMouseEvent*)), CPacketUI, SLOT(onAdvancedLWMove(QMouseEvent*)));
        QObject::connect(pbClearLog, SIGNAL(clicked()), CPacketUI, SLOT(onLogClearClicked()));
        QObject::connect(gbLoggerSettings, SIGNAL(leaveEvent(QEvent*)), CPacketUI, SLOT(onAdvancedGBLeave(QEvent*)));
        QObject::connect(pbSendFilter, SIGNAL(clicked()), CPacketUI, SLOT(onSendFilter()));
        QObject::connect(pbRecvFilter, SIGNAL(clicked()), CPacketUI, SLOT(onRecvFilter()));
        QObject::connect(pbSendBlocker, SIGNAL(clicked()), CPacketUI, SLOT(onSendBlocker()));
        QObject::connect(pbRecvBlocker, SIGNAL(clicked()), CPacketUI, SLOT(onRecvBlocker()));
        QObject::connect(pbSender, SIGNAL(clicked()), CPacketUI, SLOT(onSenderPressed()));
        QObject::connect(pbDamageCounter, SIGNAL(clicked()), CPacketUI, SLOT(onDamageCounterPressed()));

        QMetaObject::connectSlotsByName(CPacketUI);
    } // setupUi

    void retranslateUi(QMainWindow *CPacketUI)
    {
        CPacketUI->setWindowTitle(QCoreApplication::translate("CPacketUI", "Alerian Logger", nullptr));
        centralWidget->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"     background-color: #1E1E1E; /* Background color of the central widget */\n"
"     color: white; /* Default text color */\n"
"    ", nullptr));
        gbLoggerSettings->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"        background-color: #2E2E2E; /* Group box background color */\n"
"        color: white; /* Text color in group box */\n"
"       ", nullptr));
        pbSendFilter->setText(QCoreApplication::translate("CPacketUI", "Send Filter", nullptr));
        pbSendFilter->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"             background-color: #2E2E2E; /* Button background color */\n"
"             color: white; /* Button text color */\n"
"            ", nullptr));
        pbRecvFilter->setText(QCoreApplication::translate("CPacketUI", "Receive Filter", nullptr));
        pbRecvFilter->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"             background-color: #2E2E2E; /* Button background color */\n"
"             color: white; /* Button text color */\n"
"            ", nullptr));
        pbSendBlocker->setText(QCoreApplication::translate("CPacketUI", "Send Blocker", nullptr));
        pbSendBlocker->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"             background-color: #2E2E2E; /* Button background color */\n"
"             color: white; /* Button text color */\n"
"            ", nullptr));
        pbRecvBlocker->setText(QCoreApplication::translate("CPacketUI", "Receive Blocker", nullptr));
        pbRecvBlocker->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"             background-color: #2E2E2E; /* Button background color */\n"
"             color: white; /* Button text color */\n"
"            ", nullptr));
        pbSender->setText(QCoreApplication::translate("CPacketUI", "Sender", nullptr));
        pbSender->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"           background-color: #2E2E2E; /* Button background color */\n"
"           color: white; /* Button text color */\n"
"          ", nullptr));
        pbDamageCounter->setText(QCoreApplication::translate("CPacketUI", "Damage Counter", nullptr));
        pbDamageCounter->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"           background-color: #2E2E2E; /* Button background color */\n"
"           color: white; /* Button text color */\n"
"          ", nullptr));
        cbAutoScroll->setText(QCoreApplication::translate("CPacketUI", "Scroll", nullptr));
        cbAutoScroll->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"          color: white; /* Checkbox text color */\n"
"         ", nullptr));
        cbLogSendPackets->setText(QCoreApplication::translate("CPacketUI", "Log Send", nullptr));
        cbLogSendPackets->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"          color: white; /* Checkbox text color */\n"
"         ", nullptr));
        cbLogReceivePackets->setText(QCoreApplication::translate("CPacketUI", "Log Recv", nullptr));
        cbLogReceivePackets->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"          color: white; /* Checkbox text color */\n"
"         ", nullptr));
        lwPacketList->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"        background-color: #1E1E1E; /* List widget background color */\n"
"        color: white; /* Text color in list */\n"
"       ", nullptr));
        pbClearLog->setText(QCoreApplication::translate("CPacketUI", "Clear Log", nullptr));
        pbClearLog->setStyleSheet(QCoreApplication::translate("CPacketUI", "\n"
"        background-color: #2E2E2E; /* Button background color */\n"
"        color: white; /* Button text color */\n"
"       ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CPacketUI: public Ui_CPacketUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACKETUI_H
