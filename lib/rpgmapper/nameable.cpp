/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/nameable.hpp>

using namespace rpgmapper::model;


NameableInstance::NameableInstance(QObject * parent) : Changeable{parent} {
}


Nameable NameableInstance::load(QJsonObject const & json) {
    auto nameable = Nameable{new Nameable{}, &NameableInstance::deleteLater};
    if (json.contains("name") && json["name"].isString()) {
        nameable->setName(json["name"].toString());
    }
    return nameable;
}


void NameableInstance::save(QJsonObject & json) const {
    json["name"] = getName();
}


void NameableInstance::setName(QString name) {
    if (this->name != name) {
        this->name = name;
        setModified(true);
        emit changedName();
    }
}
