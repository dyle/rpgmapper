/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_RESOURCE_TYPE_HPP
#define RPGMAPPER_RESOURCE_TYPE_HPP

#include <QString>


namespace rpgmapper {
namespace model {


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


}
}


#endif
