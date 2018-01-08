/*
 * main_window.h
 *
 * Main window for the RPGMapper
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


#ifndef VIEW_MAINWINDOW_H_
#define VIEW_MAINWINDOW_H_


// ------------------------------------------------------------
// incs

// Qt
#include <QMainWindow>


// ------------------------------------------------------------
// decl

// fwd
class Ui_mainwindow;


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


    /**
     * dtor
     */
    virtual ~MainWindow();


protected:


    /**
     * handle close event
     *
     * @param   cEvent      the event passed
     */
    virtual void closeEvent(QCloseEvent * cEvent);


private:


    /**
     * centers the window on the desktop with default width and height
     */
    void centerWindow();


    /**
     * load the settings
     */
    void loadSettings();


    Ui_mainwindow * ui;                 /**< qt widgets */
};


}
}


#endif
