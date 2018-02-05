/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef VIEW_MAINWINDOW_HPP
#define VIEW_MAINWINDOW_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QMainWindow>
#include <QSettings>

// rpgmapper
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace view {


/**
 * the rpgmapper main window
 */
class MainWindow : public QMainWindow {


    Q_OBJECT


public:


    /**
     * Ctor.
     */
    MainWindow();


public slots:


    /**
     * Let the user edit the properties of the current atlas.
     */
    void editAtlasProperties();


    /**
     * Let the user edit the properties of the current selected map.
     */
    void editMapProperties();


    /**
     * Let the user edit the properties of the current selected region.
     */
    void editRegionProperties();


    /**
     * Switch enabled state of actions.
     *
     * This method checks the action is enabled or disabled for a series of available actions.
     */
    void enableActions();


    /**
     * The current map should be deleted.
     */
    void deleteMap();


    /**
     * The current region should be deleted.
     */
    void deleteRegion();


    /**
     * A new map shall be created.
     */
    void newMap();


    /**
     * A new region shall be created.
     */
    void newRegion();


    /**
     * Reapply the atlas to teh whole view.
     */
    void resetAtlas();


    /**
     * Shows the coordinates in user world transformation at the statusbar.
     *
     * @param   x   X-coordinate on the map (with origin top/left)
     * @param   y   Y-coordinate on the map (with origin top/left)
     */
    void showCoordinates(int x, int y);


    /**
     * Toggle the minimap window visibility.
     *
     * @param   bView       visibility of window
     */
    void visibleMinimap(bool bView);


    /**
     * Toggle the structure window visibility.
     *
     * @param   bView       visibility of window
     */
    void visibleStructure(bool bView);


    /**
     * Toggle the tiles window visibility.
     *
     * @param   bView       visibility of window
     */
    void visibleTiles(bool bView);


protected:


    /**
     * Handle close event
     *
     * @param   cEvent      the event passed
     */
    void closeEvent(QCloseEvent * cEvent) override;


    /**
     * Handle the show event.
     *
     * @param   cEvent      show event info
     */
    void showEvent(QShowEvent * cEvent) override;


private slots:


    /**
     * The atlas changed.
     */
    void changedAtlas();


    /**
     * Clear list of recent files.
     */
    void clearListOfRecentFiles();


    /**
     * Load an atlas.
     */
    void load();


    /**
     * Load a recent file.
     */
    void loadRecentFile();


    /**
     * Save the atlas.
     */
    void save();


    /**
     * Save the atlas with a new filename.
     */
    void saveAs();


private:


    /**
     * Adds a filename to the list of recent filenames.
     *
     * @param   sFileName       the filename to add
     */
    void addRecentFileName(QString const & sFileName);


    /**
     * Centers the window on the desktop with default width and height.
     */
    void centerWindow();


    /**
     * Empties the sub menu of recent files, but the "Clear List" action.
     */
    void clearRecentFileActions();


    /**
     * Connects all action signals for this MainWindow.
     */
    void connectActions();


    /**
     * Create list of recent file menu actions.
     */
    void createRecentFileActions();


    /**
     * Load an atlas from a file.
     *
     * @param   sFileName       the file to load
     */
    void loadAtlas(QString const & sFileName);


    /**
     * Load the settings.
     */
    void loadSettings();


    /**
     * Save the atlas to a file.
     *
     * @param   sFileName       the file to save the atlas to
     */
    void saveAtlas(QString const & sFileName);


    /**
     * Save the rpgmapper settings.
     */
    void saveSettings();


    /**
     * Save the window geometry and states.
     *
     * @param   cSettings       settings instance to save to
     */
    void saveSettingsRecentFiles(QSettings & cSettings);


    /**
     * Save the list of recent atlas files.
     *
     * @param   cSettings       settings instance to save to
     */
    void saveSettingsWindow(QSettings & cSettings);


    /**
     * Setup the internal dialogs.
     */
    void setupDialogs();


    /**
     * Show about dialog.
     */
    void showAboutDialog();


    class MainWindow_data;                              /**< Internal data type. */
    std::shared_ptr<MainWindow::MainWindow_data> d;     /**< Internal data instance. */
};


}
}


#endif
