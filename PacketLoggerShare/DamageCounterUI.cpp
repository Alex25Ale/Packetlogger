#include "DamageCounterUI.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <Windows.h>
#include <algorithm>
#include <QTimer>
#include <cmath>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>
#include <QSettings>
#include <QScrollBar>


const QColor CDamageCounterUI::HIGH_DAMAGE_COLOR = QColor(76, 175, 80, 200);  // Material Design Green 500 with alpha

#define DEBUG_PRINT(msg) OutputDebugStringA(msg)

CDamageCounterUI::CDamageCounterUI(QWidget* parent)
    : QWidget(parent), m_oUI(new Ui::CDamageCounterUI), m_activeTable(nullptr), m_isRaidActive(false), m_isUpdatingEnabled(false), isLandOfLifeActive(false), isInstantCombatActive(false), m_instantCombatColorDelegate(new InstantCombatColorDelegate()), m_isWhitelistActive(false)
{
    m_oUI->setupUi(this);
    this->installEventFilter(this);

    // Set up the stylesheet to match PacketUI with improved readability
    QString styleSheet = R"(
    QWidget {
        background-color: #1E1E1E;
        color: white;
    }
    QTableWidget {
        background-color: #2E2E2E;
        border: 1px solid #3E3E3E;
        gridline-color: #3E3E3E;
    }
    QTableWidget::item {
        border: 1px solid #3E3E3E;
    }
    QTableWidget::item:selected {
        background-color: #4E4E4E;
    }
    QHeaderView::section {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3E3E3E, stop:1 #2E2E2E);
        color: white;
        border: 1px solid #3E3E3E;
        padding: 4px;
    }
    QPushButton {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3E3E3E, stop:1 #2E2E2E);
        color: white;
        border: 1px solid #3E3E3E;
        border-radius: 2px;
        padding: 5px;
    }
    QPushButton:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4E4E4E, stop:1 #3E3E3E);
    }
    QPushButton:pressed {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2E2E2E, stop:1 #3E3E3E);
    }
    QTabWidget::pane {
        border: 1px solid #3E3E3E;
        top: -1px;
    }
    QTabBar::tab {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3E3E3E, stop:1 #2E2E2E);
        color: white;
        border: 1px solid #3E3E3E;
        border-bottom-color: #3E3E3E;
        border-top-left-radius: 4px;
        border-top-right-radius: 4px;
        padding: 5px;
    }
    QTabBar::tab:selected, QTabBar::tab:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4E4E4E, stop:1 #3E3E3E);
    }
    QScrollBar:vertical, QScrollBar:horizontal {
        border: none;
        background: #2E2E2E;
        width: 15px;
        height: 15px;
        margin: 0px;
    }

    QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
        background: #555;
        min-height: 20px;
        min-width: 20px;
    }

    QScrollBar::handle:vertical:hover, QScrollBar::handle:horizontal:hover {
        background: #666;
    }

    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
    QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
        border: none;
        background: none;
        height: 0px;
        width: 0px;
    }

    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical,
    QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
        background: #2E2E2E;
    }
    QCheckBox {
        color: white;
    }
    )";

    this->setStyleSheet(styleSheet);

    setupTable(m_oUI->currentRaidTable);
    setupTable(m_oUI->allRaidsTable);
    setupTable(m_oUI->landOfLifeTable);
    setupTable(m_oUI->instantCombatTable);
    m_oUI->instantCombatTable->setItemDelegate(m_instantCombatColorDelegate);

    m_activeTable = m_oUI->currentRaidTable;


    // Initialize column widths
    columnWidths.resize(m_oUI->currentRaidTable->columnCount());
    for (int i = 0; i < m_oUI->currentRaidTable->columnCount(); ++i) {
        columnWidths[i] = m_oUI->currentRaidTable->columnWidth(i);
    }

    // Connect tab change signal
    connect(m_oUI->tabWidget, &QTabWidget::currentChanged, this, &CDamageCounterUI::onTabChanged);
    connect(m_oUI->resetCurrentRaidButton, &QPushButton::clicked, this, &CDamageCounterUI::onResetCurrentRaidClicked);
    connect(m_oUI->resetAllRaidsButton, &QPushButton::clicked, this, &CDamageCounterUI::onResetAllRaidsClicked);
    connect(m_oUI->exportCurrentRaidButton, &QPushButton::clicked, this, &CDamageCounterUI::onExportCurrentRaidClicked);
    connect(m_oUI->exportAllRaidsButton, &QPushButton::clicked, this, &CDamageCounterUI::onExportAllRaidsClicked);
    connect(m_oUI->whitelistToggleButton, &QPushButton::clicked, this, &CDamageCounterUI::onActivateWhitelistClicked);
    connect(m_oUI->whitelistSettingsButton, &QPushButton::clicked, this, &CDamageCounterUI::onWhitelistSettingsClicked);

    resizeColumnsToContents();

    validLandOfLifeMaps = { 2750, 2751, 2758 };
    validInstantCombatMaps = { 2004 };  // Add this line



    initializeMonsterTypeNames();

    QTimer* cleanupTimer = new QTimer(this);
    connect(cleanupTimer, &QTimer::timeout, this, &CDamageCounterUI::cleanupLandOfLifeMonsters);
    cleanupTimer->start(5000);  // Run every 5 seconds


    m_whitelist = WhitelistSettingsUI::loadWhitelist();
    setupScrollbarStyles();  // Add this line

    m_updateTimer = new QTimer(this);
    m_updateTimer->setSingleShot(true);
    m_updateTimer->setInterval(200); // 200ms delay
    connect(m_updateTimer, &QTimer::timeout, this, &CDamageCounterUI::updateAllTables);
}

void CDamageCounterUI::updateAllTables()
{
    m_updatePending = false;
    updateTable(m_oUI->currentRaidTable, currentRaidRecords);
    updateTable(m_oUI->allRaidsTable, allRaidsRecords);
    updateLandOfLifeTable();
    updateInstantCombatTable();
}

void CDamageCounterUI::setupScrollbarStyles()
{
    QString scrollbarStyleSheet = R"(
        QScrollBar:vertical, QScrollBar:horizontal {
            border: none;
            background: #2E2E2E;
            margin: 0px;
        }
        QScrollBar:vertical {
            width: 15px;
        }
        QScrollBar:horizontal {
            height: 15px;
        }
        QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
            background: #555;
        }
        QScrollBar::handle:vertical {
            min-height: 20px;
        }
        QScrollBar::handle:horizontal {
            min-width: 20px;
        }
        QScrollBar::handle:vertical:hover, QScrollBar::handle:horizontal:hover {
            background: #666;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            border: none;
            background: none;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical,
        QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
            background: none;
        }
    )";

    // Apply the stylesheet to the main widget (this will cascade to child widgets)
    this->setStyleSheet(this->styleSheet() + scrollbarStyleSheet);

    // Explicitly set the stylesheet for each table
    m_oUI->currentRaidTable->setStyleSheet(m_oUI->currentRaidTable->styleSheet() + scrollbarStyleSheet);
    m_oUI->allRaidsTable->setStyleSheet(m_oUI->allRaidsTable->styleSheet() + scrollbarStyleSheet);
    m_oUI->landOfLifeTable->setStyleSheet(m_oUI->landOfLifeTable->styleSheet() + scrollbarStyleSheet);
    m_oUI->instantCombatTable->setStyleSheet(m_oUI->instantCombatTable->styleSheet() + scrollbarStyleSheet);


    // Set the scrollbar policy to show only when needed
    m_oUI->currentRaidTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_oUI->currentRaidTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_oUI->allRaidsTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_oUI->allRaidsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_oUI->landOfLifeTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_oUI->landOfLifeTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_oUI->instantCombatTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_oUI->instantCombatTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void CDamageCounterUI::setupTable(QTableWidget* table)
{
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setFocusPolicy(Qt::NoFocus);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    table->horizontalHeader()->setStretchLastSection(false);
    table->verticalHeader()->setVisible(false);
    table->setWordWrap(false);
    table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    setupCustomHeader(table);

    // Remove the default sorting
    // table->setSortingEnabled(true);

    // Remove the connection to onHeaderClicked as we're using custom header now
    // connect(table->horizontalHeader(), &QHeaderView::sectionClicked, this, &CDamageCounterUI::onHeaderClicked);
}

