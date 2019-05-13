/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <algorithm>
#include <utility>

#include <rpgmapper/exception/invalid_json.hpp>
#include <rpgmapper/nameable.hpp>

using namespace rpgmapper::model;


Nameable::Nameable(QString name) : name{std::move(name)} {
}


void Nameable::applyJson(QJsonObject const & json) {
    
    if (!json.contains("name")) {
        throw rpgmapper::model::exception::invalid_json{"No 'name' defined in json."};
    }

    if (!json["name"].isString()) {
        throw rpgmapper::model::exception::invalid_json{"'name' attribute is not a string."};
    }

    setName(json["name"].toString());
}


void Nameable::clear() {
    auto oldName = name;
    name.clear();
    emit nameChanged(oldName, name);
}


QJsonObject Nameable::getJson() const {
    QJsonObject json;
    json["name"] = name;
    return json;
}


bool Nameable::isValidName(QString const & name) {

    if (name.isEmpty()) {
        return false;
    }

    static QStringList const invalidCharacters = { "'", "\"" };

    return std::any_of(invalidCharacters.begin(),
                       invalidCharacters.end(),
                       [&] (auto s) { return name.contains(s); });
}


void Nameable::setName(QString const & name) {

    if ((name == this->name) || (!isValidName(name))) {
        return;
    }
    auto oldName = this->name;
    this->name = name;
    emit nameChanged(oldName, this->name);
}
