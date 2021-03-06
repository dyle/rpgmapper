/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_JSON_JSON_SOURCE_HPP
#define RPGMAPPER_MODEL_JSON_JSON_SOURCE_HPP

#include <QJsonObject>


namespace rpgmapper::model::json {


/**
 * A JSON source can create a JSON structure holding the properties along their values.
 */
class JSONSource {

public:
    
    
    /**
     * Create a JSON structure from ourselves.
     *
     * @return      a valid JSON  structure from ourselves.
     */
    virtual QJsonObject getJSON() const = 0;
};


}


#endif
