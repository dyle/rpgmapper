/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_HPP


#include <memory>

#include <QObject>
#include <QSharedPointer>


namespace rpgmapper {
namespace model {


class Map;


class Layer : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    using Attributes = std::map<QString, QString>;

    explicit Layer(Map * map, QObject * parent = nullptr);

    Attributes & getAttributes();

    Attributes const & getAttributes() const;

    virtual bool isValid() const { return true; }

};


class InvalidLayer final : public Layer {

public:

    InvalidLayer() : Layer{nullptr, nullptr} {}

    bool isValid() const override { return false; }

};


}
}

#endif
















#if 0


#include <memory>

#include <QPainter>

#include <rpgmapper/nameable.hpp>
#include <rpgmapper/types.hpp>


namespace rpgmapper {
namespace model {


class Layer : public Nameable {

    Q_OBJECT

    class Impl;
    std::unique_ptr<Layer::Impl> d;

public:


    /**
     * Get the attributes of this layer.
     *
     * @return  the attributes of this layer.
     */
    //std::map<QString, QString> & attributes();


    /**
     * Get the attributes of this layer.
     *
     * @return  the attributes of this layer.
     */
    //std::map<QString, QString> const & attributes() const;


    /**
     * Clears and empties a field.
     *
     * @param   nCoordinate     the coordinate of the field
     */
    //void clearField(coordinate_t nCoordinate);


    /**
     * Clears and empties a field.
     *
     * @param   cPosition       the position of the field
     */
    //void clearField(QPoint const & cPosition) { clearField(Field::coordinate(cPosition)); }


    static LayerPointer create(MapPointer map, layer_type eLayer);


    /**
     * Draw the current layer given the painter.
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    //void draw(QPainter & cPainter, int nTileSize) const;


    /**
     * Get one field on this layer.
     *
     * @param   nCoordinate         the field's coordinate value
     * @return  the field requested
     */
    //Field const & getField(coordinate_t nCoordinate) const;


    /**
     * Get one field on this layer.
     *
     * @param   cPosition           the position of the field
     * @return  the field requested
     */
    //Field const & getField(QPoint const & cPosition) const  { return getField(Field::coordinate(cPosition)); }


    /**
     * Get all the map items of this layer.
     *
     * @return  all tiles on this layer
     */
    //Fields const & fields() const;


    /**
     * Return the id of the layer.
     *
     * @return  the id of the layer
     */
    //layerid_t id() const { return m_nId; }


    /**
     * Load the layer from json.
     *
     * @param   cJSON       the json instance to load from
     */
    //void load(QJsonObject const & cJSON) override;


    /**
     * Save the layer to json.
     *
     * @param   cJSON       the json instance to save to
     */
    //void save(QJsonObject & cJSON) const override;


    /**
     * Checks if the tiles on this layer are stackable.
     *
     * Stackable tiles can be piled up on the very same field.
     * If the tiles are not stackable, then there can be only
     * one tile per field.
     *
     * @return  true, if there can be multiple tiles per field
     */
    //bool stackable() const;


    /**
     * Get the type of the layer.
     *
     * @return  the layer type enum value.
     */
    //layer_t type() const { return m_eLayer; }


public slots:


    /**
     * Reset the map to an empty state.
     */
    //void clear();


protected:


    /**
     * Ctor.
     *
     * @param   cMap        parent object
     * @param   nId         id of the layer
     * @param   eLayer      the layer type
     */
    //explicit Layer(Map * cMap, layerid_t nId, layer_t eLayer);


    /**
     * The map associated with this layer.
     *
     * @return  a pointer to the map
     */
    //Map * const & map() const;


private:


    /**
     * Draw the current layer given the painter.
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    //virtual void drawLayer(QPainter & cPainter, int nTileSize) const = 0;


};


}
}


#endif
