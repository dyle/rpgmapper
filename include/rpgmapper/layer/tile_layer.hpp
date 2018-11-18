/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP

#include <QPoint>

#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {


/**
 * A TileLayer object draws tiles on the map.
 */
class TileLayer : public Layer {

    Q_OBJECT

    std::map<int, QSharedPointer<Field>> fields;        /**< All known fields of this layer. */

public:

    /**
     * Constructs a new TileLayer.
     *
     * @param   map     the map this layer belongs to.
     */
    explicit TileLayer(Map * map);

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
    QSharedPointer<Field> const getField(int index) const;

    /**
     * Gets a field from the map.
     *
     * If the field is not found, an invalid field is returned.
     *
     * @param   x       X-coordinate of the field.
     * @param   y       Y-coordinate of the field.
     */
    QSharedPointer<Field> const getField(int x, int y) const {
        return getField(Field::getIndex(x, y));
    }
    
    /**
     * Gets a field from the map.
     *
     * If the field is not found, an invalid field is returned.
     *
     * @param   position        position holding the field's position.
     */
    QSharedPointer<Field> const getField(QPoint position) const {
        return getField(position.x(), position.y());
    }

    /**
     * Extracts this layer as JSON object.
     *
     * @return  a JSON object holding the layer data.
     */
    QJsonObject getJSON() const override;
    
    /**
     * Removes a field from the layer
     *
     * @param   index       the field index.
     */
    void removeField(int index);
    
    /**
     * Removes a field from the layer
     *
     * @param   x       x-coordinate of field.
     * @param   y       y-coordinate of field.
     */
    void removeField(int x, int y) {
        removeField(Field::getIndex(x, y));
    }
    
    /**
     * Removes a field from the layer
     *
     * @param   position    point holding the field's position.
     */
    void removeField(QPoint position) {
        removeField(Field::getIndex(position.x(), position.y()));
    }

signals:
    
    /**
     * A field has been added.
     *
     * @param   position        position of the added field.
     */
    void fieldAdded(QPoint position);
    
    /**
     * A field has been removed.
     * @param   position        position of the field removed.
     */
    void fieldRemoved(QPoint position);

};


}
}


#endif
