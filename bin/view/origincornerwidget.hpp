/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef VIEW_ORIGINCORNERWIDGET_HPP
#define VIEW_ORIGINCORNERWIDGET_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QDialog>

#include <rpgmapper/map.hpp>


// ------------------------------------------------------------
// decl


// fwd
class Ui_origincornerwidget;


namespace rpgmapper {
namespace view {


/**
 * A widget to let the user select the map's point of origin: top/left, top/right, bottom/left or bottom/right.
 */
class OriginCornerWidget : public QWidget {


Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent         parent widget instance
     */
    explicit OriginCornerWidget(QWidget * cParent);


    /**
     * Get the current selected corner.
     *
     * @return  the current selected corner
     */
    rpgmapper::model::Map::map_corner corner() const;


public slots:


    /**
     * Set the active corner.
     *
     * @param   eCorner     the current active corner
     */
    void setCorner(rpgmapper::model::Map::map_corner eCorner);


private:


    std::shared_ptr<Ui_origincornerwidget> ui;       /**< User interface. */

};


}
}


#endif
