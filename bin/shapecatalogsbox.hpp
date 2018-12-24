/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_SHAPECATALOGSBOX_HPP
#define RPGMAPPER_VIEW_SHAPECATALOGSBOX_HPP

#include <QToolBox>
#include <QString>

#include <map>
#include <set>

#include <rpgmapper/resource/shape_catalog.hpp>


namespace rpgmapper {
namespace view {


/**
 * The catalogs of all shapes available.
 */
class ShapeCatalogsBox : public QToolBox {

    Q_OBJECT
    
public:
    
    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit ShapeCatalogsBox(QWidget * parent = nullptr);
    
public slots:
    
    /**
     * The ResourceDB might have changed, setup new shape catalogs.
     */
    void applyResources();
    
    /**
     * Delete all shape catalogs widgets
     */
    void clear();

private:
    
    /**
     * Adds a catalog to the set of known catalogs.
     *
     * @param   catalog     the catalog to add.
     */
    void addCatalog(rpgmapper::model::resource::ShapeCatalog const * catalog);
};


}
}


#endif
