/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_MAP_HPP
#define RPGMAPPER_MODEL_MAP_HPP


#include <memory>

#include <QJsonObject>
#include <QObject>
#include <QSharedPointer>
#include <QString>

#include <rpgmapper/layer.hpp>


namespace rpgmapper {
namespace model {

class Region;

class Map : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    Map() = delete;

    explicit Map(QString const & name, Region * region = nullptr);

    bool applyJsonObject(QJsonObject const & json);

    LayerPointer const & getBackgroundLayer() const;

    Layers const & getBaseLayers() const;

    LayerPointer const & getGridLayer() const;

    QJsonObject getJsonObject() const;

    QString const & getName() const;

    Region * getRegion();

    Layers const & getTileLayers() const;

    LayerPointer const & getTextLayer() const;

    virtual bool isValid() const { return true; }

    void setName(QString const & name);

signals:

    void changedName();

};


class InvalidMap final : public Map {
public:
    InvalidMap() : Map{QString::Null{}, nullptr} {}
    bool isValid() const override { return false; }
};


using MapPointer = QSharedPointer<Map>;

using Maps = std::map<QString, MapPointer>;


}
}


#endif











#if 0




public:


    /**
     * These are background image render modes.
     */
    enum class map_background_image_render_mode {
        plain = 0,                /**< The background image is rendered plain as-is. */
        scaled = 1,               /**< The background image is rendered to fit the map. */
        tiled = 2                 /**< The background image is tiled across the map. */
    };


    /**
     * These are the corners of origin we support.
     */
    enum class map_corner {
        topLeft = 0,                /**< Origin is top/left. */
        topRight = 1,               /**< Origin is top/right. */
        bottomLeft = 2,             /**< Origin is bottom/left. */
        bottomRight = 3             /**< Origin is bottom/right. */
    };


    /**
     * These are the layers on a map.
     */
    enum class map_layer {
        background = 0,             /**< Background layer. */
        base = 1,                   /**< A layer for all base tiles (e.g. floor, rock, ...). */
        walls = 2,                  /**< A layer for all walls. */
        grid = 3,                   /**< The layer responsible for the map grid. */
        specials = 4,               /**< A layer rendering some special stuff. */
        text = 5                    /**< A layer for positioning text. */
    };


    /**
     * User dimension coordinate.
     */
    struct UserCoordinates {
        QString m_sX;               /**< X coordinate in user space. */
        QString m_sY;               /**< Y coordinate in user space. */
    };


    /**
     * Quick access to the background layer.
     *
     * @return  the background layer
     */
    LayerPointer & backgroundLayer() { return layer(map_layer::background); }


    /**
     * Quick access to the background layer.
     *
     * @return  the background layer
     */
    LayerPointer const & backgroundLayer() const { return layer(map_layer::background); }


    /**
     * Create a new map (factory method).
     *
     * @param   cAtlas      parent object
     * @return  a new map
     */
    static MapPointer create(Atlas * cAtlas);


    /**
     * Quick access to the grid layer.
     *
     * @return  the grid layer
     */
    LayerPointer & gridLayer() { return layer(map_layer::grid); }


    /**
     * Quick access to the grid layer.
     *
     * @return  the grid layer
     */
    LayerPointer const & gridLayer() const { return layer(map_layer::grid); }


    /**
     * Return the id of the map.
     *
     * @return  the id of the map
     */
    mapid_t id() const { return m_nId; }


    /**
     * Get a layer of this map.
     *
     * @param   eLayer      the layer requested
     * @return  the layers of this map
     */
    LayerPointer & layer(map_layer eLayer);


    /**
     * Get a layer of this map.
     *
     * @param   eLayer      the layer requested
     * @return  the layers of this map
     */
    LayerPointer const & layer(map_layer eLayer) const;


    /**
     * Get the layers of this map.
     *
     * @return  the layers of this map
     */
    Layers const & layers() const;


    /**
     * Load the map from json.
     *
     * @param   cJSON       the json instance to load from
     * @param   cAtlas      parent object
     * @return  the loaded map instance
     */
    static MapPointer load(QJsonObject const & cJSON, Atlas * cAtlas);


    /**
     * Means sto order this map among other maps.
     *
     * @return  a value indicating the position of this map among others
     */
    int orderValue() const;


    /**
     * Get the corner of the map's origin.
     *
     * @return  the corner for (0, 0)
     */
    Map::map_corner originCorner() const;


    /**
     * The offest of the origin coordinate.
     *
     * Map coordinates are relative to this offset value.
     *
     * @return  the offset of the origin coordinate on this map
     */
    QPoint const & originOffset() const;


    /**
     * Return the region to which this map belongs to.
     *
     * @return  the region of this map
     */
    RegionPointer const region() const;


    /**
     * Save the map to json.
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const override;


    /**
     * Set the means to order this map among other maps.
     *
     * Map coordinates are relative to this offset value.
     *
     * @param   nOrderValue     a value indicating the position of this maps among others
     */
    void setOrderValue(int nOrderValue);


    /**
     * Set the corner of the map's origin.
     *
     * @param   eCorner         the new map's corner of origin
     */
    void setOriginCorner(Map::map_corner eCorner);


    /**
     * Adjust the offest of the origin coordinate.
     *
     * @param   cOffset         offset of the origin
     */
    void setOriginOffset(QPoint cOffset);


    /**
     * Set the region this map belongs.
     *
     * @param   cRegion     the new region of this map
     */
    void setRegion(RegionPointer & cRegion);


    /**
     * Sets a new size of the map.
     *
     * @param   cSize       the new size of the map
     */
    void setSize(QSize cSize);


    /**
     * Returns the size of the map.
     *
     * @return  the size of the map
     */
    QSize size() const;


    /**
     * Turn map coordinates into user coordinates.
     *
     * @param   x           x-axis value on the map (origin in top/left corner)
     * @param   y           y-axis value on the map (origin in top/left corner)
     * @return  the user coordinates
     */
    UserCoordinates translate(int x, int y) const { return translate(QPoint{x, y}); }


    /**
     * Turn map coordinates into user coordinates.
     *
     * @param   cPoint          the map coordinate
     * @return  the user coordinates
     */
    UserCoordinates translate(QPoint const & cPoint) const;


    /**
     * Translate the X coordinate to the user value.
     *
     * @param   x       x on the map
     * @return  value shown to the user
     */
    QString translateX(int x) const;


    /**
     * Translate the Y coordinate to the user value.
     *
     * @param   y       y on the map
     * @return  value shown to the user
     */
    QString translateY(int y) const;


public slots:


    /**
     * Reset the map to an empty state.
     */
    void clear();


protected:


    /**
     * Load the map from json.
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON) override;


signals:


    /**
     * The map changed its region.
     */
    void changedRegion();


    /**
     * The map changed its order value.
     */
    void changedOrderValue();


    /**
     * The map origin corner has changed.
     */
    void changedOriginCorner();


    /**
     * The map origin offset has changed.
     */
    void changedOriginOffset();


    /**
     * The size of the map has changed.
     */
    void changedSize();


private:


    /**
     * Ctor.
     *
     * @param   cAtlas      parent object
     * @param   nId         id of the map
     */
    explicit Map(Atlas * cAtlas, mapid_t nId);


    /**
     * Adds the standard default layers to the map.
     */
    void createDefaultLayers();


    /**
     * Creates a nice initial state.
     */
    void init();


    mapid_t m_nId;                              /**< Map id. */

    class Map_data;                             /**< Internal data type. */
    std::shared_ptr<Map::Map_data> d;           /**< Internal data instance. */
};


}
}


#endif
