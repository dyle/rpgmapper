/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_SHAPE_HPP
#define RPGMAPPER_MODEL_RESOURCE_SHAPE_HPP

#include <rpgmapper/resource/resource.hpp>


namespace rpgmapper {
namespace model {
namespace resource {


/**
 * A shape is the geometric information which can be drawn on a tile.
 */
class Shape : public Resource {
    
    bool valid = false;     /**< Validity flag. */

public:
    
    /**
     * Constructor.
     *
     * @param   name        name of the color palette.
     * @param   data        a JSON structure holding the palette.
     */
    Shape(QString name, QByteArray const & data);
    
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
