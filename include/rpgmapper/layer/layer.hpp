/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_LAYER_HPP

#include <map>

#include <QJsonObject>
#include <QObject>
#include <QPainter>
#include <QString>

#include <rpgmapper/json/json_io.hpp>


// fwd
namespace rpgmapper::model { class Map; }


namespace rpgmapper::model::layer {


/**
 * A single map is built by Layer objects stacked upon each other.
 *
 * A Layer has a specific purpose: there are base (ground) layers, wall layers, etc.
 * Layers are stacked in a Z-order. The lowest layer will be rendered first.
 */
class Layer : public QObject, public json::JSONIO {

    Q_OBJECT
    
public:
    
    /**
     * A Layer instance may have an arbitrary set of additional attributes as key-value pairs.
     */
    using Attributes = std::map<QString, QString>;
    
private:
    
    Attributes attributes;          /**< The attributes of the current Layer. */
    rpgmapper::model::Map * map;    /**< The map this layer belongs to. */

public:

    /**
     * Constructs a new Layer.
     *
     * @param   map     the map this layer belongs to.
     */
    explicit Layer(rpgmapper::model::Map * map);

    /**
     * Destructs the object.
     */
    ~Layer() override = default;

    /**
     * Extract the layer information in the given JSON object and apply it to this layer.
     *
     * @param   json        The JSON object which maybe hold some information.
     * @return  always true (TODO: why? kick this! Unnecessary)
     */
    bool applyJSON(QJsonObject const & json) override;

    /**
     * Draws the layer using the given painter and a certain tile size.
     *
     * @param   painter     the painter used for drawing.
     * @param   tileSize    the size of a single tile square side in pixels.
     */
    virtual void draw(QPainter & painter, int tileSize) const = 0;

    /**
     * Gets the additional attributes of this layer.
     */
    Attributes & getAttributes() {
        return attributes;
    }

    /**
     * Gets the additional attributes of this layer (const version).
     */
    Attributes const & getAttributes() const {
        return attributes;
    }

    /**
     * Extracts the layer as JSON object.
     *
     * @return  a JSON object holding the layer data.
     */
    QJsonObject getJSON() const override;
    
    /**
     * Get the map the layer belongs to.
     *
     * @return  the map the layer belongs to.
     */
    rpgmapper::model::Map * getMap() {
        return map;
    }
    
    /**
     * Get the map the layer belongs to (const version)
     *
     * @return  the map the layer belongs to.
     */
    rpgmapper::model::Map const * getMap() const {
        return map;
    }
    
    /**
     * Checks the validity of this layer object ("Null object pattern").
     *
     * @return  true, if this is a valid layer.
     */
    virtual bool isValid() const {
        return true;
    }

    /**
     * Sets a new parent map.
     *
     * @parant  map     the new parent map.
     */
    void setMap(rpgmapper::model::Map * map);
};


/**
 * An inavalid layer object ("Null object pattern").
 */
class InvalidLayer final : public Layer {

public:

    /**
     * Constructs an invalid layer.
     */
    InvalidLayer() : Layer{nullptr} {
    }

    /**
     * Declares this layer to be invalid.
     *
     * @return  always false.
     */
    bool isValid() const override {
        return false;
    }
};


}


#endif
