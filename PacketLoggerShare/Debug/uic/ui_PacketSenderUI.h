/********************************************************************************
** Form generated from reading UI file 'PacketSenderUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKETSENDERUI_H
#define UI_PACKETSENDERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_CPacketSenderUI
{
public:
    QTextEdit *teSendPackets;
    QPushButton *pbSend;
    QPushButton *pbSpam;
    QSpinBox *sbTime;
    QLabel *lTime;
    QTextEdit *teReceivePackets;
    QPushButton *pbReceive;
    QPushButton *pbSpamReceive;
    QSpinBox *sbTime_2;
    QLabel *lTime_2;

    void setupUi(QGroupBox *CPacketSenderUI)
    {
        if (CPacketSenderUI->objectName().isEmpty())
            CPacketSenderUI->setObjectName(QString::fromUtf8("CPacketSenderUI"));
        CPacketSenderUI->resize(450, 487);
        teSendPackets = new QTextEdit(CPacketSenderUI);
        teSendPackets->setObjectName(QString::fromUtf8("teSendPackets"));
        teSendPackets->setGeometry(QRect(10, 20, 430, 150));
        pbSend = new QPushButton(CPacketSenderUI);
        pbSend->setObjectName(QString::fromUtf8("pbSend"));
        pbSend->setGeometry(QRect(10, 190, 120, 30));
        pbSpam = new QPushButton(CPacketSenderUI);
        pbSpam->setObjectName(QString::fromUtf8("pbSpam"));
        pbSpam->setGeometry(QRect(150, 190, 120, 30));
        sbTime = new QSpinBox(CPacketSenderUI);
        sbTime->setObjectName(QString::fromUtf8("sbTime"));
        sbTime->setGeometry(QRect(330, 190, 100, 30));
        sbTime->setMinimum(50);
        sbTime->setMaximum(2000000000);
        sbTime->setValue(100);
        lTime = new QLabel(CPacketSenderUI);
        lTime->setObjectName(QString::fromUtf8("lTime"));
        lTime->setGeometry(QRect(280, 197, 38, 16));
        teReceivePackets = new QTextEdit(CPacketSenderUI);
        teReceivePackets->setObjectName(QString::fromUtf8("teReceivePackets"));
        teReceivePackets->setGeometry(QRect(10, 250, 430, 150));
        pbReceive = new QPushButton(CPacketSenderUI);
        pbReceive->setObjectName(QString::fromUtf8("pbReceive"));
        pbReceive->setGeometry(QRect(10, 420, 120, 30));
        pbSpamReceive = new QPushButton(CPacketSenderUI);
        pbSpamReceive->setObjectName(QString::fromUtf8("pbSpamReceive"));
        pbSpamReceive->setGeometry(QRect(150, 420, 120, 30));
        sbTime_2 = new QSpinBox(CPacketSenderUI);
        sbTime_2->setObjectName(QString::fromUtf8("sbTime_2"));
        sbTime_2->setGeometry(QRect(330, 420, 100, 30));
        sbTime_2->setMinimum(50);
        sbTime_2->setMaximum(2000000000);
        sbTime_2->setValue(100);
        lTime_2 = new QLabel(CPacketSenderUI);
        lTime_2->setObjectName(QString::fromUtf8("lTime_2"));
        lTime_2->setGeometry(QRect(280, 427, 38, 16));

        retranslateUi(CPacketSenderUI);

        QMetaObject::connectSlotsByName(CPacketSenderUI);
    } // setupUi

    void retranslateUi(QGroupBox *CPacketSenderUI)
    {
        CPacketSenderUI->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"    background-color: #2E2E2E; /* Dark background for the group box */\n"
"    color: white; /* Default text color */\n"
"   ", nullptr));
        teSendPackets->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     background-color: #1E1E1E; /* Dark background for text edit */\n"
