#include "PacketUI.h"
#include "AddressFunctions.h"
#include "TcpServer.h"
#include "Config.h"
#include "DamageCounterUI.h"  // Include the header for CDamageCounterUI

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QClipboard>
#include <QTime>
#include <QTimer> 
#include <thread>
#include <QKeyEvent>  // Include for key events
#include <QScrollBar>  // Include for scrollbar customization

#ifdef ACTIVATE_FEATURE_TCP_SERVER
extern CTcpServer* g_pTcpServer;
#endif

const QColor g_oBackgroundColor = QColor(0x1E1E1E);
const QColor g_oForegroundColor = QColor(Qt::white); // New foreground color for dark theme
const QColor g_oMarkedColor = QColor(Qt::darkGray);

// Define other relevant colors
const QColor g_oButtonColor = QColor(0x2E2E2E);
const QColor g_oButtonTextColor = QColor(Qt::white);
const QColor g_oWidgetBackgroundColor = QColor(0x2E2E2E); // Background for look of dark theme

#define LW_MENU_COPY_SELECTED    "Copy Packets"
#define LW_MENU_RESEND_PACKET    "Resend Packets"
#define LW_MENU_SAVE_FILE        "Save Log to File"
#define LW_MENU_MARK_SELECTED    "Mark selected"
#define LW_MENU_UNMARK_ALL       "Unmark All"

#define START_SPLIT_PACKET    "["
#define SPLIT_PACKET        "]\t"
#define SEND_PREFIX         START_SPLIT_PACKET "Send"        SPLIT_PACKET
#define RECV_PREFIX         START_SPLIT_PACKET "Recv"        SPLIT_PACKET
#define UNKNOWN_PREFIX      START_SPLIT_PACKET "Unknown"    SPLIT_PACKET

CPacketUI::CPacketUI(QWidget* i_pParent)
    : QMainWindow(i_pParent),
    m_oSenderUI(this),
    m_oRecvFilter(this, FILTER_MACRO_RECV),
    m_oSendFilter(this, FILTER_MACRO_SEND),
    m_oRecvBlocker(this, FILTER_MACRO_RECV_BLOCK),
    m_oSendBlocker(this, FILTER_MACRO_SEND_BLOCK)
{
    this->m_oUI.setupUi(this);

    // Set dark palette for the application
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, g_oBackgroundColor);
    darkPalette.setColor(QPalette::WindowText, g_oForegroundColor);
    darkPalette.setColor(QPalette::Base, g_oWidgetBackgroundColor); // For input fields and areas
    darkPalette.setColor(QPalette::AlternateBase, g_oWidgetBackgroundColor);
    darkPalette.setColor(QPalette::ToolTipBase, g_oForegroundColor);
    darkPalette.setColor(QPalette::ToolTipText, g_oForegroundColor);
    darkPalette.setColor(QPalette::Text, g_oForegroundColor);
    darkPalette.setColor(QPalette::Button, g_oButtonColor);
    darkPalette.setColor(QPalette::ButtonText, g_oButtonTextColor);
    darkPalette.setColor(QPalette::Highlight, g_oMarkedColor);
    darkPalette.setColor(QPalette::HighlightedText, g_oForegroundColor);

    QApplication::setPalette(darkPalette);

    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());

    this->m_oUI.lwPacketList->setContextMenuPolicy(Qt::CustomContextMenu);
    this->m_oUI.lwPacketList->setUniformItemSizes(true);
    this->m_oUI.lwPacketList->setMouseTracking(true);

    // Show the logger settings group box at startup
    this->m_oUI.gbLoggerSettings->setVisible(true);

    // Setup context menu actions
    this->m_pLWMenu = new QMenu(this);
    this->m_pLWMenu->addAction(new QAction(LW_MENU_COPY_SELECTED, this->m_pLWMenu));
    this->m_pLWMenu->addAction(new QAction(LW_MENU_RESEND_PACKET, this->m_pLWMenu));
    this->m_pLWMenu->addAction(new QAction(LW_MENU_SAVE_FILE, this->m_pLWMenu));
    this->m_pLWMenu->addAction(new QAction(LW_MENU_MARK_SELECTED, this->m_pLWMenu));
    this->m_pLWMenu->addAction(new QAction(LW_MENU_UNMARK_ALL, this->m_pLWMenu));
    connect(this->m_pLWMenu, &QMenu::triggered, this, &CPacketUI::menuTriggered);

    connect(this->m_oUI.lwPacketList, &QListWidget::customContextMenuRequested, [=](const QPoint& i_oPoint) {
        this->m_pLWMenu->exec(this->m_oUI.lwPacketList->mapToGlobal(i_oPoint));
        });

    connect(this, &CPacketUI::addPacket, this, &CPacketUI::onAddPacket);

    // Connect the button to the slot for DamageCounter

    connect(m_oUI.pbDamageCounter, &QPushButton::clicked, this, &CPacketUI::onDamageCounterPressed);

    setupScrollbarStyles();
}

