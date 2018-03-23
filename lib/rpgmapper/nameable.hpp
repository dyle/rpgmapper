/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_NAMEABLE_HPP
#define RPGMAPPER_MODEL_NAMEABLE_HPP


#include <QJsonObject>
#include <QString>


namespace rpgmapper {
namespace model {


class Nameable {

    QString name;

public:

    Nameable() = default;

    virtual bool applyJsonObject(QJsonObject const & json);

    virtual void clear() {
        name.clear();
    }

    virtual QJsonObject getJsonObject() const;

    QString const & getName() const {
        return name;
    }

    virtual void setName(QString const & name) {
        this->name = name;
    }
};


}
}


#endif
