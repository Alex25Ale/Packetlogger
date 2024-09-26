#include "PacketSenderUI.h"
#include "AddressFunctions.h"
#include "PacketUI.h"
#include "Config.h"

#include <QTimer>
#include <QPalette>

static const QStringList s_asSpam = { "Start", "Stop" };
static const QStringList s_asSpamReceive = { "Start Receive", "Stop Receive" };

CPacketSenderUI::CPacketSenderUI(CPacketSender* i_pParent)
    : QGroupBox(i_pParent), m_fIsSpamStarted(false), m_fIsSpamReceiveStarted(false)
{
    this->m_oUI.setupUi(this);

    // Applying a dark theme to buttons in the constructor
    this->setStyleSheet("QGroupBox { background-color: #2E2E2E; color: white; border: none; }"   // GroupBox without border
        "QPushButton { background-color: #2E2E2E; color: white; }"   // Button
        "QTextEdit { background-color: #1E1E1E; color: white; }"     // TextEdit
        "QSpinBox { background-color: #1E1E1E; color: white; }"       // SpinBox
        "QLabel { color: white; }");                                  // Label

    connect(this->m_oUI.pbSend, &QPushButton::clicked, this, &CPacketSenderUI::onSendPacket);
    connect(this->m_oUI.pbSpam, &QPushButton::clicked, this, &CPacketSenderUI::onSpamPacket);
    connect(this->m_oUI.pbReceive, &QPushButton::clicked, this, &CPacketSenderUI::onReceivePacket);
    connect(this->m_oUI.pbSpamReceive, &QPushButton::clicked, this, &CPacketSenderUI::onSpamReceivePacket);
}

CPacketSenderUI::~CPacketSenderUI()
{
}

void CPacketSenderUI::onSendPacket() const
{
    if (this->m_oUI.teSendPackets->toPlainText().isEmpty()) return;

    QStringList asPackets = this->m_oUI.teSendPackets->toPlainText().split('\n');
    for (const QString& sPacket : asPackets) {
        if (sPacket.isEmpty()) continue;

        SendPacket(sPacket);
    }
}

void CPacketSenderUI::onSpamPacketTick() const
{
    if (this->m_fIsSpamStarted) {
        this->onSendPacket();
        QTimer::singleShot(this->m_oUI.sbTime->value(), this, &CPacketSenderUI::onSpamPacketTick);
    }
}

void CPacketSenderUI::onSpamPacket()
{
    this->m_fIsSpamStarted = !this->m_fIsSpamStarted;
    this->m_oUI.pbSpam->setText(s_asSpam[this->m_fIsSpamStarted]);

    if (this->m_fIsSpamStarted)
        onSpamPacketTick();
}

void CPacketSenderUI::onReceivePacket() const
{
    if (this->m_oUI.teReceivePackets->toPlainText().isEmpty()) return;

    QStringList asPackets = this->m_oUI.teReceivePackets->toPlainText().split('\n');
    for (const QString& sPacket : asPackets) {
        if (sPacket.isEmpty()) continue;

        RecvPacket(sPacket);
    }
}

void CPacketSenderUI::onSpamReceivePacketTick() const
{
    if (this->m_fIsSpamReceiveStarted) {
        this->onReceivePacket();
        QTimer::singleShot(this->m_oUI.sbTime_2->value(), this, &CPacketSenderUI::onSpamReceivePacketTick);
    }
}

void CPacketSenderUI::onSpamReceivePacket()
{
    this->m_fIsSpamReceiveStarted = !this->m_fIsSpamReceiveStarted;
    this->m_oUI.pbSpamReceive->setText(s_asSpamReceive[this->m_fIsSpamReceiveStarted]);

    if (this->m_fIsSpamReceiveStarted)
        onSpamReceivePacketTick();
}

CPacketSender::CPacketSender(CPacketUI* i_pParent)
    : QDialog(i_pParent), m_oInterface(this)
{
    this->setObjectName("CPacketSender");
    this->setStyleSheet("#CPacketSender { background-color: #1E1E1E; }"); // Dark background for the dialog

    this->setWindowTitle("[PacketLogger] Sender");

    this->m_oInterface.move(0, 0);

    this->adjustSize();

    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());

    this->m_oInterface.show();
}

CPacketSender::~CPacketSender()
{
}