void CDamageCounterUI::setupCustomHeader(QTableWidget* table)
{
    QHeaderView* header = table->horizontalHeader();
    header->setSectionsClickable(true);
    header->setHighlightSections(false);
    header->setStretchLastSection(true);
    header->setSortIndicatorShown(false); // Hide the default sort indicator

    // Connect the sectionClicked signal to our custom slot
    connect(header, &QHeaderView::sectionClicked, this, &CDamageCounterUI::onHeaderClicked);
}

void CDamageCounterUI::onHeaderClicked(int logicalIndex)
{
    QTableWidget* table = qobject_cast<QTableWidget*>(sender()->parent());
    if (!table) return;

    SortInfo* currentSort;
    if (table == m_oUI->currentRaidTable) {
        currentSort = &m_currentRaidSort;
    }
    else if (table == m_oUI->allRaidsTable) {
        currentSort = &m_allRaidsSort;
    }
    else if (table == m_oUI->instantCombatTable) {
        currentSort = &m_instantCombatSort;
    }
    else {
        return;
    }

    if (currentSort->column == logicalIndex) {
        currentSort->order = (currentSort->order == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    }
    else {
        currentSort->column = logicalIndex;
        currentSort->order = Qt::AscendingOrder;
    }

    table->sortItems(currentSort->column, currentSort->order);
    updateSortIndicator(table);
}

void CDamageCounterUI::applySorting(QTableWidget* table)
{
    SortInfo* currentSort;
    if (table == m_oUI->currentRaidTable) {
        currentSort = &m_currentRaidSort;
    }
    else if (table == m_oUI->allRaidsTable) {
        currentSort = &m_allRaidsSort;
    }
    else if (table == m_oUI->instantCombatTable) {
        currentSort = &m_instantCombatSort;
    }
    else {
        return;
    }

    if (currentSort->column != -1) {
        table->sortItems(currentSort->column, currentSort->order);
        updateSortIndicator(table);
    }
}

void CDamageCounterUI::updateSortIndicator(QTableWidget* table)
{
    SortInfo* currentSort;
    if (table == m_oUI->currentRaidTable) {
        currentSort = &m_currentRaidSort;
    }
    else if (table == m_oUI->allRaidsTable) {
        currentSort = &m_allRaidsSort;
    }
    else if (table == m_oUI->instantCombatTable) {
        currentSort = &m_instantCombatSort;
    }
    else {
        return;
    }

    QHeaderView* header = table->horizontalHeader();
    for (int i = 0; i < header->count(); ++i) {
        QTableWidgetItem* item = table->horizontalHeaderItem(i);
        QString text = item->text();

        // Remove any existing arrow and trailing spaces
        text = text.remove(QChar(0x25B2)).remove(QChar(0x25BC)).trimmed();

        if (i == currentSort->column) {
            // Add the appropriate arrow with exactly one space
            text += QString(" %1").arg(currentSort->order == Qt::AscendingOrder ?
                QChar(0x25B2) :  // Up arrow
                QChar(0x25BC));  // Down arrow
        }

        item->setText(text);
    }

    // Hide the default sort indicator
    header->setSortIndicatorShown(false);
}

void CDamageCounterUI::onResetCurrentRaidClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Reset Current Raid", "Are you sure you want to reset the current raid data?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        currentRaidRecords.clear();
        updateTable(m_oUI->currentRaidTable, currentRaidRecords);
        QMessageBox::information(this, "Reset", "Current raid data has been reset.");
    }
}

void CDamageCounterUI::onResetAllRaidsClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Reset All Raids", "Are you sure you want to reset all raids data?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        allRaidsRecords.clear();
        updateTable(m_oUI->allRaidsTable, allRaidsRecords);
        QMessageBox::information(this, "Reset", "All raids data has been reset.");
    }
}
void CDamageCounterUI::onExportCurrentRaidClicked()
{
    exportTableToCSV(m_oUI->currentRaidTable, "current_raid_export.csv");
}

void CDamageCounterUI::onExportAllRaidsClicked()
{
    exportTableToCSV(m_oUI->allRaidsTable, "all_raids_export.csv");
}

void CDamageCounterUI::exportTableToCSV(QTableWidget* table, const QString& defaultFilename)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export CSV"),
        defaultFilename,
        tr("CSV Files (*.csv)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file for writing."));
        return;
    }

    QTextStream out(&file);

    // Write headers
    for (int column = 0; column < table->columnCount(); ++column)
    {
        out << table->horizontalHeaderItem(column)->text();
        if (column < table->columnCount() - 1)
            out << ",";
    }
    out << "\n";

    // Write data
    for (int row = 0; row < table->rowCount(); ++row)
    {
        for (int column = 0; column < table->columnCount(); ++column)
        {
            QTableWidgetItem* item = table->item(row, column);
            if (item)
                out << item->text();
            if (column < table->columnCount() - 1)
                out << ",";
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, tr("Export Successful"), tr("Table data has been exported to ") + fileName);
}

void CDamageCounterUI::resetCurrentRaidData()
{
    currentRaidRecords.clear();
    updateTable(m_oUI->currentRaidTable, currentRaidRecords);
}

void CDamageCounterUI::handleRaidStart(const QString& packet)
{
    if (packet.startsWith("raid 1 0") || packet.startsWith("raidf 1 0")) {
        m_isRaidActive = true;
        m_isUpdatingEnabled = true;
        resetCurrentRaidData();
        qDebug() << "New raid started. Current raid data reset. Waiting for phase 5 to enable tracking.";
    }
}

void CDamageCounterUI::handleRaidEnd(const QString& packet)
{
    if (packet.startsWith("raid 2 -1") || packet.startsWith("raidf 2 -1") || packet.startsWith("clist_start 0")) {
        m_isRaidActive = false;
        m_isUpdatingEnabled = false;
        qDebug() << "Raid ended. Damage tracking disabled.";
    }
}

void CDamageCounterUI::onTabChanged(int index)
{
    switch (index) {
    case 0: // Current Raid
        m_activeTable = m_oUI->currentRaidTable;
        resizeColumnsToContents(m_activeTable);
        updateSortIndicator(m_activeTable);
        break;
    case 1: // All Raids
        m_activeTable = m_oUI->allRaidsTable;
        resizeColumnsToContents(m_activeTable);
        updateSortIndicator(m_activeTable);
        break;
    case 2: // Land of Life
        m_activeTable = m_oUI->landOfLifeTable;
        resizeColumnsToContentsLandOfLife(m_activeTable);
        // Land of Life doesn't use sorting, so we don't call updateSortIndicator
        break;
    case 3: // Instant Combat
        m_activeTable = m_oUI->instantCombatTable;
        resizeColumnsToContents(m_activeTable);
        updateSortIndicator(m_activeTable);
        break;
    default:
        qDebug() << "Unknown tab index:" << index;
        break;
    }
}


