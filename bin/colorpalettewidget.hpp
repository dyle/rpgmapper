/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_COLORPALETTEWIDGET_HPP
#define RPGMAPPER_VIEW_COLORPALETTEWIDGET_HPP

#include <QWidget>


namespace rpgmapper {
namespace view {


/**
 * A widget which is capable to show a color palette and select a single color.
 */
class ColorPaletteWidget : public QWidget {

    Q_OBJECT
    
public:
    
    /**
     * Constructor.
     *
     * @param   parent      The parent QWidget instance.
     */
    explicit ColorPaletteWidget(QWidget * parent = nullptr);
    
};


}
}


#endif