void CPacketUI::onDamageCounterPressed()
{
    if (!m_oDamageCounterUI) {
        m_oDamageCounterUI = new CDamageCounterUI(nullptr); // Create as a top-level window
        m_oDamageCounterUI->setAttribute(Qt::WA_DeleteOnClose); // Ensure it's deleted when closed
        connect(m_oDamageCounterUI, &QObject::destroyed, this, [this]() {
            m_oDamageCounterUI = nullptr;
            });
    }

    m_oDamageCounterUI->show();
    m_oDamageCounterUI->raise();
    m_oDamageCounterUI->activateWindow();
}

CPacketUI::~CPacketUI() {
    if (m_oDamageCounterUI) {
        delete m_oDamageCounterUI;
        m_oDamageCounterUI = nullptr;
    }
}

void CPacketUI::keyPressEvent(QKeyEvent* i_pEvent)
{
    if (i_pEvent->modifiers() & Qt::ControlModifier && i_pEvent->key() == Qt::Key_C) {
        QList<QListWidgetItem*> selectedItems = this->m_oUI.lwPacketList->selectedItems();
        if (!selectedItems.isEmpty()) {
            QString clipboardText;
            for (QListWidgetItem* item : selectedItems) {
                QStringList rawPacket = item->text().split(SPLIT_PACKET);
                if (rawPacket.size() >= 3) {
                    clipboardText += rawPacket[2] + "\n";
                }
            }
            QApplication::clipboard()->setText(clipboardText.trimmed());
        }
        i_pEvent->accept(); // Indicate that the event has been handled
    }
    else {
        QMainWindow::keyPressEvent(i_pEvent); // Handle other key events normally
    }
}

void CPacketUI::onAdvancedLWMove(QMouseEvent* i_pEvent)
{
    // Removed the logic related to showing/hiding the settings group box
}

void CPacketUI::onAdvancedGBLeave(QEvent* i_pEvent)
{
    // Removed the logic related to showing/hiding the settings group box
}

void CPacketUI::onLogClearClicked()
{
    this->m_oUI.lwPacketList->clear();
}

void CPacketUI::closeEvent(QCloseEvent* i_pEvent)
{
    m_oRecvFilter.safe(true);
    m_oSendFilter.safe(true);
    QApplication::exit();
}