void CDamageCounterUI::onColumnResized(int logicalIndex, int oldSize, int newSize)
{
    columnWidths[logicalIndex] = newSize;
}

CDamageCounterUI::~CDamageCounterUI()
{
    delete m_instantCombatColorDelegate;
    delete m_oUI;
}

void CDamageCounterUI::processPacket(const QString& packet, bool isReceived)
{
    if (isReceived) {
        // Always parse c_info packets
        if (packet.startsWith("c_info")) {
            parseCInfoPacket(packet);
        }
        // Always parse lev packets
        else if (packet.startsWith("lev")) {
            parseLevPacket(packet);
        }
        // Always parse c_map packets to handle Land of Life activation/deactivation
        else if (packet.startsWith("c_map")) {
            handleCMapPacket(packet);
        }
        // Handle raid start/end
        else if (packet.startsWith("raid") || packet.startsWith("raidf")) {
            handleRaidStart(packet);
            handleRaidEnd(packet);
        }
        else if (packet.startsWith("clist_start")) {
            handleRaidEnd(packet);
        }
        // Always process rdlst/rdlstf packets
        if (packet.startsWith("rdlst") || packet.startsWith("rdlstf")) {
            parseRdlstPacket(packet);
        }
        // Process in packets for Land of Life
        if (packet.startsWith("in ")) {
            QStringList parts = packet.split(' ');
            if (parts.size() >= 2) {
                if (parts[1] == "1") {
                    parseInPacket(packet);
                }
                else if (parts[1] == "3") {
                    parseIn3Packet(packet);
                }
            }
        }
        // Process su packets for both Land of Life and raids
        if (packet.startsWith("su 1")) {
            parseSuPacket(packet);
        }
        if (packet.startsWith("msgi 0 1287 4 40 0 0 0")) {
            parseMsgiPacket(packet);
        }
        // Process other packets if raid updating is enabled
        if (m_isUpdatingEnabled) {
            if (packet.startsWith("rboss 3")) {
                parseRbossPacket(packet);
            }
            else if (packet.startsWith("throw 1046")) {
                parseThrowPacket(packet);
            }
            else if (packet.startsWith("get 1")) {
                parseGetPacket(packet);
            }
            else if (packet.startsWith("msgi2 0 777 1")) {
                parseDeathPacket(packet);
            }
        }

        // Instead of calling updateTable or other update methods directly,
        // use the timer to schedule an update
        if (!m_updatePending) {
            m_updatePending = true;
            m_updateTimer->start();
        }
    }
}

void CDamageCounterUI::parseRbossPacket(const QString& packet)
{
    QStringList parts = packet.split(' ');
    if (parts.size() < 3) {
        qDebug() << "Rboss packet too short, ignoring";
        return;
    }
    QString bossEntityId = parts[2];
    if (!bosses.contains(bossEntityId)) {
        bosses.insert(bossEntityId);
        qDebug() << "Added new boss entity ID:" << bossEntityId;
    }
    else {
        qDebug() << "Received update for existing boss entity ID:" << bossEntityId;
    }
    qDebug() << "Current boss IDs:" << bosses;
}

void CDamageCounterUI::parseRdlstPacket(const QString& packet)
{
    QStringList parts = packet.split(' ');
    if (parts.size() < 4) {
        qDebug() << "Packet too short, ignoring";
        return;
    }

    int startIndex = packet.startsWith("rdlst ") ? 3 : 4;  // Handle both rdlst and rdlstf
    QString raidMembersData = parts.mid(startIndex).join(' ');
    QStringList raidMembers = raidMembersData.split(' ', Qt::SkipEmptyParts);
    qDebug() << "Parsing" << raidMembers.size() << "raid members";

    bool newPlayerAdded = false;

    for (const QString& memberData : raidMembers)
    {
        QStringList memberParts = memberData.split('.');
        if (memberParts.size() < 8) {
            qDebug() << "Member data too short, ignoring:" << memberData;
            continue;
        }

        QString characterName = memberParts[4];
        QString combatLevel = memberParts[0];
        QString championLevel = memberParts[7];
        QString characterId = memberParts[6];

        qDebug() << "Processing member:" << characterName
            << "ID:" << characterId
            << "Level:" << combatLevel + "+" + championLevel;

        auto updateRecord = [&](QMap<QString, DamageRecord>& records) {
            if (m_isRaidActive) {  // Only update records when raid is active
                if (!records.contains(characterId)) {
                    DamageRecord& record = records[characterId];
                    record.characterName = characterName;
                    record.level = combatLevel + "+" + championLevel;
                    qDebug() << "Added new record:" << record.characterName
                        << "Level:" << record.level;
                    newPlayerAdded = true;
                }
                else {
                    DamageRecord& record = records[characterId];
                    QString newLevel = combatLevel + "+" + championLevel;
                    if (record.level != newLevel) {
                        record.level = newLevel;
                        qDebug() << "Updated level for:" << record.characterName
                            << "New Level:" << record.level;
                        newPlayerAdded = true;  // Consider level update as a change
                    }
                }
            }
            };

        updateRecord(currentRaidRecords);
        updateRecord(allRaidsRecords);
    }

    // Always update the UI after processing rdlstf packet
    QMetaObject::invokeMethod(this, "onDamageRecordsUpdated", Qt::QueuedConnection);
    qDebug() << "UI update requested after processing rdlstf packet";
}


