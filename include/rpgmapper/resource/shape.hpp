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


namespace rpgmapper {
namespace model {
namespace resource {


/**
 * A shape is the geometric information which can be drawn on a tile.
 */
class Shape : public Resource {
    
    mutable std::map<unsigned int, QIcon> icons;          /**< The shape icon at a certain scale (tile size). */
    mutable std::map<unsigned int, QImage> images;        /**< The shape image at a certain scale (tile size). */
    mutable std::map<unsigned int, QPixmap> pixmaps;      /**< The shape pixmap at a certain scale (tile size). */
    bool valid = false;                                   /**< Validity flag. */

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
     * Gets the pixmap of this shape at a specific tile size.
     *
     * @param   tileSize        the tile size of the image requested.
     * @return  the shape as QPixmap at the given scale.
     */
    QPixmap getPixmap(unsigned int tileSize) const;
    
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
