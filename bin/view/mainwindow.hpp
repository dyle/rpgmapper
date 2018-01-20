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
     * ctor
     */
    MainWindow();


protected:


    /**
     * handle close event
     *
     * @param   cEvent      the event passed
     */
    void closeEvent(QCloseEvent * cEvent) override;



private slots:


    /**
     * Load an atlas.
     */
    void load();


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
     * Centers the window on the desktop with default width and height.
     */
    void centerWindow();


    /**
     * Connects all action signals for this MainWindow.
     */
    void connectActions();


    /**
     * Load the settings.
     */
    void loadSettings();


    /**
     * Setup the internal dialogs.
     */
    void setupDialogs();


    class MainWindow_data;                              /**< Internal data type. */
    std::shared_ptr<MainWindow::MainWindow_data> d;     /**< Internal data instance. */
};


}
}


#endif
