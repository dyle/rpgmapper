/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_FIELD_HPP
#define RPGMAPPER_MODEL_FIELD_HPP


#include <QJsonObject>

#include <rpgmapper/types.hpp>


namespace rpgmapper {
namespace model {


// TODO: move to field class
Field loadFromJson(QJsonObject const & cJSON);

// TODO: move to field class
QJsonObject saveToJson(Field const & cField);


}
}


#endif
