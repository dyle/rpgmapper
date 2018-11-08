/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QJsonArray>
#include <QRegExp>

#include "atlas_impl.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


Atlas::Impl::Impl(Atlas * atlas) : atlas(atlas) {
    if (atlas == nullptr) {
        throw std::invalid_argument("rpgmapper::model::Atlas::Impl::Impl() - atlas must not be nullptr.");
    }
    prozessor = QSharedPointer<rpgmapper::model::command::Processor>{new Processor};
    resourceDB = ResourceDBPointer{new ResourceDB};
}


bool Atlas::Impl::applyJSON(QJsonObject const & json) {

    if (!Nameable::applyJSON(json)) {
        return false;
    }
    if (json.contains("regions")) {
        if (!json["regions"].isArray()) {
            return false;
        }
        if (!applyJsonRegionsArray(json["regions"].toArray())) {
            return false;
        }
    }
    return true;
}


bool Atlas::Impl::applyJsonRegionsArray(QJsonArray const & jsonRegions) {

    for (auto && jsonRegion : jsonRegions) {

        if (jsonRegion.toObject().contains("name") && jsonRegion.toObject()["name"].isString()) {
            auto region = createRegion(jsonRegion.toObject()["name"].toString());
            if (!region->applyJSON(jsonRegion.toObject())) {
                return false;
            }
        }
    }
    return true;
}


void Atlas::Impl::clear() {
    Nameable::clear();
    regions.clear();
}


void Atlas::Impl::collectIOContent(rpgmapper::model::io::Content & content) const {
    QJsonDocument json;
    json.setObject(getJSON(content));
    content["atlas.json"] = json.toJson(QJsonDocument::Compact);
}


QSharedPointer<rpgmapper::model::Region> & Atlas::Impl::createRegion(QString const & name) {

    static QSharedPointer<rpgmapper::model::Region> invalidRegion{new InvalidRegion};
    if (regions.find(name) != regions.end()) {
        return invalidRegion;
    }
    auto pair = regions.emplace(std::make_pair(name,
                                               QSharedPointer<rpgmapper::model::Region>{new Region{name, this->atlas},
                                                             &Region::deleteLater}));
    return pair.first->second;
}


QSharedPointer<rpgmapper::model::Map> & Atlas::Impl::findMap(QString const & name) {
    static QSharedPointer<rpgmapper::model::Map> invalidMap{new InvalidMap};
    for (auto & pair : regions) {
        auto & map = pair.second->findMap(name);
        if (map->isValid()) {
            return map;
        }
    }
    return invalidMap;
}


QSharedPointer<rpgmapper::model::Map> const & Atlas::Impl::findMap(QString const & name) const {
    static QSharedPointer<rpgmapper::model::Map> invalidMap{new InvalidMap};
    for (auto & pair : regions) {
        auto & map = pair.second->findMap(name);
        if (map->isValid()) {
            return map;
        }
    }
    return invalidMap;
}


QSharedPointer<rpgmapper::model::Region> & Atlas::Impl::findRegion(QString const & name) {
    static QSharedPointer<rpgmapper::model::Region> invalidRegion{new InvalidRegion};
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return invalidRegion;
    }
    return (*iter).second;
}


QSharedPointer<rpgmapper::model::Region> const & Atlas::Impl::findRegion(QString const & name) const {
    static QSharedPointer<rpgmapper::model::Region> invalidRegion{new InvalidRegion};
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return invalidRegion;
    }
    return (*iter).second;
}


std::set<QString> Atlas::Impl::getAllMapNames() const {

    std::set<QString> allMapNames;
    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&] (auto const & pair) {
                      auto regionMapNames = pair.second->getMapNames();
                      allMapNames.insert(std::begin(regionMapNames), std::end(regionMapNames));
                  });
    return allMapNames;
}


std::set<QString> Atlas::Impl::getAllRegionNames() const {
    std::set<QString> regionNames;
    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&] (auto const & pair) { regionNames.insert(pair.second->getName()); });
    return regionNames;
}


QSharedPointer<rpgmapper::model::command::Processor> & Atlas::Impl::getCommandProzessor() {
    return prozessor;
}


QSharedPointer<rpgmapper::model::command::Processor> const & Atlas::Impl::getCommandProzessor() const {
    return prozessor;
}


QString Atlas::Impl::getInvalidCharactersInName() {
    return R"raw(:\\*\?/)raw";
}


QJsonObject Atlas::Impl::getJSON(rpgmapper::model::io::Content & content) const {

    auto json = Nameable::getJSON(content);

    QJsonArray jsonRegions;
    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&] (auto const & pair) { jsonRegions.append(pair.second->getJSON(content)); });
    json["regions"] = jsonRegions;

    return json;
}


bool Atlas::Impl::isModified() const {
    return getCommandProzessor()->getHistory().size() != unmodifiedCommandCounter;
}


bool Atlas::Impl::isNameValid(QString name) {
    QRegExp regExp{QString{"[%1]"}.arg(getInvalidCharactersInName())};
    return (!name.isEmpty()) && (regExp.indexIn(name) == -1);
}


bool Atlas::Impl::moveMap(QSharedPointer<rpgmapper::model::Map> map, QSharedPointer<rpgmapper::model::Region> regionTo) {

    if (!map->isValid()) {
        return false;
    }
    if (!regionTo->isValid()) {
        return false;
    }

    return regionTo->addMap(map);
}


void Atlas::Impl::readIOContent(rpgmapper::model::io::Content const & content) {
    for (auto const & pair : content) {
        resourceDB->addResource(pair.first, pair.second);
    }
}


bool Atlas::Impl::removeRegion(QString const & name) {
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return false;
    }
    regions.erase(iter);
    return true;
}


void Atlas::Impl::renameRegion(QString nameBefore, QString nameAfter) {
    auto iter = regions.find(nameBefore);
    if (iter != regions.end()) {
        regions[nameAfter] = (*iter).second;
        regions.erase(iter);
    }
}


void Atlas::Impl::resetChanged() {
    unmodifiedCommandCounter = getCommandProzessor()->getHistory().size();
}


void Atlas::Impl::setName(QString const & name) {
    if (getName() == name) {
        return;
    }
    Nameable::setName(name);
}
