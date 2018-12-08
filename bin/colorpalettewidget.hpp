/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_COLORPALETTEWIDGET_HPP
#define RPGMAPPER_VIEW_COLORPALETTEWIDGET_HPP

#include <array>

#include <QWidget>

#include <rpgmapper/colorpalette.hpp>
#include "colorwidget.hpp"


namespace rpgmapper {
namespace view {


/**
 * A widget which is capable to show a color palette and select a single color.
 */
class ColorPaletteWidget : public QWidget {

    Q_OBJECT

    rpgmapper::model::ColorPalette palette;     /**< The current palette loaded. */
    
    /**
     * The color widgets showing the palette.
     */
    std::array<std::array<rpgmapper::view::ColorWidget *, 16>, 16> colorWidgets;
    
    int selectedIndex = -1;                     /**< Current selected color. */
    
public:
    
    /**
     * Constructor.
     *
     * @param   parent      The parent QWidget instance.
     */
    explicit ColorPaletteWidget(QWidget * parent = nullptr);
    
    
    /**
     * Sets a new color palette.
     *
     * @param   palette     the new palette to show.
     */
    void setPalette(rpgmapper::model::ColorPalette const & palette);
    
private slots:
    
    /**
     * The selection of a single color has changed.
     *
     * @param   id              id of the color in the grid.
     * @param   selected        selected flag
     */
    void colorSelectedChange(int id, bool selected);
};


}
}


#endif