void CPacketUI::menuTriggered(QAction* i_pAction)
{
    if (i_pAction->text() == LW_MENU_SAVE_FILE) {
        QFileDialog oDialog;
        oDialog.setWindowTitle("Select File");
        oDialog.setNameFilter("File (*.*)");
        oDialog.setFileMode(QFileDialog::AnyFile);
        if (oDialog.exec()) {
            QString sFile = oDialog.selectedFiles()[0];
            QFile oFile(sFile);
            if (oFile.open(QIODevice::WriteOnly)) {
                QTextStream oStream(&oFile);
                for (int i = 0, iSize = this->m_oUI.lwPacketList->count(); i < iSize; i++)
                    oStream << this->m_oUI.lwPacketList->item(i)->text() << "\n";
                QMessageBox::information(0, "[PacketLogger] - Information", "File saved in '" + sFile + "'!");
            }
            else
                QMessageBox::warning(0, "[PacketLogger] - Error", "Couldn't open File '" + sFile + "'!");
        }
    }
    else if (i_pAction->text() == LW_MENU_RESEND_PACKET) {
        QList<QListWidgetItem*> itemsToResend;

        // Collect all selected and marked items
        for (int i = 0; i < this->m_oUI.lwPacketList->count(); ++i) {
            QListWidgetItem* pItem = this->m_oUI.lwPacketList->item(i);
            if (pItem->isSelected() || pItem->background().color() == g_oMarkedColor) {
                itemsToResend.append(pItem);
            }
        }

        if (!itemsToResend.isEmpty()) {
            for (QListWidgetItem* pItem : itemsToResend) {
                QStringList asRawPacket = pItem->text().split(SPLIT_PACKET);
                if (asRawPacket.size() < 3) continue;

                if (pItem->text().contains(SPLIT_PACKET SEND_PREFIX))
                    SendPacket(asRawPacket[2]);
                else if (pItem->text().contains(SPLIT_PACKET RECV_PREFIX))
                    RecvPacket(asRawPacket[2]);

                std::this_thread::sleep_for(std::chrono::milliseconds(3));
            }
        }
    }
    else if (i_pAction->text() == LW_MENU_COPY_SELECTED) {
        QStringList packetsToCopy;

        // Iterate through all items in the list
        for (int i = 0; i < this->m_oUI.lwPacketList->count(); ++i) {
            QListWidgetItem* pItem = this->m_oUI.lwPacketList->item(i);

            // Check if the item is either selected or marked
            if (pItem->isSelected() || pItem->background().color() == g_oMarkedColor) {
                QStringList asRawPacket = pItem->text().split(SPLIT_PACKET);
                if (asRawPacket.size() >= 3) {
                    packetsToCopy.append(asRawPacket[2]);
                }
            }
        }

        // Join the packets and set to clipboard
        if (!packetsToCopy.isEmpty()) {
            QString sText = packetsToCopy.join("\n");
            QApplication::clipboard()->setText(sText);
        }
    }
    else if (i_pAction->text() == LW_MENU_MARK_SELECTED) {
        QList<QListWidgetItem*> apItems = this->m_oUI.lwPacketList->selectedItems();
        if (apItems.size() > 0) {
            for (QListWidgetItem* pItem : apItems) {
                if (pItem->background().color() == g_oBackgroundColor) {
                    // Marking the item
                    pItem->setBackground(g_oMarkedColor);
                    pItem->setForeground(Qt::white);
                }
                else {
                    // Unmarking the item
                    pItem->setBackground(g_oBackgroundColor);
                    // Restore original color based on packet type
                    if (pItem->text().contains(SPLIT_PACKET RECV_PREFIX)) {
                        pItem->setForeground(Qt::cyan);
                    }
                    else if (pItem->text().contains(SPLIT_PACKET SEND_PREFIX)) {
                        pItem->setForeground(Qt::yellow);
                    }
                    else {
                        pItem->setForeground(g_oForegroundColor);
                    }
                }
            }
        }
    }
    else if (i_pAction->text() == LW_MENU_UNMARK_ALL) {
        for (int i = 0; i < this->m_oUI.lwPacketList->count(); ++i) {
            QListWidgetItem* pItem = this->m_oUI.lwPacketList->item(i);
            if (pItem->background().color() == g_oMarkedColor) {
                // Unmarking the item
                pItem->setBackground(g_oBackgroundColor);
                // Restore original color based on packet type
                if (pItem->text().contains(SPLIT_PACKET RECV_PREFIX)) {
                    pItem->setForeground(Qt::cyan);
                }
                else if (pItem->text().contains(SPLIT_PACKET SEND_PREFIX)) {
                    pItem->setForeground(Qt::yellow);
                }
                else {
                    pItem->setForeground(g_oForegroundColor);
                }
            }
        }
    }
}

