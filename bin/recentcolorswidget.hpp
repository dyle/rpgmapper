/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_RECENTCOLORSWIDGET_HPP
#define RPGMAPPER_VIEW_RECENTCOLORSWIDGET_HPP

#include <QWidget>


namespace rpgmapper {
namespace view {


/**
 * Displays the recent colors the user picked.
 */
class RecentColorsWidget : public QWidget {

    Q_OBJECT

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