"     color: white; /* Text color */\n"
"     border: 1px solid #444; /* Subtle border */\n"
"     padding: 5px; /* Padding for better spacing */\n"
"    ", nullptr));
        pbSend->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     QPushButton {\n"
"         background-color: #4A4A4A; /* Darker button background color */\n"
"         color: white; /* Button text color */\n"
"         padding: 6px; /* Padding */\n"
"         border: none; /* No border for the button */\n"
"         border-radius: 5px; /* Rounded corners */\n"
"     }\n"
"     QPushButton:hover {\n"
"         background-color: #5A5A5A; /* Slightly lighter on hover */\n"
"     }\n"
"    ", nullptr));
        pbSend->setText(QCoreApplication::translate("CPacketSenderUI", "Send", nullptr));
        pbSpam->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     QPushButton {\n"
"         background-color: #4A4A4A; /* Darker button background color */\n"
"         color: white; /* Button text color */\n"
"         padding: 6px; /* Padding */\n"
"         border: none; /* No border for the button */\n"
"         border-radius: 5px; /* Rounded corners */\n"
"     }\n"
"     QPushButton:hover {\n"
"         background-color: #5A5A5A; /* Slightly lighter on hover */\n"
"     }\n"
"    ", nullptr));
        pbSpam->setText(QCoreApplication::translate("CPacketSenderUI", "Start", nullptr));
        sbTime->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     QSpinBox {\n"
"         background-color: #1E1E1E; /* Spin box background color */\n"
"         color: white; /* Text color */\n"
"         border: 1px solid #444; /* Subtle border */\n"
"         padding: 5px; /* Padding for better spacing */\n"
"     }\n"
"    ", nullptr));
        sbTime->setSuffix(QCoreApplication::translate("CPacketSenderUI", "ms", nullptr));
        lTime->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     color: white; /* Label text color */\n"
"     font-weight: bold; /* Bold font for emphasis */\n"
"    ", nullptr));
        lTime->setText(QCoreApplication::translate("CPacketSenderUI", "Time:", nullptr));
        teReceivePackets->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     background-color: #1E1E1E; /* Dark background for text edit */\n"
"     color: white; /* Text color */\n"
"     border: 1px solid #444; /* Subtle border */\n"
"     padding: 5px; /* Padding for better spacing */\n"
"    ", nullptr));
        pbReceive->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     QPushButton {\n"
"         background-color: #4A4A4A; /* Darker button background color */\n"
"         color: white; /* Button text color */\n"
"         padding: 6px; /* Padding */\n"
"         border: none; /* No border for the button */\n"
"         border-radius: 5px; /* Rounded corners */\n"
"     }\n"
"     QPushButton:hover {\n"
"         background-color: #5A5A5A; /* Slightly lighter on hover */\n"
"     }\n"
"    ", nullptr));
        pbReceive->setText(QCoreApplication::translate("CPacketSenderUI", "Receive", nullptr));
        pbSpamReceive->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     QPushButton {\n"
"         background-color: #4A4A4A; /* Darker button background color */\n"
"         color: white; /* Button text color */\n"
"         padding: 6px; /* Padding */\n"
"         border: none; /* No border for the button */\n"
"         border-radius: 5px; /* Rounded corners */\n"
"     }\n"
"     QPushButton:hover {\n"
"         background-color: #5A5A5A; /* Slightly lighter on hover */\n"
"     }\n"
"    ", nullptr));
        pbSpamReceive->setText(QCoreApplication::translate("CPacketSenderUI", "Start Receive", nullptr));
        sbTime_2->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     QSpinBox {\n"
"         background-color: #1E1E1E; /* Spin box background color */\n"
"         color: white; /* Text color */\n"
"         border: 1px solid #444; /* Subtle border */\n"
"         padding: 5px; /* Padding for better spacing */\n"
"     }\n"
"    ", nullptr));
        sbTime_2->setSuffix(QCoreApplication::translate("CPacketSenderUI", "ms", nullptr));
        lTime_2->setStyleSheet(QCoreApplication::translate("CPacketSenderUI", "\n"
"     color: white; /* Label text color */\n"
"     font-weight: bold; /* Bold font for emphasis */\n"
"    ", nullptr));
        lTime_2->setText(QCoreApplication::translate("CPacketSenderUI", "Time:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CPacketSenderUI: public Ui_CPacketSenderUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACKETSENDERUI_H
