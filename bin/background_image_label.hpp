/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_BACKGROUND_IMAGE_LABEL_HPP
#define RPGMAPPER_VIEW_BACKGROUND_IMAGE_LABEL_HPP


#include <QLabel>

#include <rpgmapper/layer/background_renderer.hpp>


namespace rpgmapper {
namespace view {


class BackgroundImageLabel : public QLabel, public rpgmapper::model::BackgroundRenderer {

    Q_OBJECT

public:

    explicit BackgroundImageLabel(QWidget * parent);

    QPixmap const * getBackgroundPixmap() const override {
        return pixmap();
    }

protected:

    void paintEvent(QPaintEvent * event) override;
};


}
}


#endif
