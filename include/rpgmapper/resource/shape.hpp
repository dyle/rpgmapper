/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_SHAPE_HPP
#define RPGMAPPER_MODEL_RESOURCE_SHAPE_HPP

#include <map>

#include <QIcon>
#include <QImage>
#include <QPixmap>

#include <rpgmapper/resource/resource.hpp>
#include <rpgmapper/tile/tile_insert_modes.hpp>


namespace rpgmapper {
namespace model {
namespace resource {


/**
 * A shape is the geometric information which can be drawn on a tile.
 *
 * A shape is an SVG information. This SVG is targeted on a specific map layer (base or tile layer)
 * and at a target Z-ordering position.
 *
 * Shapes with a high Z-Order number are drawn above shapes with a lower number. However, the
 * Z-order number is capped at a maximum of getMaxZOrder().
 */
class Shape : public Resource {

public:
    
    /**
     * Different target layers for this tile.
     */
    enum class TargetLayer {
        unknown,                /**< Unknown target layer for this shape. */
        base,                   /**< The shape ought to be placed at the base layer. */
        tile                    /**< The shape ought to be placed at the tile layer. */
    };
    
private:
    
    mutable std::map<unsigned int, QIcon> icons;          /**< The shape icon at a certain scale (tile size). */
    mutable std::map<unsigned int, QImage> images;        /**< The shape image at a certain scale (tile size). */
    mutable std::map<unsigned int, QPixmap> pixmaps;      /**< The shape pixmap at a certain scale (tile size). */
    
    TargetLayer targetLayer = TargetLayer::tile;          /**< Where to place this shape. */
    unsigned int zOrdering = 0;                           /**< Z-Order position of the shape in the target layer. */
    
    bool valid = false;                                   /**< Validity flag. */
    
    rpgmapper::model::tile::TileInsertMode insertMode;    /**< Insert mode of tile based on this shape. */

public:
    
    /**
     * Constructor.
     *
     * @param   path        path to the shape resource.
     * @param   data        a JSON structure holding the shape catalog.
     */
    Shape(QString path, QByteArray const & data);
    
    /**
     * Gets the icon of this shape at a specific tile size.
     *
     * @param   tileSize        the tile size of the image requested.
     * @return  the shape as QIcon at the given scale.
     */
    QIcon getIcon(unsigned int tileSize) const;
    
    /**
     * Gets the image of this shape at a specific tile size.
     *
     * @param   tileSize        the tile size of the image requested.
     * @return  the shape as QImage at the given scale.
     */
    QImage getImage(unsigned int tileSize) const;
    
    /**
     * Gets the insert mode of tiles based on this shape.
     *
     * @return  the insert mode of tiles of this shape.
     */
    rpgmapper::model::tile::TileInsertMode getInsertMode() const {
        return insertMode;
    }
    
    /**
     * Maximum Z order value for shapes.
     *
     * @return  the maximum z-value for shapes.
     */
    constexpr static unsigned int getMaxZOrder() {
        return 5;
    }
    
    /**
     * Gets the pixmap of this shape at a specific tile size.
     *
     * @param   tileSize        the tile size of the image requested.
     * @return  the shape as QPixmap at the given scale.
     */
    QPixmap getPixmap(unsigned int tileSize) const;
    
    /**
     * Gets the target layer of the shape.
     *
     * @return  the layer at which this shape ought to be drawn.
     */
    TargetLayer getTargetLayer() const {
        return targetLayer;
    }
    
    /**
     * Gets the Z-ordering of the shape.
     *
     * @return  the Z-Ordering of the shape.
     */
    unsigned int getZOrdering() const {
        return zOrdering;
    }
    
    /**
     * Checks if the given data array could contain a shape.
     *
     * @param   data        the data to check.
     * @return  return true, if this data can be treated as a shape.
     */
    static bool isShape(QByteArray const & data);
    
    /**
     * Checks if this ColorPalette is a valid instance.
     *
     * @return  true if this is a valid instance.
     */
    bool isValid() const override {
        return valid;
    }
    
    /**
     * Sets a new data to this resource.
     *
     * @param   data        the new data.
     */
    void setData(QByteArray const & data) override;
    
    /**
     * Applies a new insert mode for tiles based on this shape.
     *
     * @param   insertMode      the new insert mode for tiles on this shape.
     */
    void setInsertMode(rpgmapper::model::tile::TileInsertMode insertMode) {
        this->insertMode = insertMode;
    }
    
    /**
     * Sets the target layer of the shape.
     *
     * @param   targetLayer         the new target layer of the shape.
     */
    void setTargetLayer(TargetLayer layer) {
        targetLayer = layer;
    }
    
    /**
     * Sets a new z ordering.
     *
     * @param   z       the new Z Ordering of the shape.
     */
    void setZOrdering(unsigned int z) {
        zOrdering = std::min(z, getMaxZOrder());
    }
    
    /**
     * Converts a string to a TargetLayer enum value.
     *
     * @param   layer       the layer as string.
     * @return  the identified target layer.
     */
    static TargetLayer targetLayerFromString(QString layer);
    
private:
    
    /**
     * Adds the rendered drawings of this shape to the internal cache.
     *
     * @param   tileSize        the length of the square.
     * @param   image           the QImage of the shape at the given size.
     * @param   pixmap          the QPixmap of the shape at the given size.
     * @param   icon            the QIcon of the shape at the given size.
     */
    void addCache(unsigned int tileSize, QImage image, QPixmap pixmap, QIcon icon) const;
    
    /**
     * Adds the drawings (icon, image and pixmap) of the shape at the given tile size.
     *
     * @param   tileSize        the length of the square to draw.
     */
    void prepare(unsigned int tileSize) const;
    
    /**
     * Renders the shape on an image of the given square with length tileSize.
     *
     * @param   tileSize        the length of the square.
     * @return  an image holding the shape at the given square size.
     */
    QImage render(unsigned int tileSize) const;
};


}
}
}


#endif
