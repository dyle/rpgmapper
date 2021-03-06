/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP

#include <map>

#include <QJsonObject>
#include <QPainter>
#include <QPoint>
#include <QSharedPointer>

#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/field_pointer.hpp>


// fwd
namespace rpgmapper::model { class Map; }


namespace rpgmapper::model::layer {


/**
 * A TileLayer object draws tiles on the map.
 */
class TileLayer : public Layer {

    Q_OBJECT

    std::map<int, rpgmapper::model::FieldPointer> fields;        /**< All known fields of this layer. */

public:

    /**
     * Constructs a new TileLayer.
     *
     * @param   map     the map this layer belongs to.
     */
    explicit TileLayer(rpgmapper::model::Map * map);

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
    void addField(rpgmapper::model::FieldPointer field);

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
    rpgmapper::model::FieldPointer const getField(int index) const;

    /**
     * Gets a field from the map.
     *
     * If the field is not found, an invalid field is returned.
     *
     * @param   x       X-coordinate of the field.
     * @param   y       Y-coordinate of the field.
     */
    rpgmapper::model::FieldPointer const getField(int x, int y) const;
    
    /**
     * Gets a field from the map.
     *
     * If the field is not found, an invalid field is returned.
     *
     * @param   position        position holding the field's position.
     */
    rpgmapper::model::FieldPointer const getField(QPoint position) const {
        return getField(position.x(), position.y());
    }
    
    /**
     * Gets a field from the map.
     *
     * If the field is not found, an invalid field is returned.
     *
     * @param   position        position holding the field's position.
     */
    rpgmapper::model::FieldPointer const getField(QPointF position) const {
        return getField(static_cast<int>(position.x()), static_cast<int>(position.y()));
    }
    
    /**
     * Returns all known fields on this layer.
     *
     * @return  the fields of this layer.
     */
    std::map<int, rpgmapper::model::FieldPointer> const & getFields() const {
        return fields;
    }

    /**
     * Extracts this layer as JSON object.
     *
     * @return  a JSON object holding the layer data.
     */
    QJsonObject getJSON() const override;
    
    /**
     * Checks if there is a field present at the given location.
     *
     * @param   x       the X coordinate.
     * @param   y       the Y coordinate.
     * @return  true, of there is a field already.
     */
    bool isFieldPresent(int x, int y) const;
    
    /**
     * Checks if there is a field at the given position already present.
     *
     * @param   position    the position.
     * @return  true, if there is a field at this position.
     */
    bool isFieldPresent(QPoint const & position) const {
        return isFieldPresent(position.x(), position.y());
    }
    
    /**
     * Checks if there is a field at the given position already present.
     *
     * @param   position    the position.
     * @return  true, if there is a field at this position.
     */
    bool isFieldPresent(QPointF const & position) const {
        return isFieldPresent(static_cast<int>(position.x()), static_cast<int>(position.y()));
    }
    
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
    void removeField(int x, int y);
    
    /**
     * Removes a field from the layer
     *
     * @param   position    point holding the field's position.
     */
    void removeField(QPoint position) {
        removeField(position.x(), position.y());
    }
    
    /**
     * Removes a field from the layer
     *
     * @param   position    point holding the field's position.
     */
    void removeField(QPointF position) {
        removeField(static_cast<int>(position.x()), static_cast<int>(position.y()));
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


#endif
