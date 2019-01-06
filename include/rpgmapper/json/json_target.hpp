/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_JSON_JSON_TARGET_HPP
#define RPGMAPPER_MODEL_JSON_JSON_TARGET_HPP

#include <QJsonObject>


namespace rpgmapper {
namespace model {
namespace json {


/**
 * A JSON target can apply a JSON to itself by reading values and setting it properly.
 */
class JSONTarget {

public:
    
    /**
     * Applies a JSON to this instance.
     *
     * @param   json    the JSON.
     * @return  true, if the found values in the JSON data has been applied.
     */
    virtual bool applyJSON(QJsonObject const & json) = 0;
};


}
}
}


#endif
