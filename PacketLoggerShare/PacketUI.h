#pragma once

#include <QMainWindow>
#include <QMouseEvent>
#include <QMenu>
#include <QKeyEvent>
#include <QCloseEvent>

#include "ui_PacketUI.h"
#include "PacketSenderUI.h"
#include "FilterUI.h"
#include "DamageCounterUI.h"  // Ensure proper inclusion of header

enum EPacketType {
    PTReceive,
    PTSend,
};

class CPacketUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit CPacketUI(QWidget* i_pParent = nullptr);
    ~CPacketUI();

signals:
    void addPacket(const QString&, int);

private slots:
    void onAddPacket(const QString& i_sPacket, int i_iPacketType);
    void onAdvancedLWMove(QMouseEvent* i_pEvent);
    void onAdvancedGBLeave(QEvent* i_pEvent);
    void onLogClearClicked();
    void keyPressEvent(QKeyEvent* i_pEvent) override;
    void onSendFilter() { this->m_oSendFilter.show(); }
    void onRecvFilter() { this->m_oRecvFilter.show(); }
    void onSendBlocker() { this->m_oSendBlocker.show(); }
    void onRecvBlocker() { this->m_oRecvBlocker.show(); }
    void onSenderPressed() { this->m_oSenderUI.show(); }
    void onDamageCounterPressed(); // Slot to handle the button press

    void closeEvent(QCloseEvent* i_pEvent);
    void menuTriggered(QAction* i_pAction);
    void setupScrollbarStyles(); // Declaration of the setupScrollbarStyles function

public:
    CFilterUI& sendFilter() { return m_oSendFilter; }
    CFilterUI& recvFilter() { return m_oRecvFilter; }
    CFilterUI& sendBlocker() { return m_oSendBlocker; }
    CFilterUI& recvBlocker() { return m_oRecvBlocker; }

private:
    Ui::CPacketUI m_oUI;
    QMenu* m_pLWMenu;

    CPacketSender m_oSenderUI;
    CFilterUI m_oSendFilter;
    CFilterUI m_oRecvFilter;
    CFilterUI m_oSendBlocker;
    CFilterUI m_oRecvBlocker;

    CDamageCounterUI* m_oDamageCounterUI = nullptr; // Initialize to nullptr

    bool m_bIsDamageCounterConnected; // Flag to track connection status
    bool m_bIsInButtonClick = false;  // Initialize to false
};