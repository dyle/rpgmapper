/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_SHAPE_CATALOG_HPP
#define RPGMAPPER_MODEL_RESOURCE_SHAPE_CATALOG_HPP

#include <QString>

#include <rpgmapper/resource/resource.hpp>


namespace rpgmapper {
namespace model {
namespace resource {


/**
 * A shape catalog lists known shapes with their names.
 */
class ShapeCatalog : public Resource {
    
    std::map<QString, QString> shapes;      /**< Map of shape name to shape path of this catalog. */
    bool valid = false;                     /**< Validity flag. */

public:
    
    /**
     * Constructor.
     *
     * @param   path        path to the shape catalog resource.
     * @param   data        a JSON structure holding the shape catalog.
     */
    ShapeCatalog(QString path, QByteArray const & data);
    
    /**
     * Returns the catalog base path.
     *
     * E.g. "/shapes/my_shapes/base/my_catalog.json" --> "/shapes/my_shapes/base"
     *
     * @return  the full path without the final path particle.
     */
    QString getCatalogBase() const;
    
    /**
     * Gets the shapes of this catalog.
     *
     * @return  the shapes assigned to this catalog.
     */
    std::map<QString, QString> const & getShapes() const {
        return shapes;
    }
    
    /**
     * Checks if the given data array could contain a shape catalog.
     *
     * @param   data        the data to check.
     * @return  return true, if this data can be treated as a shape catalog.
     */
    static bool isShapeCatalog(QByteArray const & data);
    
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
     * Loads a shape catalog from the internal byte array data of the resource.
     */
    void fromJSON();
};


}
}
}


#endif
