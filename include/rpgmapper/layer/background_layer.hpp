/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_BACKGROUND_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_BACKGROUND_LAYER_HPP


#include <QColor>
#include <QImage>
#include <QMargins>
#include <QUuid>

#include <rpgmapper/layer/image_render_mode.hpp>
#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {

class BackgroundLayer;
using BackgroundLayerPointer = QSharedPointer<BackgroundLayer>;

class BackgroundLayer : public Layer {

    Q_OBJECT

    QImage image;
    QString imageResourcePath;

public:

    explicit BackgroundLayer(rpgmapper::model::Map * map, QObject * parent = nullptr);

    ~BackgroundLayer() override = default;

    void draw(QPainter & painter, int tileSize) const override;

    QColor getColor() const;

    QImage const & getImage() const;

    QString getImageResourcePath() const {
        return imageResourcePath;
    }

    ImageRenderMode getImageRenderMode() const;

    QJsonObject getJsonObject() const override;

    QMargins getMargins() const;

    QString getRendering() const;

    bool isColorRendered() const;

    bool isImageRendered() const;

    bool isImageRenderedPlain() const {
        return getImageRenderMode() == ImageRenderMode::plain;
    }

    bool isImageRenderedScaled() const {
        return getImageRenderMode() == ImageRenderMode::scaled;
    }

    bool isImageRenderedTiled() const {
        return getImageRenderMode() == ImageRenderMode::tiled;
    }

    static bool isValidRendering(QString const & rendering);

    void setColor(QColor color);

    void setImage(QImage image);

    void setImageRenderMode(ImageRenderMode mode);

    void setMargins(QMargins const & margins);

    void setRendering(QString const & rendering);
};



}
}


#endif