void CDamageCounterUI::parseSuPacket(const QString& packet)
{
    const int VALID_PACKET_SIZE_1 = 16;
    const int VALID_PACKET_SIZE_2 = 18;
    const QString MONSTER_ACTION_CODE = "3";
    const QString DEBUFF_SKILL_DAMAGE = "0";
    const QString DEBUFF_SKILL_FLAG = "5";
    const QString MISS_FLAG_1 = "1";
    const QString MISS_FLAG_2 = "4";
    const QString MISS_FLAG_3 = "7";  // New miss flag
    const QString CRIT_FLAG_1 = "3";
    const QString CRIT_FLAG_2 = "6";  // New crit flag
    const QString DEBUFF_FLAG_1 = "-1";  // New debuff flag
    const QString DEBUFF_FLAG_2 = "-2";  // New debuff flag

    QStringList parts = packet.split(' ');

    // Check for valid packet length (16 or 18 parts including 'su')
    if (parts.size() != VALID_PACKET_SIZE_1 && parts.size() != VALID_PACKET_SIZE_2) {
        qDebug() << "Invalid su packet length, ignoring:" << parts.size();
        return;
    }

    // Check if the action is done to a monster (part 3 should be '3')
    if (parts[3] != MONSTER_ACTION_CODE) {
        qDebug() << "Ignoring non-monster action packet";
        return;
    }

    // Ignore packet if parts[13] is 0 and parts[14] is 5
    if (parts[13] == DEBUFF_SKILL_DAMAGE && parts[14] == DEBUFF_SKILL_FLAG) {
        qDebug() << "Ignoring packet due to being a debuff skill with no damage";
        return;
    }

    // New rule: Ignore packet if size is 18 and part[14] is -1 or -2 (debuff flags)
    if (parts.size() == VALID_PACKET_SIZE_2 && (parts[14] == DEBUFF_FLAG_1 || parts[14] == DEBUFF_FLAG_2)) {
        qDebug() << "Ignoring packet due to being a debuff skill (flag -1 or -2)";
        return;
    }

    QString characterId = parts[2];
    QString targetEntityId = parts[4];
    int64_t damage = parts[13].toLongLong();
    QString hitType = parts[14];
    int64_t monsterMaxHp = -1;

    // Set damage to 0 if parts[14] is 1, 4, or 7 (miss)
    if (hitType == MISS_FLAG_1 || hitType == MISS_FLAG_2 || hitType == MISS_FLAG_3) {
        qDebug() << "Miss detected, setting damage to 0";
        damage = 0;
    }

    // Set damage to 0 if remaining HP is equal to max HP (old no HP consumption effect)
    if (parts.size() >= VALID_PACKET_SIZE_2 && parts[16] == parts[17]) {
        qDebug() << "No HP consumption detected, setting damage to 0";
        damage = 0;
    }

    if (parts.size() == VALID_PACKET_SIZE_2) {
        monsterMaxHp = parts[17].toLongLong();
    }

    // Ignore self-damage (character attacking itself)
    if (characterId == targetEntityId) {
        qDebug() << "Ignoring self-damage for character ID:" << characterId;
        return;
    }


    // Handle Land of Life damage
    if (isLandOfLifeActive) {
        int monsterId = targetEntityId.toInt();

        if (landOfLifeRecords.contains(characterId)) {
            auto& characterRecord = landOfLifeRecords[characterId];

            // Check if the monster was damaged before
            bool monsterDamagedBefore = characterRecord.monsterTotalDamage.contains(monsterId);

            // If it's a 16-part packet and the monster was never damaged before, ignore it
            if (parts.size() == VALID_PACKET_SIZE_1 && !monsterDamagedBefore) {
                qDebug() << "Ignoring 16-part packet for new monster. Character ID:" << characterId << "Monster ID:" << monsterId;
                return;
            }

            // If it's an 18-part packet and the monster was never damaged before, store the max HP
            if (parts.size() == VALID_PACKET_SIZE_2 && !monsterDamagedBefore) {
                characterRecord.monsterMaxHp[monsterId] = monsterMaxHp;
            }

            // Use stored max HP if available, otherwise use the one from the packet
            int64_t usedMaxHp = characterRecord.monsterMaxHp.value(monsterId, monsterMaxHp);

            // Ignore packets with invalid monster max HP
            if (usedMaxHp <= 0) {
                qDebug() << "Invalid monster max HP, ignoring:" << usedMaxHp;
                return;
            }

            // Cap the total damage at the monster's max HP
            int64_t cappedDamage = std::min<int64_t>(characterRecord.monsterTotalDamage[monsterId] + damage, usedMaxHp);
            characterRecord.monsterTotalDamage[monsterId] = cappedDamage;

            double totalDamagePercentage = (static_cast<double>(cappedDamage) / usedMaxHp) * 100.0;
            characterRecord.monsterDamage[monsterId] = totalDamagePercentage;
            characterRecord.lastDamageTime[monsterId] = QDateTime::currentDateTime();

            qDebug() << "Land of Life damage update:";
            qDebug() << "  Character ID:" << characterId;
            qDebug() << "  Monster ID:" << monsterId;
            qDebug() << "  Monster Max HP:" << usedMaxHp;
            qDebug() << "  Damage Dealt:" << damage;
            qDebug() << "  Total Damage Dealt:" << characterRecord.monsterTotalDamage[monsterId];
            qDebug() << "  Current Damage Percentage:" << QString::number(totalDamagePercentage, 'f', 2) + "%";

            updateLandOfLifeTable();
        }
        else {
            qDebug() << "Character ID not found in landOfLifeRecords:" << characterId;
        }
    }

    // Handle Instant Combat damage
    if (isInstantCombatActive) {
        if (instantCombatRecords.contains(characterId)) {
            instantCombatRecords[characterId].damageDealt += damage;

            qDebug() << "Instant Combat damage update:";
            qDebug() << "  Character ID:" << characterId;
            qDebug() << "  Damage Dealt:" << damage;
            qDebug() << "  Total Damage Dealt:" << instantCombatRecords[characterId].damageDealt;

            onDamageRecordsUpdated();
        }
        else {
            qDebug() << "Character ID not found in instantCombatRecords:" << characterId;
        }
    }

    // Handle raid damage
    if (m_isRaidActive && m_isUpdatingEnabled) {
        auto updateRecord = [&](QMap<QString, DamageRecord>& records) {
            if (records.contains(characterId)) {
                DamageRecord& record = records[characterId];
                if (parts.size() == VALID_PACKET_SIZE_2) {  // Only increment hits for 18-part packets
                    record.hits++;
                }
                if (bosses.contains(targetEntityId)) {
                    if (parts.size() == VALID_PACKET_SIZE_2) {  // Only increment bossHits for 18-part packets
                        record.bossHits++;
                    }
                    if (damage > 0) {
                        record.bossDamage += damage;
                        record.maxHit = qMax(record.maxHit, damage);
                        if (hitType == CRIT_FLAG_1 || hitType == CRIT_FLAG_2) {
                            record.crits++;
                        }
                    }
                    else {
                        record.misses++;
                    }
                }
                record.totalDamage += damage;
            }
            };

        updateRecord(currentRaidRecords);
        updateRecord(allRaidsRecords);

        QMetaObject::invokeMethod(this, "onDamageRecordsUpdated", Qt::QueuedConnection);
    }
}

void CDamageCounterUI::parseThrowPacket(const QString& packet)
{
    if (!m_isRaidActive || !m_isUpdatingEnabled) {
        qDebug() << "Damage tracking disabled. Ignoring throw packet.";
        return;
    }

    QStringList parts = packet.split(' ');
    if (parts.size() < 8 || parts[0] != "throw" || parts[1] != "1046") {
        return;
    }

    int entityId = parts[2].toInt();
    int64_t goldValue = parts[7].toLongLong();  // Changed to toLongLong()

    goldItems[entityId] = GoldItem{ entityId, goldValue };
    qDebug() << "Gold item spawned: Entity ID" << entityId << "Value:" << goldValue;
}

void CDamageCounterUI::parseGetPacket(const QString& packet)
{
    if (!m_isRaidActive || !m_isUpdatingEnabled) {
        qDebug() << "Damage tracking disabled. Ignoring get packet.";
        return;
    }

    QStringList parts = packet.split(' ');
    if (parts.size() < 5 || parts[0] != "get" || parts[1] != "1") {
        return;
    }
    QString characterId = parts[2];
    int entityId = parts[3].toInt();

    if (goldItems.contains(entityId)) {
        int64_t goldValue = goldItems[entityId].value;  // Changed to int64_t

        auto updateRecord = [&](QMap<QString, DamageRecord>& records) {
            if (records.contains(characterId)) {
                DamageRecord& record = records[characterId];
                record.gold += goldValue;
                qDebug() << "Character" << record.characterName << "looted" << goldValue << "gold. Total gold:" << record.gold;
            }
            else {
                qDebug() << "Character ID not found in damage records:" << characterId;
            }
            };

        updateRecord(currentRaidRecords);
        updateRecord(allRaidsRecords);

        goldItems.remove(entityId);
        QMetaObject::invokeMethod(this, "onDamageRecordsUpdated", Qt::QueuedConnection);
    }
    else {
        qDebug() << "Gold item not found: Entity ID" << entityId;
    }
}

