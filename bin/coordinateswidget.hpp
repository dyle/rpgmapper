/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_COORDINATEWIDGET_HPP
#define RPGMAPPER_VIEW_COORDINATEWIDGET_HPP

#include <memory>

#include <QWidget>

#include <rpgmapper/coordinate_system.hpp>


// fwd
class Ui_coordinatesWidget;


namespace rpgmapper {
namespace view {


/**
 * The CoordinatesWidget display a X- and Y-coordinate as a small label.
 */
class CoordinatesWidget : public QWidget {

    Q_OBJECT

    std::shared_ptr<Ui_coordinatesWidget> ui;           /**< The User Interface as created by the uic. */

public:
    
    /**
     * Constructor
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit CoordinatesWidget(QWidget * parent);

public slots:

    /**
     * Resets the X- and Y-Coordinate.
     */
    void clear();

    /**
     * Displays the coordinates.
     *
     * @param   coordinates     coordinates to display.
     */
    void showCoordinates(rpgmapper::model::NumeralCoordinates coordinates);
};


}
}


#endif
