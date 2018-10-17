/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP

#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {


// Forward declaration of the TileLayer class.
class TileLayer;


/**
 * A smart pointer on the heap for TileLayer objects.
 */
using TileLayerPointer = QSharedPointer<TileLayer>;


/**
 * A list of TileLayer objects.
 */
using TileLayers = std::list<TileLayerPointer>;


/**
 * A TileLayer object draws tiles on the map.
 */
class TileLayer : public Layer {

    Q_OBJECT

    std::map<int, FieldPointer> fields;         /**< All known fields of this layer. */

public:

    /**
     * Constructs a new TileLayer.
     *
     * @param   map         the Map instance the layer belongs to.
     * @param   parent      QObject parent.
     */
    explicit TileLayer(rpgmapper::model::Map * map, QObject * parent = nullptr);

    /**
     * Destructs the TileLayer.
     */
    ~TileLayer() override = default;

    /**
     * Adds a new Field instance to this layer.
     *
     * The given field data will be copied.
     *
     * @param   field       the new field to add to this layer.
     */
    void addField(Field const & field);

    /**
     * Draws the tiles defined on the map.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    void draw(QPainter & painter, int tileSize) const override;

    /**
     * Gets a field from the map.
     *
     * If the field is not found, an invalid field is returned.
     *
     * @param   index       the field index.
     */
    FieldPointer const getField(int index) const;

    /**
     * Gets a field from the map.
     *
     * If the field is not found, an invalid field is returned.
     *
     * @param   x       X-coordinate of the field.
     * @param   y       Y-coordinate of the field.
     */
    FieldPointer const getField(int x, int y) const {
        return getField(Field::getIndex(x, y));
    }

    /**
     * Gets a field from the map.
     *
     * If the field is not found, an invalid field is returned.
     *
     * @param   point   point holding the field's position.
     */
    FieldPointer const getField(QPoint const & point) const {
        return getField(point.x(), point.y());
    }

    /**
     * Extracts this layer as JSON object.
     *
     * @param   content     TODO: why content object?
     * @return  a JSON object holding the layer data.
     */
    QJsonObject getJsonObject(rpgmapper::model::io::Content & content) const override;

};


}
}


#endif