void CDamageCounterUI::parseDeathPacket(const QString& packet)
{
    if (!m_isRaidActive || !m_isUpdatingEnabled) {
        qDebug() << "Damage tracking disabled. Ignoring death packet.";
        return;
    }

    QStringList parts = packet.split(' ');
    if (parts.size() < 5 || parts[0] != "msgi2" || parts[1] != "0" || parts[2] != "777" || parts[3] != "1") {
        qDebug() << "Invalid death packet format, ignoring";
        return;
    }
    QString characterName = parts.mid(4).join(' '); // Join all parts after the 4th space to get the full character name

    auto updateRecord = [&](QMap<QString, DamageRecord>& records) {
        for (auto it = records.begin(); it != records.end(); ++it) {
            if (it.value().characterName == characterName) {
                it.value().deaths++;
                qDebug() << "Updated death count for" << characterName << "to" << it.value().deaths;
                return true;
            }
        }
        return false;
        };

    bool updated = updateRecord(currentRaidRecords);
    updated |= updateRecord(allRaidsRecords);

    if (updated) {
        QMetaObject::invokeMethod(this, "onDamageRecordsUpdated", Qt::QueuedConnection);
    }
    else {
        qDebug() << "Character not found in damage records:" << characterName;
    }
}

void CDamageCounterUI::parseCInfoPacket(const QString& packet)
{
    QStringList parts = packet.split(' ');
    if (parts.size() < 7) {
        qDebug() << "c_info packet too short, ignoring";
        return;
    }

    QString characterName = parts[1];
    QString characterId = parts[6];

    // Update both LoL and IC character information
    lolCharacterName = characterName;
    lolCharacterId = characterId;
    icCharacterName = characterName;
    icCharacterId = characterId;

    qDebug() << "Parsed c_info packet: Character Name =" << characterName << ", Character ID =" << characterId;
}

void CDamageCounterUI::parseLevPacket(const QString& packet)
{
    QStringList parts = packet.split(' ');
    if (parts.size() < 11) {
        qDebug() << "lev packet too short, ignoring";
        return;
    }

    int mainLevel = parts[1].toInt();
    int championLevel = parts[10].toInt();
    QString level = QString("%1+%2").arg(mainLevel).arg(championLevel);

    // Always update the level for the current character
    icLevel = level;

    // Update the Instant Combat record if it exists
    if (instantCombatRecords.contains(icCharacterId)) {
        instantCombatRecords[icCharacterId].level = level;
        updateInstantCombatTable();
    }

    qDebug() << "Parsed lev packet: Character Name =" << icCharacterName << ", Character ID =" << icCharacterId << ", Level =" << level;
}

void CDamageCounterUI::handleCMapPacket(const QString& packet)
{
    QStringList parts = packet.split(' ');
    if (parts.size() < 3) return;
    int mapId = parts[2].toInt();
    isLandOfLifeActive = validLandOfLifeMaps.contains(mapId);
    bool wasInstantCombatActive = isInstantCombatActive;
    isInstantCombatActive = (mapId == 2004);

    if (isLandOfLifeActive) {
        // Existing Land of Life logic (unchanged)
        LandOfLifeRecord record;
        record.characterName = lolCharacterName;
        landOfLifeRecords[lolCharacterId] = record;
    }
    else {
        landOfLifeRecords.clear();
    }

    if (isInstantCombatActive != wasInstantCombatActive) {
        instantCombatRecords.clear();
        if (isInstantCombatActive) {
            // Initialize the record for the current character
            InstantCombatRecord record;
            record.characterName = icCharacterName;
            record.level = icLevel;
            record.damageDealt = 0;
            record.currentRound = 1;  // Initialize round to 1
            instantCombatRecords[icCharacterId] = record;
        }
    }

    updateLandOfLifeTable();
    updateInstantCombatTable();
    qDebug() << "Map changed to:" << mapId << "Instant Combat active:" << isInstantCombatActive;
}

void CDamageCounterUI::parseInPacket(const QString& packet)
{
    QStringList parts = packet.split(' ');
    qDebug() << "Parsing 'in' packet with" << parts.size() << "parts";

    if (parts.size() < 4 || parts[1] != "1") {
        qDebug() << "Invalid 'in' packet: too few parts or not type 1";
        return;
    }

    QString characterName = parts[2];
    QString characterId = parts[4];
    qDebug() << "Processing 'in' packet for character:" << characterName << "ID:" << characterId;

    // Handle Instant Combat
    if (isInstantCombatActive) {
        QString level;
        if (characterId == icCharacterId) {
            level = icLevel; // Use the stored level for the current character
            qDebug() << "Using stored level for current character:" << level;
        }
        else if (parts.size() >= 41) {
            QString mainLevel = parts[33];
            QString championLevel = parts[39];
            level = mainLevel + "+" + championLevel;
            qDebug() << "Extracted level from 'in' packet:" << level;
        }
        else {
            level = "Unknown";
            qDebug() << "Unable to extract level, packet too short. Parts:" << parts.size();
        }

        if (!instantCombatRecords.contains(characterId)) {
            InstantCombatRecord record;
            record.characterName = characterName;
            record.level = level;
            record.damageDealt = 0;
            instantCombatRecords[characterId] = record;
            qDebug() << "Created new Instant Combat record for" << characterName;
        }
        else {
            instantCombatRecords[characterId].characterName = characterName;
            instantCombatRecords[characterId].level = level;
            qDebug() << "Updated existing Instant Combat record for" << characterName;
        }

        updateInstantCombatTable();
    }

    // Handle Land of Life
    if (isLandOfLifeActive) {
        bool newCharacterAdded = false;
        if (!landOfLifeRecords.contains(characterId)) {
            LandOfLifeRecord record;
            record.characterName = characterName;
            landOfLifeRecords[characterId] = record;
            newCharacterAdded = true;
            qDebug() << "Added new character to Land of Life:" << characterName;
        }
        else {
            landOfLifeRecords[characterId].characterName = characterName;
            qDebug() << "Updated existing Land of Life record for" << characterName;
        }

        if (newCharacterAdded) {
            updateLandOfLifeTable();
        }
    }

    qDebug() << "Finished processing 'in' packet for character:" << characterName
        << "ID:" << characterId
        << "Level:" << (instantCombatRecords.contains(characterId) ? instantCombatRecords[characterId].level : "N/A");

    // Print the entire packet for debugging
    qDebug() << "Full 'in' packet:" << packet;
}

void CDamageCounterUI::parseIn3Packet(const QString& packet)
{
    QStringList parts = packet.split(' ');
    if (parts.size() < 5 || parts[1] != "3") return;

    int monsterId = parts[3].toInt();
    int monsterType = parts[2].toInt();

    // Store the monster type for this monster ID
    monsterIdToType[monsterId] = monsterType;
}

void CDamageCounterUI::onDamageRecordsUpdated()
{
    if (!m_updatePending) {
        m_updatePending = true;
        m_updateTimer->start();
    }
}

