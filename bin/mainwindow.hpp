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

#include "aboutdialog.hpp"
#include "coordinateswidget.hpp"
#include "logdialog.hpp"
#include "mappropertiesdialog.hpp"


// fwd
class Ui_mainwindow;


namespace rpgmapper {
namespace view {


/**
 * This is the rpgmapper main window, holding the whole application in place.
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

    std::shared_ptr<Ui_mainwindow> ui;                          /**< The User Interface as created by the uic. */

    AboutDialog * aboutDialog = nullptr;                        /**< Pre-created about dialog. */
    QFileDialog * loadAtlasDialog = nullptr;                    /**< Pre-created load dialog. */
    LogDialog * logDialog = nullptr;                            /**< Pre-created log dialog. */
    MapPropertiesDialog * mapPropertiesDialog = nullptr;        /**< Pre-created map properties dialog. */
    QFileDialog * saveAtlasDialog = nullptr;                    /**< Pre-created save dialog. */

    QStringList recentAtlasFileNames;                           /**< List of recent loaded/saved atlas files. */
    QString recentAtlasFolderName;                              /**< The last folder to load/save an atlas file. */
    int maximumRecentAtlasFiles = 10;                           /**< Maximum number of entries in the recent list. */
    QList<QAction *> recentFileLoadActions;                     /**< Menu-actions to load the atlas files. */

    CoordinatesWidget * coordinatesWidget = nullptr;            /**< Pre-created coordinate widgets. */

public:

    /**
     * Constructor.
     */
    MainWindow();

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

    // TODO: void connectModelSignals();

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

    void clearListOfRecentFiles();

    void createNewMap();

    void createNewRegion();

    void deleteMap();

    void deleteRegion();

    void executedCommand();

    void load();

    void loadRecentFile();

    void save();

    void saveAs();
};


}
}


#endif
