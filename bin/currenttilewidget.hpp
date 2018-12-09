/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_CURRENTTILEWIDGET_HPP
#define RPGMAPPER_VIEW_CURRENTTILEWIDGET_HPP

#include <QWidget>


namespace rpgmapper {
namespace view {


/**
 * The CurrentTileWidget displays a selected tile.
 */
class CurrentTileWidget : public QWidget {

    Q_OBJECT
    
public:
    
    /**
     * Constructor
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit CurrentTileWidget(QWidget * parent = nullptr);
};


}
}


#endif
