/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_COLOR_PALETTE_HPP
#define RPGMAPPER_COLOR_PALETTE_HPP

#include <array>

#include <QByteArray>
#include <QColor>
#include <QJsonDocument>
#include <QString>

#include <rpgmapper/resource.hpp>


namespace rpgmapper {
namespace model {


/**
 * A color palette is has 256 colors.
 */
using Palette = std::array<QColor, 16 *16>;


/**
 * This is the way colors are managed in a palette by rpgmapper.
 */
class ColorPalette : public Resource {
    
    Palette palette;        /**< The color palette managed by this instance. */
    bool valid = false;     /**< Validity flag. */

public:
    
    /**
     * Constructor.
     *
     * @param   name        name of the color palette.
     * @param   data        a JSON structure holding the palette.
     */
    ColorPalette(QString name, QByteArray const & data);
    
    /**
     * Gets the palette managed by this object (const version)
     *
     * @return  the palette managed by this object.
     */
    Palette & getPalette() {
        return palette;
    }
    
    /**
     * Gets the palette managed by this object (const version)
     *
     * @return  the palette managed by this object.
     */
    Palette const & getPalette() const {
        return palette;
    }
    
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
    
    /**
     * Converts this color palette to a JSON representation.
     *
     * @return  a JSON representation of this palette.
     */
    QJsonDocument toJSON() const;
    
private:
    
    /**
     * Loads a palette from the internal byte array data of the resource.
     *
     * The Byte Array should contain a JSON 256 array of colors.
     * If the color palette could not be loaded the isValid() will return false,
     * otherwise true.
     */
    void fromJSON();
};


}
}


#endif
