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


namespace rpgmapper {
namespace model {


/**
 * A color palette is has 256 colors.
 */
using Palette = std::array<QColor, 16 *16>;


/**
 * This is the way colors are managed in a palette by rpgmapper.
 */
class ColorPalette {
    
    Palette palette;        /**< The color palette managed by this instance. */
    QString name;           /**< The name of the palette. */
    bool valid = false;     /**< Validity flag. */

public:
    
    /**
     * Constructor.
     */
    ColorPalette() = default;
    
    /**
     * Creates a deep copy of this object.
     *
     * @return  a deep copy of *this.
     */
    ColorPalette clone() const;
    
    /**
     * Returns the name of the palette.
     *
     * @return  the name of the palette.
     */
    QString const & getName() const {
        return name;
    }
    
    /**
     * Gets the palette managed by this object.
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
     * Loads a palette form a byte array.
     *
     * The Byte Array should contain a JSON 256 array of colors.
     */
    static ColorPalette load(QByteArray const & data);
    
    /**
     * Sets the name of the palette.
     *
     * @param   name        the new name of the palette.
     */
    void setName(QString name);
    
    /**
     * Sets the palette of this object.
     *
     * @param   palette     the new palette of this object.
     */
    void setPalette(Palette & palette) {
        this->palette = palette;
        valid = true;
    }
    
    /**
     * Converts this color palette to a JSON representation.
     *
     * @return  a JSON representation of this palette.
     */
    QJsonDocument toJSON() const;
};


}
}


#endif
