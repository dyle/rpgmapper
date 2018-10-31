/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_TEXT_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_TEXT_LAYER_HPP

#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {


/**
 * The objects of this class are capable of drawing text on the map.
 */
class TextLayer : public Layer {

    Q_OBJECT

public:

    /**
     * Constructs a new TextLayer.
     *
     * @param   map     the map this layer belongs to.
     */
    explicit TextLayer(QSharedPointer<Map> map);

    /**
     * Destructs the TextLayer.
     */
    ~TextLayer() override = default;

    /**
     * Draws the known text items on the map.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void draw(QPainter & painter, int tileSize) const override;

    /**
     * Extracts this layer as JSON object.
     *
     * @return  a JSON object holding the layer data.
     */
    QJsonObject getJSON() const override;

};


}
}


#endif
