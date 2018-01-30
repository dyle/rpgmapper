/*
 * coordinatewidget.hpp
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


#ifndef VIEW_COORDINATEWIDGET_HPP
#define VIEW_COORDINATEWIDGET_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QWidget>


// ------------------------------------------------------------
// decl


// fwd
class Ui_coordinatewidget;


namespace rpgmapper {
namespace view {


/**
 * The rpgmapper coordinate widget displays the X and Y coordinates in the statusbar.
 */
class CoordinateWidget : public QWidget {


    Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent         parent widget instance
     */
    CoordinateWidget(QWidget * cParent);


public slots:


    /**
     * Clears the coordinate display.
     */
    void clear();


    /**
     * Display some coordinates.
     *
     * @param   sXCoordinate        the X coordinate in user dimensions
     * @param   sYCoordinate        the Y coordinate in user dimensions
     */
    void showCoordinates(QString sXCoordinate, QString sYCoordinate);


private:


    std::shared_ptr<Ui_coordinatewidget> ui;       /**< User interface. */

};


}
}


#endif
