/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_ORIGINCORNERWIDGET_HPP
#define RPGMAPPER_VIEW_ORIGINCORNERWIDGET_HPP

#include <memory>

#include <QDialog>

#include <rpgmapper/coordinate_system.hpp>


// fwd
class Ui_coordinatesOriginWidget;


namespace rpgmapper {
namespace view {


/**
 * This is a small widget, which lets the user chose in which corner the origin of map resides.
 */
class CoordinatesOriginWidget : public QWidget {

    Q_OBJECT

    std::shared_ptr<Ui_coordinatesOriginWidget> ui;         /**< The User Interface as created by the uic. */

public:

    /**
     * Constructor.
     *
     * @param   parent      The parent QWidget instance.
     */
    explicit CoordinatesOriginWidget(QWidget * parent);

    /**
     * Retrieves the orgin corner set.
     *
     * @return  a maps origin corner.
     */
    rpgmapper::model::CoordinatesOrigin getOrigin() const;

public slots:

    /**
     * Sets a new maps origin corner for this widget.
     *
     * @param   origin      a new map origin to display.
     */
    void setOrigin(rpgmapper::model::CoordinatesOrigin origin);
};


}
}


#endif
