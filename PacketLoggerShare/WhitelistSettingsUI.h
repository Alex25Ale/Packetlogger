#pragma once

#include <QDialog>
#include <QStringList>

namespace Ui {
    class WhitelistSettingsUI;
}

class WhitelistSettingsUI : public QDialog
{
    Q_OBJECT

public:
    explicit WhitelistSettingsUI(QWidget* parent = nullptr);
    ~WhitelistSettingsUI();

    QStringList getWhitelist() const;
    void setWhitelist(const QStringList& whitelist);

    // Static methods for saving and loading whitelist
    static void saveWhitelist(const QStringList& whitelist);
    static QStringList loadWhitelist();

signals:
    void whitelistChanged(const QStringList& newWhitelist);

private slots:
    void addCharacter();
    void removeCharacter();

private:
    void updateWhitelistDisplay();

    Ui::WhitelistSettingsUI* ui;
    QStringList m_whitelist;
};