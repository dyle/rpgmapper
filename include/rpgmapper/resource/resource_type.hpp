/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_RESOURCE_TYPE_HPP
#define RPGMAPPER_MODEL_RESOURCE_RESOURCE_TYPE_HPP

#include <QString>


namespace rpgmapper {
namespace model {
namespace resource {


/**
 * Well known resources types.
 */
enum class ResourceType {
    unknown,                /**< Not a known resource type. */
    background,             /**< A background. */
    colorpalette,           /**< A colorpalette. */
    shape                   /**< A shape. */
};


/**
 * Returns the commonly used prefix for the given type.
 *
 * @param   type        the resource type.
 * @return  the path prefix to use for this type.
 */
QString getResourcePrefixForType(ResourceType type);


/**
 * Gets a human readable name for the resource.
 *
 * @param   type        the resource type.
 * @param   plural      if true, plural names are returned.
 * @return  a human readable name for the resource type.
 */
QString getResourceTypeName(ResourceType type, bool plural);


/**
 * Detect resource type by the given path.
 *
 * @param   path        the path of the resource.
 * @return  the detected resource type based on the path prefix.
 */
ResourceType suggestResourceTypeByPath(QString path);


}
}
}


#endif
