#include "WhitelistSettingsUI.h"
#include "ui_WhitelistSettingsUI.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>
#include <QDir>
#include <QCoreApplication>
#include <QMessageBox>
#include <QLabel>

WhitelistSettingsUI::WhitelistSettingsUI(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::WhitelistSettingsUI)
{
    ui->setupUi(this);

    // Set title and flags
    setWindowTitle("Whitelist Settings");
    setWindowFlags(Qt::Window);

    // Apply 3D style to buttons
    QString buttonStyle = R"(
        QPushButton {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #4A4A4A, stop:1 #3A3A3A);
            border: 1px solid #555555;
            border-radius: 3px;
            color: white;
            padding: 3px;
            min-height: 20px;
            max-height: 20px;
        }
        QPushButton:hover {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #5A5A5A, stop:1 #4A4A4A);
        }
        QPushButton:pressed {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #3A3A3A, stop:1 #2A2A2A);
            border: 1px solid #222222;
            padding-top: 4px;
            padding-left: 4px;
            padding-bottom: 2px;
            padding-right: 2px;
        }
    )";

    ui->addButton->setStyleSheet(buttonStyle);
    ui->removeButton->setStyleSheet(buttonStyle);

    // Apply existing stylesheet
    QString styleSheet = parent->styleSheet();
    this->setStyleSheet(styleSheet);
    ui->whitelistWidget->setStyleSheet(styleSheet + ui->whitelistWidget->styleSheet());

    connect(ui->addButton, &QPushButton::clicked, this, &WhitelistSettingsUI::addCharacter);
    connect(ui->removeButton, &QPushButton::clicked, this, &WhitelistSettingsUI::removeCharacter);

    loadWhitelist();

    // Set a minimum size for the window
    setMinimumSize(300, 400);
}

WhitelistSettingsUI::~WhitelistSettingsUI()
{
    delete ui;
}
void WhitelistSettingsUI::addCharacter()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add Character");
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    QLineEdit* lineEdit = new QLineEdit(&dialog);
    layout->addWidget(new QLabel("Enter character name:", &dialog));
    layout->addWidget(lineEdit);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okButton = new QPushButton("OK", &dialog);
    QPushButton* cancelButton = new QPushButton("Cancel", &dialog);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    // Apply the same 3D style to OK and Cancel buttons
    okButton->setStyleSheet(ui->addButton->styleSheet());
    cancelButton->setStyleSheet(ui->addButton->styleSheet());

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString character = lineEdit->text().trimmed();
        if (!character.isEmpty()) {
            if (ui->whitelistWidget->findItems(character, Qt::MatchExactly).isEmpty()) {
                ui->whitelistWidget->addItem(character);
                saveWhitelist(getWhitelist());  // Pass the whitelist
                emit whitelistChanged(getWhitelist());
            }
            else {
                QMessageBox::warning(this, "Duplicate Entry", "This character is already in the whitelist.");
            }
        }
    }
}

void WhitelistSettingsUI::removeCharacter()
{
    QListWidgetItem* item = ui->whitelistWidget->currentItem();
    if (item) {
        delete ui->whitelistWidget->takeItem(ui->whitelistWidget->row(item));
        saveWhitelist(getWhitelist());  // Pass the whitelist
        emit whitelistChanged(getWhitelist());
    }
}

QStringList WhitelistSettingsUI::getWhitelist() const
{
    QStringList whitelist;
    for (int i = 0; i < ui->whitelistWidget->count(); ++i) {
        whitelist << ui->whitelistWidget->item(i)->text();
    }
    return whitelist;
}

void WhitelistSettingsUI::setWhitelist(const QStringList& whitelist)
{
    ui->whitelistWidget->clear();
    ui->whitelistWidget->addItems(whitelist);
}

void WhitelistSettingsUI::saveWhitelist(const QStringList& whitelist)
{
    QString configPath = QCoreApplication::applicationDirPath() + "/Config";
    QDir().mkpath(configPath);  // Ensure the Config directory exists
    QString filePath = configPath + "/Whitelist.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setValue("Whitelist", whitelist);
}

QStringList WhitelistSettingsUI::loadWhitelist()
{
    QString configPath = QCoreApplication::applicationDirPath() + "/Config";
    QString filePath = configPath + "/Whitelist.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    return settings.value("Whitelist").toStringList();
}