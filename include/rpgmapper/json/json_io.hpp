/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_JSON_JSON_IO_HPP
#define RPGMAPPER_MODEL_JSON_JSON_IO_HPP

#include <rpgmapper/json/json_source.hpp>
#include <rpgmapper/json/json_target.hpp>


namespace rpgmapper::model::json {


/**
 * This class is capable of writing and reading JSON.
 */
class JSONIO : public JSONSource, public JSONTarget {
};


}


#endif
