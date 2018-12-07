/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_COLORCHOOSERWIDGET_HPP
#define RPGMAPPER_VIEW_COLORCHOOSERWIDGET_HPP

#include <memory>

#include <QWidget>


// fwd
class Ui_ColorChooserWidget;


namespace rpgmapper {
namespace view {


/**
 * This widget lets the user choose a color and a color palette (including load/save and recent colors).
 */
class ColorChooserWidget : public QWidget {

    Q_OBJECT
    
    std::shared_ptr<Ui_ColorChooserWidget> ui;        /**< The User Interface as created by the uic. */

public:
    
    /**
     * Constructor.
     *
     * @param   parent      The parent QWidget instance.
     */
    explicit ColorChooserWidget(QWidget * parent = nullptr);
    
};


}
}


#endif
