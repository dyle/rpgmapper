/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_SHAPE_CATALOG_HPP
#define RPGMAPPER_MODEL_RESOURCE_SHAPE_CATALOG_HPP

#include <rpgmapper/resource/resource.hpp>


namespace rpgmapper {
namespace model {
namespace resource {


/**
 * A shape catalog lists known shapes with their names.
 */
class ShapeCatalog : public Resource {
    
    bool valid = false;     /**< Validity flag. */

public:
    
    /**
     * Constructor.
     *
     * @param   name        name of the color palette.
     * @param   data        a JSON structure holding the palette.
     */
    ShapeCatalog(QString name, QByteArray const & data);
    
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
