/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
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