QString packetPrefix(const EPacketType i_eType) {
    switch (i_eType) {
    case EPacketType::PTReceive:
        return QString::fromUtf8(RECV_PREFIX);
    case EPacketType::PTSend:
        return QString::fromUtf8(SEND_PREFIX);
    default:
        return QString::fromUtf8(UNKNOWN_PREFIX);
    }
}

void CPacketUI::onAddPacket(const QString& i_sPacket, int i_iPacketType) {
#ifdef ACTIVATE_FEATURE_TCP_SERVER
    emit g_pTcpServer->broadcastPacket(i_sPacket, i_iPacketType);
#endif
    if (m_oDamageCounterUI) {
        m_oDamageCounterUI->processPacket(i_sPacket, i_iPacketType == EPacketType::PTReceive);
    }
    if ((i_iPacketType == EPacketType::PTReceive && (!this->m_oUI.cbLogReceivePackets->isChecked() || this->m_oRecvFilter.isFiltered(i_sPacket))) ||
        (i_iPacketType == EPacketType::PTSend && (!this->m_oUI.cbLogSendPackets->isChecked() || this->m_oSendFilter.isFiltered(i_sPacket))))
        return;
    QListWidgetItem* pItem = new QListWidgetItem(QString::fromUtf8(START_SPLIT_PACKET) + QTime::currentTime().toString("hh:mm:ss").toUtf8() + QString::fromUtf8(SPLIT_PACKET) + packetPrefix(static_cast<EPacketType>(i_iPacketType)) + i_sPacket);
    pItem->setToolTip(i_sPacket);
    pItem->setBackground(g_oBackgroundColor);

    // Set text color based on packet type
    if (i_iPacketType == EPacketType::PTReceive) {
        pItem->setForeground(Qt::cyan);  // Set text color to cyan for received packets
    }
    else if (i_iPacketType == EPacketType::PTSend) {
        pItem->setForeground(Qt::yellow);  // Set text color to yellow for sent packets
    }

    this->m_oUI.lwPacketList->addItem(pItem);

    if (this->m_oUI.cbAutoScroll->isChecked())
        this->m_oUI.lwPacketList->scrollToBottom();
}

void CPacketUI::setupScrollbarStyles() {
    // Access the vertical scrollbar of the QListWidget
    QScrollBar* vScrollBar = this->m_oUI.lwPacketList->verticalScrollBar();

    // Apply stylesheet to the scrollbar
    vScrollBar->setStyleSheet(
        "QScrollBar:vertical {"
        "   border: none;"
        "   background: #2E2E2E;"
        "   width: 15px;"
        "   margin: 15px 0 15px 0;" // Add top and bottom margins to prevent overlap
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #555;"
        "   min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "   background: #666;"
        "}"
        "QScrollBar::add-line:vertical {"
        "   border: none;"
        "   background: #444;"
        "   height: 15px;"
        "   subcontrol-position: bottom;"
        "   subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:vertical {"
        "   border: none;"
        "   background: #444;"
        "   height: 15px;"
        "   subcontrol-position: top;"
        "   subcontrol-origin: margin;"
        "}"
        "QScrollBar::add-line:vertical:hover, QScrollBar::sub-line:vertical:hover {"
        "   background: #555;"
        "}"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
        "   border: none;"
        "   width: 3px;"
        "   height: 3px;"
        "   background: #777;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "   background: none;"
        "}"
    );

    // Set the scrollbar policy to show only when needed
    this->m_oUI.lwPacketList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}