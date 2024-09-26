#pragma once
#include <QGroupBox>
#include <QDialog>
#include "ui_PacketSenderUI.h"

class CPacketUI;
class CPacketSender;
class CPacketSenderUI : public QGroupBox
{
    Q_OBJECT
public:
    CPacketSenderUI(CPacketSender* i_pParent);
    ~CPacketSenderUI();

private slots:
    void onSendPacket() const;
    void onSpamPacketTick() const;
    void onSpamPacket();
    void onReceivePacket() const;
    void onSpamReceivePacketTick() const;
    void onSpamReceivePacket();

private:
    Ui::CPacketSenderUI m_oUI;
    bool m_fIsSpamStarted;
    bool m_fIsSpamReceiveStarted;
};

class CPacketSender : public QDialog {
    Q_OBJECT
public:
    CPacketSender(CPacketUI* i_pParent);
    ~CPacketSender();

private:
    CPacketSenderUI m_oInterface;
};
