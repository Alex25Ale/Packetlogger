#pragma once

#include <QWidget>
#include <QMap>
#include <QSet>
#include <QVector>
#include <QDateTime>
#include "ui_DamageCounterUI.h"
#include <cstdint>
#include <QColor>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include "WhitelistSettingsUI.h"
#include <QListWidget>
#include <QLineEdit>

struct GoldItem {
    int entityId;
    int64_t value;  // Changed to int64_t
};

struct DamageRecord {
    QString characterName;
    QString level;
    int hits = 0;
    int misses = 0;
    int crits = 0;
    int64_t bossDamage = 0;  // Changed to int64_t
    int64_t totalDamage = 0; // Changed to int64_t
    int64_t maxHit = 0;      // Changed to int64_t
    double averageDamage = 0.0;
    int64_t gold = 0;        // Changed to int64_t
    int deaths = 0;
    int bossHits = 0;
};

struct LandOfLifeRecord {
    QString characterName;
    QMap<int, double> monsterDamage;  // monster ID -> damage percentage
    QMap<int, int64_t> monsterTotalDamage;  // New field
    QMap<int, QDateTime> lastDamageTime;  // monster ID -> last damage time
    QMap<int, int64_t> monsterMaxHp;  // New map to store max HP for each monster

};

struct InstantCombatRecord {
    QString characterName;
    QString level;
    int64_t damageDealt = 0;
    int currentRound = 1;  // Add this line
    // Other fields will be calculated in updateInstantCombatTable()
};

class InstantCombatColorDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

class CDamageCounterUI : public QWidget
{
    Q_OBJECT

public:
    explicit CDamageCounterUI(QWidget* parent = nullptr);
    ~CDamageCounterUI();

    void processPacket(const QString& packet, bool isReceived);
    static const QColor HIGH_DAMAGE_COLOR;

public slots:
    void onDamageRecordsUpdated();

private slots:
    void onResetCurrentRaidClicked();
    void onResetAllRaidsClicked();
    void onExportCurrentRaidClicked();
    void onExportAllRaidsClicked();
    void onColumnResized(int logicalIndex, int oldSize, int newSize);
    void onTabChanged(int index);
    void onHeaderClicked(int logicalIndex);
    void onWhitelistSettingsClicked();
    void onActivateWhitelistClicked();
    void onWhitelistChanged(const QStringList& newWhitelist);

private:
    Ui::CDamageCounterUI* m_oUI;
    QMap<QString, DamageRecord> currentRaidRecords;
    QMap<QString, DamageRecord> allRaidsRecords;
    QMap<int, GoldItem> goldItems;
    QSet<QString> bosses;
    QVector<int> columnWidths;
    QTableWidget* m_activeTable;
    bool m_isRaidActive;
    bool m_isUpdatingEnabled;
    int getScrollBarWidth(QTableWidget* table);

    QMap<QString, LandOfLifeRecord> landOfLifeRecords;
    QString lolCharacterName;
    QString lolCharacterId;
    bool isLandOfLifeActive;
    QSet<int> validLandOfLifeMaps;
    QMap<int, QString> monsterTypeNames;
    QMap<int, int> monsterIdToType;
    class ColorDelegate : public QStyledItemDelegate {
    public:
        void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    };

    QMap<QString, InstantCombatRecord> instantCombatRecords;
    QString icCharacterName;
    QString icCharacterId;
    QString icLevel; // Store the current character's level
    QSet<int> validInstantCombatMaps;
    bool isInstantCombatActive;
    int64_t calculateRequiredDamage(int mainLevel, int round);
    InstantCombatColorDelegate* m_instantCombatColorDelegate;

    void adjustTableSizes();
    void exportTableToCSV(QTableWidget* table, const QString& defaultFilename);
    void setupScrollbarStyles();
    void resizeColumnsToContents();
    void resizeColumnsToContents(QTableWidget* table);
    void parseRdlstPacket(const QString& packet);
    void parseSuPacket(const QString& packet);
    void parseRbossPacket(const QString& packet);
    void parseThrowPacket(const QString& packet);
    void parseGetPacket(const QString& packet);
    void parseDeathPacket(const QString& packet);
    void updateTable(QTableWidget* table, const QMap<QString, DamageRecord>& records);
    void setupTable(QTableWidget* table);
    void resetCurrentRaidData();
    void handleRaidStart(const QString& packet);
    void handleRaidEnd(const QString& packet);
    void applySorting(QTableWidget* table);
    void updateSortIndicator(QTableWidget* table);
    void parseCInfoPacket(const QString& packet);
    void handleCMapPacket(const QString& packet);
    void parseInPacket(const QString& packet);
    void parseIn3Packet(const QString& packet);
    void updateLandOfLifeTable();
    void cleanupLandOfLifeMonsters();
    void initializeMonsterTypeNames();
    void resizeColumnsToContentsLandOfLife(QTableWidget* table);
    void updateInstantCombatTable();
    void parseLevPacket(const QString& packet);
    void parseMsgiPacket(const QString& packet);

    WhitelistSettingsUI* m_whitelistSettings;
    bool m_isWhitelistActive;
    QStringList m_whitelist;
    void updateWhitelistButtonText();
    bool isCharacterWhitelisted(const QString& characterName);
    void applyWhitelist();
    void loadWhitelist();
    void saveWhitelist();

    QTimer* m_updateTimer;
    bool m_updatePending;
    void updateAllTables();

    struct SortInfo {
        int column = -1;
        Qt::SortOrder order = Qt::AscendingOrder;
    };
    SortInfo m_currentRaidSort;
    SortInfo m_allRaidsSort;
    SortInfo m_instantCombatSort;


    void setupCustomHeader(QTableWidget* table);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

};

class NumericTableWidgetItem : public QTableWidgetItem
{
public:
    NumericTableWidgetItem(const QString& text) : QTableWidgetItem(text) {}

    bool operator <(const QTableWidgetItem& other) const override
    {
        return text().remove(' ').toLongLong() < other.text().remove(' ').toLongLong();
    }
};