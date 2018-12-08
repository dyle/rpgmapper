/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_RECENTCOLORSWIDGET_HPP
#define RPGMAPPER_VIEW_RECENTCOLORSWIDGET_HPP

#include <array>

#include <QWidget>

#include "colorwidget.hpp"


namespace rpgmapper {
namespace view {


/**
 * Displays the recent colors the user picked.
 */
class RecentColorsWidget : public QWidget {

    Q_OBJECT
    
    /**
     * The color widgets showing the recent colors.
     */
    std::array<std::array<rpgmapper::view::ColorWidget *, 2>, 8> colorWidgets;
    
public:
    
    /**
     * Constructor.
     *
     * @param   parent      The parent QWidget instance.
     */
    explicit RecentColorsWidget(QWidget * parent = nullptr);
    
};


}
}


#endif