void CDamageCounterUI::updateTable(QTableWidget* table, const QMap<QString, DamageRecord>& records)
{
    if (!table) {
        qDebug() << "Table is null!";
        return;
    }

    // Apply the same check for both tables
    if (!m_isRaidActive) {
        qDebug() << "Raid not active. Not updating table.";
        return;
    }

    qDebug() << "Updating table with" << records.size() << "records";

    table->setSortingEnabled(false);
    table->setUpdatesEnabled(false);

    // If the number of rows has changed, reset the table
    if (table->rowCount() != records.size()) {
        table->setRowCount(records.size());
        int row = 0;
        for (auto it = records.constBegin(); it != records.constEnd(); ++it) {
            for (int col = 0; col < table->columnCount(); ++col) {
                table->setItem(row, col, new QTableWidgetItem());
            }
            row++;
        }
    }

    auto formatNumber = [](int64_t number) {
        return QLocale(QLocale::English).toString(static_cast<qlonglong>(number)).replace(",", " ");
        };

    int row = 0;
    for (auto it = records.constBegin(); it != records.constEnd(); ++it) {
        const DamageRecord& record = it.value();
        table->setItem(row, 0, new QTableWidgetItem(record.level));
        table->setItem(row, 1, new QTableWidgetItem(record.characterName));
        table->setItem(row, 2, new NumericTableWidgetItem(formatNumber(record.bossDamage)));
        double avgBossDamage = (record.bossHits - record.misses) > 0 ?
            static_cast<double>(record.bossDamage) / (record.bossHits - record.misses) : 0.0;
        table->setItem(row, 3, new NumericTableWidgetItem(formatNumber(static_cast<int>(avgBossDamage))));
        table->setItem(row, 4, new NumericTableWidgetItem(formatNumber(record.maxHit)));
        table->setItem(row, 5, new NumericTableWidgetItem(formatNumber(record.bossHits)));
        table->setItem(row, 6, new NumericTableWidgetItem(formatNumber(record.misses)));
        table->setItem(row, 7, new NumericTableWidgetItem(formatNumber(record.crits)));
        table->setItem(row, 8, new NumericTableWidgetItem(formatNumber(record.hits)));
        table->setItem(row, 9, new NumericTableWidgetItem(formatNumber(record.totalDamage)));
        double avgTotalDamage = record.hits > 0 ?
            static_cast<double>(record.totalDamage) / record.hits : 0.0;
        table->setItem(row, 10, new NumericTableWidgetItem(formatNumber(static_cast<int>(avgTotalDamage))));
        table->setItem(row, 11, new NumericTableWidgetItem(formatNumber(record.gold)));
        table->setItem(row, 12, new NumericTableWidgetItem(formatNumber(record.deaths)));
        row++;
    }

    table->setSortingEnabled(true);
    SortInfo& currentSort = (table == m_oUI->currentRaidTable) ? m_currentRaidSort : m_allRaidsSort;
    if (currentSort.column != -1) {
        table->sortItems(currentSort.column, currentSort.order);
        updateSortIndicator(table);
    }

    table->setUpdatesEnabled(true);
    table->viewport()->update();

    // Delay the resizing
    QTimer::singleShot(0, [this, table]() {
        this->resizeColumnsToContents(table);
        });
}

void CDamageCounterUI::initializeMonsterTypeNames()
{
    monsterTypeNames[3252] = "Blessed Golden Gryphon";
    monsterTypeNames[3251] = "Giant Redshroom Mage";
    monsterTypeNames[3250] = "Giant Goldshroom Swordsman";
    monsterTypeNames[3249] = "Giant Goldshroom Archer";
    monsterTypeNames[3248] = "Glacial Ghost Stag";
    monsterTypeNames[3247] = "Dark Dragon Harpy";
    monsterTypeNames[3246] = "Golden Gryphon";
    monsterTypeNames[3245] = "Red Dragon Army's Centaur Warrior";
    monsterTypeNames[3244] = "Golden Dragon Army's Centaur Archer";
    monsterTypeNames[3243] = "Redshroom Mage";
    monsterTypeNames[3242] = "Goldshroom Swordsman";
    monsterTypeNames[3216] = "Goldshroom Archer";
    monsterTypeNames[1461] = "Blessed Undead Dragon";
    monsterTypeNames[809] = "Golden Dragon";
    monsterTypeNames[1465] = "Elite Goldshroom Archer";
    monsterTypeNames[1466] = "Elite Goldshroom Swordsman";
    monsterTypeNames[1467] = "Elite Redshroom Mage";
    monsterTypeNames[1468] = "Elite Giant Goldshroom Archer";
    monsterTypeNames[1471] = "Elite Giant Goldshroom Swordsman";
    monsterTypeNames[1472] = "Elite Giant Redshroom Mage";
    monsterTypeNames[1473] = "Elite Golden Gryphon";
    monsterTypeNames[1475] = "Elite Blessed Golden Gryphon";
    monsterTypeNames[1476] = "Elite Dark Dragon Harpy";
    monsterTypeNames[1478] = "Elite Glacial Ghost Stag";
    monsterTypeNames[1479] = "Elite Golden Dragon Army's Centaur Archer";
    monsterTypeNames[1480] = "Elite Red Dragon Army's Centaur Warrior";
    monsterTypeNames[1481] = "Elite Golden Dragon";
    monsterTypeNames[1482] = "Elite Blessed Undead Dragon";
    monsterTypeNames[1569] = "Expert Goldshroom Archer";
    monsterTypeNames[1570] = "Expert Goldshroom Swordsman";
    monsterTypeNames[1571] = "Expert Blueshroom Mage";
    monsterTypeNames[1572] = "Expert Gryphon";
    monsterTypeNames[1573] = "Expert Dark Dragon Harpy";
    monsterTypeNames[1574] = "Expert Blue Dragon Army's Centaur Warrior";
    monsterTypeNames[1575] = "Expert Obsidian Dragon";
}

void CDamageCounterUI::ColorDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    bool ok;
    double value = index.data(Qt::DisplayRole).toString().remove('%').toDouble(&ok);
    if (ok && value > 11.0) {
        painter->save();
        // Fill the background
        painter->fillRect(option.rect, CDamageCounterUI::HIGH_DAMAGE_COLOR);
        // Draw text
        painter->setPen(Qt::black);
        painter->setFont(option.font);  // Use the default font
        painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());
        painter->restore();
    }
    else {
        // For non-highlighted cells, use the default painting
        QStyledItemDelegate::paint(painter, option, index);
    }
}

void InstantCombatColorDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() == 1) // Character Name column
    {
        int64_t damageDealt = index.sibling(index.row(), 2).data(Qt::UserRole).toLongLong();
        int64_t requiredDamage = index.sibling(index.row(), 4).data(Qt::UserRole).toLongLong();

        // Get the current round from the model data
        int currentRound = index.model()->data(index, Qt::UserRole + 1).toInt();

        // Only apply green color if it's not the 5th round or if required damage is not zero
        if (damageDealt >= requiredDamage && !(currentRound == 5 && requiredDamage == 0))
        {
            painter->save();
            // Fill the background
            painter->fillRect(option.rect, CDamageCounterUI::HIGH_DAMAGE_COLOR);
            // Draw text
            painter->setPen(Qt::black);
            painter->setFont(option.font);
            painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, "  " + index.data().toString());
            painter->restore();
        }
        else
        {
            // For non-highlighted cells, use the default painting
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
    else
    {
        // For all other columns, use the default painting
        QStyledItemDelegate::paint(painter, option, index);
    }
}

