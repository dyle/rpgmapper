/*
 * mainwindow.hpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef VIEW_MAINWINDOW_HPP
#define VIEW_MAINWINDOW_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QMainWindow>
#include <QSettings>


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
     * Switch enabled state of actions.
     *
     * This method checks the action is enabled or disabled for a series of available actions.
     */
    void enableActions();


    /**
     * Reapply the atlas to teh whole view.
     */
    void resetAtlas();


protected:


    /**
     * handle close event
     *
     * @param   cEvent      the event passed
     */
    void closeEvent(QCloseEvent * cEvent) override;



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
