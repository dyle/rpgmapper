/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_BACKGROUND_IMAGE_RENDERER_HPP
#define RPGMAPPER_VIEW_BACKGROUND_IMAGE_RENDERER_HPP


#include <QLabel>

#include <rpgmapper/layer/background_layer.hpp>


namespace rpgmapper {
namespace view {


class BackgroundImageRenderer : public QLabel {

    Q_OBJECT

    rpgmapper::model::BackgroundLayer::ImageRenderMode renderMode;

public:

    explicit BackgroundImageRenderer(QWidget * parent);

    rpgmapper::model::BackgroundLayer::ImageRenderMode getImageRenderMode() const { return renderMode; }

    void setImageRenderMode(rpgmapper::model::BackgroundLayer::ImageRenderMode renderMode);

private:

    void paintEvent(QPaintEvent * event) override;

};


}
}


#endif
