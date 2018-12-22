/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_BACKGROUND_HPP
#define RPGMAPPER_MODEL_RESOURCE_BACKGROUND_HPP

#include <QByteArray>
#include <QImage>

#include <rpgmapper/resource/resource.hpp>


namespace rpgmapper {
namespace model {
namespace resource {


/**
 * A background is an image drawn at the very lowest layer of a map.
 */
class Background : public Resource {
    
    QImage image;           /**< The background image. */
    bool valid = false;     /**< Validity flag. */

public:
    
    /**
     * Constructor.
     *
     * @param   name        name of the color palette.
     * @param   data        a JSON structure holding the palette.
     */
    Background(QString name, QByteArray const & data);
    
    /**
     * Gets the internal image of the background.
     *
     * @return  the image to draw as background.
     */
    QImage getImage() const {
        return image;
    }
    
    /**
     * Checks if the given data array could contain a background image.
     *
     * @param   data        the data to check.
     * @return  return true, if this data can be treated as a background.
     */
    static bool isBackground(QByteArray const & data);
    
    /**
     * Checks if this ColorPalette is a valid instance.
     *
     * @return  true if this is a valid instance.
     */
    bool isValid() const {
        return valid;
    }
    
    /**
     * Sets a new data to this resource.
     *
     * @param   data        the new data.
     */
    void setData(QByteArray const & data) override;
};


}
}
}


#endif
