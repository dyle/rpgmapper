/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_SHAPE_CATALOG_POINTER_HPP
#define RPGMAPPER_MODEL_RESOURCE_SHAPE_CATALOG_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper {
namespace model {
namespace resource {


// fwd
class ShapeCatalog;


/**
 * A smart pointer to a shape catalog.
 */
using ShapeCatalogPointer = QSharedPointer<ShapeCatalog>;


}
}
}


#endif