void CDamageCounterUI::updateLandOfLifeTable()
{
    QTableWidget* table = m_oUI->landOfLifeTable;
    QString currentStyleSheet = table->styleSheet();

    // Save the current scroll position
    int horizontalScrollValue = table->horizontalScrollBar()->value();
    int verticalScrollValue = table->verticalScrollBar()->value();

    // Use existing ColorDelegate if possible, or create a new one
    if (!table->itemDelegate() || !dynamic_cast<ColorDelegate*>(table->itemDelegate())) {
        table->setItemDelegate(new ColorDelegate());
    }

    if (landOfLifeRecords.isEmpty()) {
        table->clearContents();
        table->setRowCount(0);
        table->setColumnCount(0);
        return;
    }

    // Set up headers (character names)
    QStringList headers;
    headers << "Monster";
    for (const auto& record : landOfLifeRecords) {
        headers << record.characterName;
    }

    if (table->columnCount() != headers.size() || table->horizontalHeaderItem(0)->text() != headers[0]) {
        table->setColumnCount(headers.size());
        table->setHorizontalHeaderLabels(headers);
    }

    // Collect all unique monster IDs
    QSet<int> monsterIds;
    for (const auto& record : landOfLifeRecords) {
        const auto& keys = record.monsterDamage.keys();
        monsterIds.unite(QSet<int>(keys.begin(), keys.end()));
    }

    // Create a list of monster names and IDs, then sort it
    QList<QPair<QString, int>> sortedMonsters;
    for (int monsterId : monsterIds) {
        QString monsterName;
        if (monsterIdToType.contains(monsterId) && monsterTypeNames.contains(monsterIdToType[monsterId])) {
            monsterName = monsterTypeNames[monsterIdToType[monsterId]];
        }
        else {
            monsterName = QString::number(monsterId);
        }
        sortedMonsters.append(qMakePair(monsterName, monsterId));
    }
    std::sort(sortedMonsters.begin(), sortedMonsters.end());

    // Update table content
    table->setRowCount(sortedMonsters.size());
    for (int row = 0; row < sortedMonsters.size(); ++row) {
        const auto& monster = sortedMonsters[row];

        // Update monster name
        QTableWidgetItem* monsterItem = table->item(row, 0);
        if (!monsterItem) {
            monsterItem = new QTableWidgetItem();
            monsterItem->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, 0, monsterItem);
        }
        monsterItem->setText(monster.first);

        // Update damage values
        int col = 1;
        for (const auto& record : landOfLifeRecords) {
            QTableWidgetItem* item = table->item(row, col);
            if (!item) {
                item = new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, col, item);
            }

            if (record.monsterDamage.contains(monster.second)) {
                double damage = record.monsterDamage[monster.second];
                if (std::isfinite(damage) && damage >= 0) {
                    damage = std::min<double>(damage, 100.0);
                    item->setText(QString::number(damage, 'f', 2) + "%");
                }
                else {
                    item->setText("N/A");
                }
            }
            else {
                item->setText("0%");
            }
            col++;
        }
    }

    table->setStyleSheet(currentStyleSheet);
    table->viewport()->update();  // Force repaint

    // Delay the resizing and restore scroll position
    QTimer::singleShot(0, [this, table, horizontalScrollValue, verticalScrollValue]() {
        this->resizeColumnsToContentsLandOfLife(table);
        table->horizontalScrollBar()->setValue(horizontalScrollValue);
        table->verticalScrollBar()->setValue(verticalScrollValue);
        });
}

void CDamageCounterUI::cleanupLandOfLifeMonsters()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    bool tableUpdated = false;

    for (auto& record : landOfLifeRecords) {
        QMutableMapIterator<int, QDateTime> it(record.lastDamageTime);
        while (it.hasNext()) {
            it.next();
            if (it.value().secsTo(currentTime) > 20) {
                record.monsterDamage.remove(it.key());
                it.remove();
                tableUpdated = true;
            }
        }
    }

    if (tableUpdated) {
        updateLandOfLifeTable();
    }
}

int64_t CDamageCounterUI::calculateRequiredDamage(int mainLevel, int round)
{
    int roundFactor;

    if (mainLevel >= 80) {
        roundFactor = (round == 1) ? 100 : (round == 2) ? 300 : (round == 3) ? 600 : (round == 4) ? 1000 : 0;
    }
    else if (mainLevel >= 70) {
        roundFactor = (round == 1) ? 75 : (round == 2) ? 225 : (round == 3) ? 500 : (round == 4) ? 750 : 0;
    }
    else if (mainLevel >= 60) {
        roundFactor = (round == 1) ? 75 : (round == 2) ? 225 : (round == 3) ? 500 : (round == 4) ? 750 : 0;
    }
    else if (mainLevel >= 50) {
        roundFactor = (round == 1) ? 50 : (round == 2) ? 150 : (round == 3) ? 300 : (round == 4) ? 500 : 0;
    }
    else if (mainLevel >= 40) {
        roundFactor = (round == 1) ? 50 : (round == 2) ? 150 : (round == 3) ? 300 : (round == 4) ? 500 : 0;
    }
    else {
        roundFactor = (round == 1) ? 25 : (round == 2) ? 75 : (round == 3) ? 150 : (round == 4) ? 250 : 0;
    }

    return static_cast<int64_t>(3) * mainLevel * roundFactor;
}

void CDamageCounterUI::parseMsgiPacket(const QString& packet)
{
    if (packet == "msgi 0 1287 4 40 0 0 0" && isInstantCombatActive) {
        for (auto& record : instantCombatRecords) {
            record.currentRound++;
            record.damageDealt = 0;  // Reset damage dealt for the new round
        }
        updateInstantCombatTable();
    }
}

void CDamageCounterUI::onActivateWhitelistClicked()
{
    m_isWhitelistActive = !m_isWhitelistActive;
    updateWhitelistButtonText();
    if (m_isWhitelistActive) {
        QMessageBox::information(this, "Whitelist Activated", "Whitelist is now active for Instant Combat. Only whitelisted characters will be shown in the Instant Combat table.");
    }
    else {
        QMessageBox::information(this, "Whitelist Deactivated", "Whitelist is now inactive for Instant Combat. All characters will be shown in the Instant Combat table.");
    }
    // Update only the Instant Combat table
    updateInstantCombatTable();
}

void CDamageCounterUI::onWhitelistSettingsClicked()
{
    WhitelistSettingsUI* whitelistSettings = new WhitelistSettingsUI(this);
    whitelistSettings->setWhitelist(m_whitelist);
    connect(whitelistSettings, &WhitelistSettingsUI::whitelistChanged, this, &CDamageCounterUI::onWhitelistChanged);
    whitelistSettings->show();
}

void CDamageCounterUI::updateWhitelistButtonText()
{
    if (m_isWhitelistActive) {
        m_oUI->whitelistToggleButton->setText("Deactivate Whitelist");
    }
    else {
        m_oUI->whitelistToggleButton->setText("Activate Whitelist");
    }
}

bool CDamageCounterUI::isCharacterWhitelisted(const QString& characterName)
{
    return !m_isWhitelistActive || m_whitelist.contains(characterName);
}

void CDamageCounterUI::onWhitelistChanged(const QStringList& newWhitelist)
{
    m_whitelist = newWhitelist;
    WhitelistSettingsUI::saveWhitelist(m_whitelist);
    updateInstantCombatTable();
}

void CDamageCounterUI::loadWhitelist()
{
    QString configPath = QCoreApplication::applicationDirPath() + "/Config";
    QString filePath = configPath + "/Whitelist.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    m_whitelist = settings.value("Whitelist").toStringList();
}

