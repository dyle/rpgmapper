/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_BACKGROUND_IMAGE_LABEL_HPP
#define RPGMAPPER_VIEW_BACKGROUND_IMAGE_LABEL_HPP

#include <QLabel>

#include <rpgmapper/layer/background_renderer.hpp>


namespace rpgmapper {
namespace view {


/**
 * This class renders a background (plain, scaled, tiled) on a QLabel.
 */
class BackgroundImageLabel : public QLabel, public rpgmapper::model::layer::BackgroundRenderer {

    Q_OBJECT

public:

    /**
     * Constructor
     *
     * @param   parent      parent widget.
     */
    explicit BackgroundImageLabel(QWidget * parent);

    /**
     * Returns the pixmap used as background.
     *
     * @return  the pixmap used as background.
     */
    QPixmap const * getBackgroundPixmap() const override {
        return pixmap();
    }

protected:

    /**
     * Draws this widget.
     *
     * @param   event       the paint event involved.
     */
    void paintEvent(QPaintEvent * event) override;
};


}
}


#endif
