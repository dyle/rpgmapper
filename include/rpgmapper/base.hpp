/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_BASE_HPP
#define RPGMAPPER_MODEL_BASE_HPP

#include <ostream>
#include <string>

#include <QtCore/QByteArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>


namespace rpgmapper::model {


/**
 * The base class of all rpgmapper objects.
 */
class Base {

public:
    
    /**
     * Returns a JSON string of this object by casting it to std::string.
     *
     * @return  a human readable JSON string of this object.
     */
    explicit operator std::string() const {
        QJsonDocument doc{getJson()};
        auto byteArray = doc.toJson(QJsonDocument::JsonFormat::Compact);
        return byteArray.toStdString();
    }

    /**
     * Applies a state defined in the given JSON to this object.
     *
     * @param   json        the state to apply to this object.
     */
    virtual void applyJson(QJsonObject const & json) = 0;


    /**
     * Returns the state of this object as JSON.
     *
     * @return  a string describing the current object state in json.
     */
    virtual QJsonObject getJson() const = 0;
};


}


/**
 * Stream a base rpgmapper object.
 *
 * @param   s       the out stream instance.
 * @param   o       the object to stream
 */
inline std::ostream & operator<<(std::ostream & s, rpgmapper::model::Base const & o) {
    return s << std::string{o};
}


#endif