void CDamageCounterUI::saveWhitelist()
{
    QString configPath = QCoreApplication::applicationDirPath() + "/Config";
    QDir().mkpath(configPath);  // Ensure the Config directory exists
    QString filePath = configPath + "/Whitelist.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setValue("Whitelist", m_whitelist);
}
void CDamageCounterUI::updateInstantCombatTable()
{
    if (!m_updatePending) {
        m_updatePending = true;
        m_updateTimer->start();
        return;
    }

    QTableWidget* table = m_oUI->instantCombatTable;
    table->setSortingEnabled(false);
    table->setUpdatesEnabled(false);

    // Store current column widths
    QVector<int> columnWidths;
    for (int i = 0; i < table->columnCount(); ++i) {
        columnWidths.append(table->columnWidth(i));
    }

    // Clear the table
    table->setRowCount(0);

    auto formatNumber = [](int64_t number) {
        return QLocale(QLocale::English).toString(static_cast<qlonglong>(number)).replace(",", " ");
        };

    for (const auto& record : instantCombatRecords) {
        // Apply whitelist filter
        if (m_isWhitelistActive && !m_whitelist.contains(record.characterName)) {
            continue;
        }

        int row = table->rowCount();
        table->insertRow(row);

        QStringList levelParts = record.level.split('+');
        int mainLevel = levelParts[0].toInt();

        // Column 0: Level
        table->setItem(row, 0, new QTableWidgetItem(record.level));

        // Column 1: Character Name
        QTableWidgetItem* characterNameItem = new QTableWidgetItem(record.characterName);
        characterNameItem->setData(Qt::UserRole + 1, record.currentRound);  // Store current round
        table->setItem(row, 1, characterNameItem);

        // Column 2: Damage Dealt
        QTableWidgetItem* damageDealtItem = new NumericTableWidgetItem(formatNumber(record.damageDealt));
        damageDealtItem->setData(Qt::UserRole, record.damageDealt);
        table->setItem(row, 2, damageDealtItem);

        // Column 3: Damage Remaining
        int64_t requiredDamage = calculateRequiredDamage(mainLevel, record.currentRound);
        int64_t damageRemaining = std::max<int64_t>(0, requiredDamage - record.damageDealt);
        QTableWidgetItem* damageRemainingItem = new NumericTableWidgetItem(formatNumber(damageRemaining));
        damageRemainingItem->setData(Qt::UserRole, damageRemaining);
        table->setItem(row, 3, damageRemainingItem);

        // Column 4: Damage Required This Round
        QTableWidgetItem* requiredDamageItem = new NumericTableWidgetItem(formatNumber(requiredDamage));
        requiredDamageItem->setData(Qt::UserRole, requiredDamage);
        table->setItem(row, 4, requiredDamageItem);
    }

    // Restore column widths
    for (int i = 0; i < table->columnCount() && i < columnWidths.size(); ++i) {
        table->setColumnWidth(i, columnWidths[i]);
    }

    table->setSortingEnabled(true);
    if (m_instantCombatSort.column != -1) {
        table->sortItems(m_instantCombatSort.column, m_instantCombatSort.order);
        updateSortIndicator(table);
    }

    table->setUpdatesEnabled(true);
    table->viewport()->update();

    // Delay the resizing
    QTimer::singleShot(0, [this, table]() {
        this->resizeColumnsToContents(table);
        });

    m_updatePending = false;
}

void CDamageCounterUI::resizeColumnsToContents()
{
    resizeColumnsToContents(m_oUI->currentRaidTable);
    resizeColumnsToContents(m_oUI->allRaidsTable);
    resizeColumnsToContentsLandOfLife(m_oUI->landOfLifeTable);
    resizeColumnsToContents(m_oUI->instantCombatTable);

}

void CDamageCounterUI::resizeColumnsToContents(QTableWidget* table)
{
    if (!table) return;

    int totalWidth = table->viewport()->width();
    int columnCount = table->columnCount();

    // First, resize columns to fit their content
    table->resizeColumnsToContents();

    // Calculate the total width of all columns
    int contentWidth = 0;
    for (int i = 0; i < columnCount; ++i) {
        contentWidth += table->columnWidth(i);
    }

    // If content width is less than the viewport width, distribute the extra space
    if (contentWidth < totalWidth) {
        int extraSpace = totalWidth - contentWidth;
        int extraPerColumn = extraSpace / columnCount;
        int remainder = extraSpace % columnCount;

        for (int i = 0; i < columnCount; ++i) {
            int newWidth = table->columnWidth(i) + extraPerColumn;
            if (i < remainder) newWidth++; // Distribute the remainder
            table->setColumnWidth(i, newWidth);
        }
    }
    // If content width is greater than the viewport width, scale down the columns
    else {
        double scaleFactor = static_cast<double>(totalWidth) / contentWidth;
        int allocatedWidth = 0;

        for (int i = 0; i < columnCount - 1; ++i) {
            int newWidth = static_cast<int>(table->columnWidth(i) * scaleFactor);
            table->setColumnWidth(i, newWidth);
            allocatedWidth += newWidth;
        }

        // Set the last column width to fill the remaining space
        int lastColumnWidth = totalWidth - allocatedWidth;
        table->setColumnWidth(columnCount - 1, lastColumnWidth);
    }

    // Ensure the horizontal header is updated
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setStretchLastSection(false);
}

void CDamageCounterUI::resizeColumnsToContentsLandOfLife(QTableWidget* table)
{
    if (!table || table->columnCount() < 2) return;

    QSignalBlocker blocker(table);

    // Set fixed width for monster column
    const int monsterFixedWidth = 350; // Example fixed width, adjust as needed
    table->setColumnWidth(0, monsterFixedWidth);

    int totalWidth = table->viewport()->width();
    int columnCount = table->columnCount();

    // Distribute the remaining width to player columns
    int remainingWidth = totalWidth - monsterFixedWidth;
    int playerColumnWidth = remainingWidth / (columnCount - 1);

    for (int i = 1; i < columnCount - 1; ++i) {
        table->setColumnWidth(i, playerColumnWidth);
    }

    // Set the last column width to fill the remaining space
    int lastColumnWidth = totalWidth - monsterFixedWidth - playerColumnWidth * (columnCount - 2);
    table->setColumnWidth(columnCount - 1, lastColumnWidth);

    // Ensure text elision for the monster column
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);

    // Set all other columns to Fixed
    for (int i = 1; i < table->columnCount(); ++i) {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }

    // Update the layout to reflect changes
    table->horizontalHeader()->updateGeometry();
    table->viewport()->updateGeometry();
}


void CDamageCounterUI::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    QTimer::singleShot(0, [this]() {
        this->resizeColumnsToContents(m_oUI->currentRaidTable);
        this->resizeColumnsToContents(m_oUI->allRaidsTable);
        this->resizeColumnsToContents(m_oUI->instantCombatTable);
        this->resizeColumnsToContentsLandOfLife(m_oUI->landOfLifeTable);
        });
}

void CDamageCounterUI::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    QTimer::singleShot(0, [this]() {
        this->resizeColumnsToContents(m_oUI->currentRaidTable);
        this->resizeColumnsToContents(m_oUI->allRaidsTable);
        this->resizeColumnsToContents(m_oUI->instantCombatTable);
        this->resizeColumnsToContentsLandOfLife(m_oUI->landOfLifeTable);
        });
}

int CDamageCounterUI::getScrollBarWidth(QTableWidget* table)
{
    int scrollBarWidth = 0;
    if (table->verticalScrollBar() && table->verticalScrollBar()->isVisible()) {
        scrollBarWidth = table->verticalScrollBar()->width();
    }
    return scrollBarWidth;
}

bool CDamageCounterUI::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Resize) {
        QTimer::singleShot(0, this, &CDamageCounterUI::adjustTableSizes);
        return false;
    }
    return QObject::eventFilter(obj, event);
}

void CDamageCounterUI::adjustTableSizes()
{
    resizeColumnsToContents(m_oUI->currentRaidTable);
    resizeColumnsToContents(m_oUI->allRaidsTable);
    resizeColumnsToContents(m_oUI->instantCombatTable);
    resizeColumnsToContentsLandOfLife(m_oUI->landOfLifeTable);
}