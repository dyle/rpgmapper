/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_HPP

#include <memory>

#include <QJsonObject>
#include <QObject>
#include <QPainter>
#include <QSharedPointer>

#include <rpgmapper/field.hpp>
#include <rpgmapper/resource_db.hpp>
#include <rpgmapper/io/content.hpp>


namespace rpgmapper {
namespace model {


// Forward declaration of Map class.
class Map;


/**
 * A single map is built by Layer objects stacked upon each other.
 *
 * A Layer has a specific purpose: there are base (ground) layers, wall layers, etc.
 * Layers are stacked in a Z-order. The lowest layer will be rendered first.
 */
class Layer : public QObject {

    Q_OBJECT

    class Impl;                                 /**< Implementation class. */
    std::shared_ptr<Impl> impl;                 /**< Pimpl C++ idiom. */

public:

    /**
     * A Layer instance may have an arbitrary set of additional attributes as key-value pairs.
     *
     * E.g. one of the most important attributes of a layer is visibility:
     *      "visible" -> "true"
     */
    using Attributes = std::map<QString, QString>;

    /**
     * Constructs a new Layer.
     *
     * @param   map         the Map instance the layer belongs to.
     * @param   parent      QObject parent.
     */
    explicit Layer(rpgmapper::model::Map * map, QObject * parent = nullptr);

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
    virtual bool applyJsonObject(QJsonObject const & json);

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
    Attributes & getAttributes();

    /**
     * Gets the additional attributes of this layer (const version).
     */
    Attributes const & getAttributes() const;

    /**
     * Extracts the layer as JSON object.
     *
     * @param   content     TODO: why content object?
     * @return  a JSON object holding the layer data.
     */
    virtual QJsonObject getJsonObject(rpgmapper::model::io::Content & content) const;

    /**
     * Gets the resource database used for this layer.
     *
     * @return  the resource database holding all necessary resources for this layer.
     */
    ResourceDBPointer & getResourceDB();

    /**
     * Gets the resource database used for this layer (const version).
     *
     * @return  the const resource database holding all necessary resources for this layer.
     */
    ResourceDBPointer const & getResourceDB() const;

    /**
     * Disables draw/visiblity on next repaint.
     */
    void hide();

    /**
     * Checks the validity of this layer object ("Null object pattern").
     *
     * @return  true, if this is a valid layer.
     */
    virtual bool isValid() const {
        return true;
    }

    /**
     * Checks if the layer would be draw/visible on next repaint.
     *
     * @return  true, if the layer will be drawn next time.
     */
    bool isVisible() const;

    /**
     * Enables draw/visibility on next repaint.
     */
    void show();

protected:

    /**
     * Returns the parent map this layer belongs to.
     *
     * @return  the map this layer belongs to.
     */
    Map * getMap();

    /**
     * Returns the parent map this layer belongs to (const version).
     *
     * @return  the map this layer belongs to.
     */
    Map const * getMap() const;

signals:

    /**
     * A change of the layer's visibility.
     */
    void visibilityChanged();
};


/**
 * An inavalid layer object ("Null object pattern").
 */
class InvalidLayer final : public Layer {

public:

    /**
     * Constructs an invalid layer.
     */
    InvalidLayer()
        : Layer{nullptr, nullptr} {
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
}


#endif
