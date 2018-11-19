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

    /**
     * The user wants to edit the atlas properties.
     */
    void editAtlasProperties();

    /**
     * The user wants to edit the properties of a map.
     */
    void editMapProperties();

    /**
     * The user wants to edit the properties of a region.
     */
    void editRegionProperties();

    /**
     * Check which action can currently be enabled and which disabled.
     */
    void enableActions();

    /**
     * Adjust the window title.
     */
    void setApplicationWindowTitle();

    /**
     * Make some map coordinates visible.
     *
     * @param   x       X-Coordinate
     * @param   y       Y-Coordinate
     */
    void showCoordinates(int x, int y);

    /**
     * Shoe/hide the color picker widget.
     *
     * @param   visible     show/hide flag for widget.
     */
    void visibleColorPicker(bool visible);

    /**
     * Show/hide the minimap.
     *
     * @param   visible     show/hide flag for the minimap.
     */
    void visibleMinimap(bool visible);

    /**
     * Show/hide structure widget
     *
     * @param   visible     show/hide structure widget.
     */
    void visibleStructure(bool visible);

    /**
     * Show/hide tile choser.
     *
     * @param   visible     show/hide tile choser.
     */
    void visibleTiles(bool visible);

protected:

    /**
     * Handle application close event.
     *
     * @param   event       the close event.
     */
    void closeEvent(QCloseEvent * event) override;

    /**
     * Hanlde application show event.
     *
     * @param   event       the show event.
     */
    void showEvent(QShowEvent * event) override;

private:

    /**
     * Adds a filename to the list of recently used files.
     *
     * @param   fileName        a new recently used filename.
     */
    void addRecentFileName(QString const & fileName);

    /**
     * TODO: ?
     */
    void addUnusedActions();

    /**
     * Centers the window in the middle of the desktop.
     */
    void centerWindow();

    /**
     * Connect all actions known to the application.
     */
    void connectActions();

    // TODO: void connectModelSignals();

    /**
     * Clear the actions of the recent files.
     */
    void clearRecentFileActions();

    /**
     * Create the QActions for the recent files.
     */
    void createRecentFileActions();

    /**
     * Loads an atlas.
     * @param   fileName        the filename to load
     */
    void loadAtlas(QString fileName);

    /**
     * Load application settings.
     */
    void loadSettings();

    /**
     * Show the about dialog.
     */
    void showAboutDialog();

    /**
     * Saves the current atals to disk.
     *
     * @param   fileName        file to save the atlas to.
     */
    void saveAtlas(QString fileName);

    /**
     * Saves the current application settings to disk.
     */
    void saveSettings();

    /**
     * Saves the list of recently used files to a settings instance.
     *
     * @param   settings        settings instance to be filled with the list.
     */
    void saveSettingsRecentFiles(QSettings & settings);

    /**
     * Save the current window size and position to a settings instance.
     *
     * @param   settings        settings instance to be filled.
     */
    void saveSettingsWindow(QSettings & settings);

    /**
     * Pre-create all dialogs.
     */
    void setupDialogs();

private slots:

    /**
     * Clears the list of recently used files.
     */
    void clearListOfRecentFiles();

    /**
     * A new map has been created.
     */
    void createNewMap();

    /**
     * A new region has been created.
     */
    void createNewRegion();

    /**
     * A map has been deleted.
     */
    void deleteMap();

    /**
     * A region has been deleted.
     */
    void deleteRegion();

    /**
     * A command has been executed.
     */
    void executedCommand();

    /**
     * Load action.
     */
    void load();

    /**
     * Loads the last used file.
     */
    void loadRecentFile();
    
    /**
     * Save action.
     */
    void save();

    /**
     * Save with a name action.
     */
    void saveAs();
};


}
}


#endif
