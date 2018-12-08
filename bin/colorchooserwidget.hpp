/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_COLORCHOOSERWIDGET_HPP
#define RPGMAPPER_VIEW_COLORCHOOSERWIDGET_HPP

#include <array>
#include <map>
#include <memory>

#include <QWidget>

#include <rpgmapper/colorpalette.hpp>


// fwd
class Ui_ColorChooserWidget;


namespace rpgmapper {
namespace view {


/**
 * This widget lets the user choose a color and a color palette (including load/save and recent colors).
 */
class ColorChooserWidget : public QWidget {

    Q_OBJECT
    
    std::shared_ptr<Ui_ColorChooserWidget> ui;                      /**< The User Interface as created by the uic. */
    
    std::map<QString, rpgmapper::model::ColorPalette> palettes;     /**< Known palettes. */
    
public:
    
    /**
     * Constructor.
     *
     * @param   parent      The parent QWidget instance.
     */
    explicit ColorChooserWidget(QWidget * parent = nullptr);
    
public slots:
    
    /**
     * Loads the color palettes form the resources.
     */
    void loadPalettes();
    
private:
    
    /**
     * Loads a reosurce as color palette.
     *
     * @param   palette             the color palette to be filled.
     * @param   resourceName        the name of the resource to load.
     * @return  if the color palette has been loaded.
     */
    bool loadPalette(rpgmapper::model::ColorPalette & palette, QString const & resourceName) const;
};


}
}


#endif
