/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MAINWINDOW_HPP
#define RPGMAPPER_MAINWINDOW_HPP


#include <memory>

#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>

#include <rpgmapper/selection.hpp>
#include "aboutdialog.hpp"
#include "coordinateswidget.hpp"
#include "logdialog.hpp"
#include "mappropertiesdialog.hpp"


class Ui_mainwindow;


namespace rpgmapper {
namespace view {


class MainWindow : public QMainWindow {

    Q_OBJECT

    std::shared_ptr<Ui_mainwindow> ui;

    rpgmapper::model::SelectionPointer selection;

    AboutDialog * aboutDialog = nullptr;
    QFileDialog * loadAtlasDialog = nullptr;
    LogDialog * logDialog = nullptr;
    MapPropertiesDialog * mapPropertiesDialog = nullptr;
    QFileDialog * saveAtlasDialog = nullptr;

    QStringList recentAtlasFileNames;
    QString recentAtlasFolderName;
    int maximumRecentAtlasFiles = 10;
    QList<QAction *> recentFileLoadActions;

    CoordinatesWidget * coordinatesWidget = nullptr;

public:

    MainWindow();

    rpgmapper::model::AtlasPointer & getAtlas();

    rpgmapper::model::AtlasPointer const & getAtlas() const;

public slots:

    void editAtlasProperties();

    void editMapProperties();

    void editRegionProperties();

    void enableActions();

    void setApplicationWindowTitle();

    void showCoordinates(int mapX, int mapY);

    void visibleColorPicker(bool visible);

    void visibleMinimap(bool visible);

    void visibleStructure(bool visible);

    void visibleTiles(bool visible);

protected:

    void closeEvent(QCloseEvent * event) override;

    void showEvent(QShowEvent * event) override;

private:

    void addRecentFileName(QString const & fileName);

    void addUnusedActions();

    void centerWindow();

    void connectActions();

    void connectModelSignals();

    void clearRecentFileActions();

    void createRecentFileActions();

    void loadAtlas(QString const & fileName);

    void loadSettings();

    void showAboutDialog();

    void saveAtlas(QString const & fileName);

    void saveSettings();

    void saveSettingsRecentFiles(QSettings & settings);

    void saveSettingsWindow(QSettings & settings);

    void setupDialogs();

private slots:

    void atlasNameChanges(QString newName);

    void clearListOfRecentFiles();

    void createNewMap();

    void load();

    void loadRecentFile();

    void save();

    void saveAs();
};


}
}


#endif
