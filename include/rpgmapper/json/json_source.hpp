/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_JSON_SOURCE_HPP
#define RPGMAPPER_MODEL_JSON_SOURCE_HPP

#include <QJsonObject>


namespace rpgmapper {
namespace model {
namespace json {


/**
 * A JSON source can create a JSON structure holding the properties along their values.
 */
class JSONSource {

public:
    
    
    /**
     * Create a JSON structure from oourselves.
     *
     * @return      a valid JSON  structure from ooourselves.
     */
    virtual QJsonObject getJSON() const = 0;
};


}
}
}


#endif
