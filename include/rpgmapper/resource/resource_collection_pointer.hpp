/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_RESOURCE_COLLECTION_POINTER_HPP
#define RPGMAPPER_MODEL_RESOURCE_RESOURCE_COLLECTION_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper {
namespace model {
namespace resource {


// fwd
class ResourceCollection;


/**
 * A smart pointer to a resource database.
 */
using ResourceCollectionPointer = QSharedPointer<ResourceCollection>;


}
}
}


#endif
