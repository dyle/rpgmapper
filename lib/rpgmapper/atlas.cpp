/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


//#include <sstream>

//#include <QJsonArray>
//#include <QTextCodec>

#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;


namespace rpgmapper {
namespace model {


class Atlas::Impl final {

    Atlas * atlas = nullptr;
    bool changed = false;
    QString name;
    Regions regions;

public:

    Impl(Atlas * atlas);

    Impl(Impl const &) = delete;

    RegionPointer createRegion(QString const & name);

    QString const & getName() const { return name; }

    Regions const & getRegions() const { return regions; }

    bool hasChanged() const { return changed; }

    bool removeRegion(QString const & name);

    void setName(QString const & name);

};


}
}


Atlas::Impl::Impl(Atlas * atlas) : atlas(atlas), name{QObject::tr("New Atlas")} {
    if (atlas == nullptr) {
        throw std::invalid_argument("rpgmapper::model::Atlas::Impl::Impl() - atlas must not be nullptr.");
    }
    auto region = createRegion(QObject::tr("New Region 1"));
    region->createMap(QObject::tr("New Map 1"));
    changed = false;
}


RegionPointer Atlas::Impl::createRegion(QString const & name) {
    if (regions.find(name) != regions.end()) {
        return RegionPointer{new InvalidRegion};
    }
    auto pair = regions.emplace(std::make_pair(name, RegionPointer{new Region{name, this->atlas}, &Region::deleteLater}));
    changed = true;
    return pair.first->second;
}


bool Atlas::Impl::removeRegion(QString const & name) {
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        return false;
    }
    regions.erase(iter);
    changed = true;
    return true;
}


void Atlas::Impl::setName(QString const & name) {
    if (this->name == name) {
        return;
    }
    this->name = name;
    changed = true;
}


Atlas::Atlas(QObject * parent) : QObject{parent} {
    impl = std::make_shared<Atlas::Impl>(this);
}


RegionPointer Atlas::createRegion(QString const & name) {
    bool hasAlreadyChanged = impl->hasChanged();
    auto region = impl->createRegion(name);
    if (region->isValid()) {
        emit regionAdded(name);
        if (!hasAlreadyChanged) {
            emit changed();
        }
    }
    return region;
}


QString const & Atlas::getName() const {
    return impl->getName();
}


Regions const & Atlas::getRegions() const {
    return impl->getRegions();
}


bool Atlas::hasChanged() const {
    return impl->hasChanged();
}


void Atlas::removeRegion(QString const & name) {

    bool hasAlreadyChanged = impl->hasChanged();
    if (impl->removeRegion(name)) {
        emit regionRemoved(name);
        if (!hasAlreadyChanged) {
            emit changed();
        }
    }
}


void Atlas::setName(QString const & name) {
    bool hasAlreadyChanged = impl->hasChanged();
    impl->setName(name);
    if (impl->hasChanged() && !hasAlreadyChanged) {
        emit changed();
    }
}









#if 0

/**
 * Reset the atlas to an empty state.
 */
void Atlas::clear() {
    setName("");
    d->m_cMaps.clear();
    d->m_cRegions.clear();
    setModified(true);
}


/**
 * Creates a new map to this atlas.
 *
 * @return  a reference to the new map
 */
MapPointer Atlas::createMap() {

    auto cMap = Map::create(this);
    connect(cMap.data(), &Map::changedName, this, &Atlas::mapChangedName);

    d->m_cMaps.insert(std::make_pair(cMap->id(), cMap));
    cMap->setRegion(currentRegion());

    emit newMap(cMap->id());
    emit changedAtlas();

    return cMap;
}


/**
 * Creates a new region to this atlas.
 *
 * @return  a reference to the new region
 */
RegionPointer Atlas::createRegion() {

    auto cRegion = Region::create(this);
    connect(cRegion.data(), &Region::changedName, this, &Atlas::regionChangedName);

    d->m_cRegions.insert(std::make_pair(cRegion->id(), cRegion));
    emit newRegion(cRegion->id());
    emit changedAtlas();

    return cRegion;
}


/**
 * Returnes the currenty selected Map.
 *
 * @return  the map which is currently selected
 */
MapPointer & Atlas::currentMap() {
    return d->m_cCurrentMap;
}


/**
 * Returns the currently selected Region.
 *
 * @return  the region which is currently selected
 */
RegionPointer & Atlas::currentRegion() {
    return d->m_cCurrentRegion;
}


/**
 * Deletes a map.
 *
 * @param   nMapId          the map to delete
 */
void Atlas::deleteMap(rpgmapper::model::mapid_t nMapId) {

    auto nCurrentMapId = d->m_cCurrentMap.data() != nullptr ? d->m_cCurrentMap->id() : -1;
    auto cMap = mapById(nMapId);
    if (cMap.data() == nullptr) {
        return;
    }

    auto cRegion = cMap->region();
    if (cRegion.data() != nullptr) {
        cRegion->removeMap(nMapId);
    }

    d->m_cMaps.erase(nMapId);

    if (nCurrentMapId == nMapId) {
        d->m_cCurrentMap = MapPointer(nullptr);
        emit selectedMap(-1);
    }

    emit deletedMap(nMapId);
    emit changedAtlas();
}


/**
 * Deletes a region.
 *
 * @param   nRegionId       the region to delete
 */
void Atlas::deleteRegion(rpgmapper::model::regionid_t nRegionId) {

    auto nCurrentRegionId = d->m_cCurrentRegion.data() != nullptr ? d->m_cCurrentRegion->id() : -1;
    auto cRegion = regionById(nRegionId);
    if (cRegion.data() == nullptr) {
        return;
    }

    for (auto cPair : cRegion->maps()) {
        cRegion->removedMap(cPair.second->id());
    }

    d->m_cRegions.erase(nRegionId);

    if (nCurrentRegionId == nRegionId) {
        d->m_cCurrentRegion = RegionPointer(nullptr);
        emit selectedRegion(-1);
    }

    emit deletedRegion(nRegionId);
    emit changedAtlas();
}


/**
 * Dumps the current atlas structure to a string.
 *
 * @return  a string describing the current structure
 */
std::string Atlas::dumpStructure() const {

    std::stringstream ss;

    ss << "Atlas {'" << name().toStdString() << "}\n";

    for (auto const & cRegionPair : d->m_cRegions) {

        ss << "+-- Region {'" << cRegionPair.second->name().toStdString() << "' "
           << "[" << cRegionPair.second->id() << "]}\n";

        for (auto const & cMapPair : d->m_cMaps) {

            ss << "    +-- Map {'" << cMapPair.second->name().toStdString() << "' "
               << "[" << cMapPair.second->id() << "]}\n";
        }
    }

    return ss.str();
}


/**
 * Create a json string form this atlas.
 *
 * @param   eJsonFormat     the format for representation
 * @return  a string holding the atlas in json format
 */
QString Atlas::json(QJsonDocument::JsonFormat eJsonFormat) const {

    QJsonObject cJSON;
    save(cJSON);

    QJsonDocument cJSONDoc{cJSON};
    return QTextCodec::codecForName("UTF-8")->toUnicode(cJSONDoc.toJson(eJsonFormat).data());
}


/**
 * Load the atlas from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Atlas::load(QJsonObject const & cJSON) {

    clear();
    Nameable::load(cJSON);

    if (cJSON.contains("maps") && cJSON["maps"].isArray()) {
        QJsonArray cJSONMaps = cJSON["maps"].toArray();
        for (auto && cJSONMap : cJSONMaps) {
            auto cMap = Map::load(cJSONMap.toObject(), this);
            d->m_cMaps[cMap->id()] = cMap;
            connect(cMap.data(), &Map::changedName, this, &Atlas::mapChangedName);
        }
    }

    if (cJSON.contains("regions") && cJSON["regions"].isArray()) {
        QJsonArray cJSONRegions = cJSON["regions"].toArray();
        for (auto &&cJSONRegion : cJSONRegions) {
            auto cRegion = Region::load(cJSONRegion.toObject(), this);
            d->m_cRegions[cRegion->id()] = cRegion;
            connect(cRegion.data(), &Region::changedName, this, &Atlas::regionChangedName);
        }
    }

    setModified(false);
}


/**
 * Provide some nice initial state.
 */
void Atlas::init() {

    clear();

    setName("New Atlas");
    auto cRegion = createRegion();
    setCurrentRegion(cRegion->id());

    auto cMap = createMap();
    cRegion->addMap(cMap);
    setCurrentMap(cMap->id());

    setModified(false);
}


/**
 * State if the atlas (and any descendants) has changed.
 *
 * @return  true, if the atlas (or any descendants) has changed.
 */
bool Atlas::isModified() const {

    if (Nameable::isModified()) {
        return true;
    }

    if (std::any_of(maps().begin(),
                    maps().end(),
                    [](Maps::value_type const & cPair) { return cPair.second->isModified(); })) {
        return true;
    }

    return std::any_of(regions().begin(),
                       regions().end(),
                       [](Regions::value_type const & cPair) { return cPair.second->isModified(); });
}


/**
 * Get a map based on an Id.
 *
 * Hence, if the map has not been found, a MapPointer
 * with data() == nullptr is returned,
 *
 * @param   nMapId          id of the map
 * @return  a smart map pointer
 */
MapPointer & Atlas::mapById(rpgmapper::model::mapid_t nMapId) {

    static MapPointer cNullMap{nullptr};

    auto iter = d->m_cMaps.find(nMapId);
    if (iter == d->m_cMaps.end()) {
        return cNullMap;
    }
    return (*iter).second;
}


/**
 * Get a map based on an Id.
 *
 * Hence, if the map has not been found, a MapPointer
 * with data() == nullptr is returned,
 *
 * @param   nMapId          id of the map
 * @return  a smart map pointer
 */
MapPointer const & Atlas::mapById(rpgmapper::model::mapid_t nMapId) const {

    static MapPointer cNullMap{nullptr};

    auto iter = d->m_cMaps.find(nMapId);
    if (iter == d->m_cMaps.end()) {
        return cNullMap;
    }
    return (*iter).second;
}


/**
 * A map has changed its name.
 */
void Atlas::mapChangedName() {
    auto cMap = dynamic_cast<Map *>(sender());
    if (cMap != nullptr) {
        emit changedMapName(cMap->id());
        emit changedAtlas();
    }
}


/**
 * Return all the maps managed by this atlas.
 *
 * @return  all maps of this atlas
 */
Maps const & Atlas::maps() const {
    return d->m_cMaps;
}


/**
 * Get a region based on an Id.
 *
 * Hence, if the region has not been found, a RegionPointer
 * with data() == nullptr is returned,
 *
 * @param   nRegionId       id of the region
 * @return  a smart region pointer
 */
RegionPointer & Atlas::regionById(rpgmapper::model::regionid_t nRegionId) {

    static RegionPointer cNullRegion{nullptr};

    auto iter = d->m_cRegions.find(nRegionId);
    if (iter == d->m_cRegions.end()) {
        return cNullRegion;
    }
    return (*iter).second;
}


/**
 * Get a region based on an Id.
 *
 * Hence, if the region has not been found, a RegionPointer
 * with data() == nullptr is returned,
 *
 * @param   nRegionId       id of the region
 * @return  a smart region pointer
 */
RegionPointer const & Atlas::regionById(rpgmapper::model::regionid_t nRegionId) const {

    static RegionPointer cNullRegion{nullptr};

    auto iter = d->m_cRegions.find(nRegionId);
    if (iter == d->m_cRegions.end()) {
        return cNullRegion;
    }
    return (*iter).second;
}


/**
 * A region has changed its name.
 */
void Atlas::regionChangedName() {
    auto cRegion = dynamic_cast<Region *>(sender());
    if (cRegion != nullptr) {
        emit changedRegionName(cRegion->id());
        emit changedAtlas();
    }
}


/**
 * Return all the regions managed by this atlas.
 *
 * @return  all regions of this atlas
 */
Regions const & Atlas::regions() const {
    return d->m_cRegions;
}


/**
 * Save the atlas to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Atlas::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    QJsonArray cJSONRegions;
    for (auto const & cRegion: d->m_cRegions) {
        QJsonObject cJSONRegion;
        cRegion.second->save(cJSONRegion);
        cJSONRegions.append(cJSONRegion);
    }
    cJSON["regions"] = cJSONRegions;

    QJsonArray cJSONMaps;
    for (auto const & cMap: d->m_cMaps) {
        QJsonObject cJSONMap;
        cMap.second->save(cJSONMap);
        cJSONMaps.append(cJSONMap);
    }
    cJSON["maps"] = cJSONMaps;
}

/**
 * Set a new map as selected.
 * An invalid id (e.g. -1) will select no map.
 *
 * @param   nMapId      the map selected
 */
void Atlas::setCurrentMap(rpgmapper::model::mapid_t nMapId) {
    
    auto iter = d->m_cMaps.find(nMapId);
    if (iter != d->m_cMaps.end()) {
        d->m_cCurrentMap = (*iter).second;
        setCurrentRegion(d->m_cCurrentMap->region()->id());
    }
    else {
        d->m_cCurrentMap = nullptr;
    }

    emit selectedMap(nMapId);
}


/**
 * Select a new region.
 * An invalid id (e.g. -1) will select no region.
 *
 * @param   nRegionId   the region selected
 */
void Atlas::setCurrentRegion(rpgmapper::model::regionid_t nRegionId) {

    auto iter = d->m_cRegions.find(nRegionId);
    if (iter != d->m_cRegions.end()) {
        d->m_cCurrentRegion = (*iter).second;
    }
    else {
        d->m_cCurrentRegion = nullptr;
    }

    emit selectedRegion(nRegionId);
}


/**
 * Set the atlas and all descendants to a new modification state.
 * Only applies "true" to the current item and not to all maps and regions.
 *
 * @param   bModified       the new modification state
 */
void Atlas::setModified(bool bModified) {

    Nameable::setModified(bModified);

    if (!bModified) {

        std::for_each(d->m_cMaps.begin(),
                      d->m_cMaps.end(),
                      [&] (Maps::value_type & cPair) { cPair.second->setModified(bModified); });

        std::for_each(d->m_cRegions.begin(),
                      d->m_cRegions.end(),
                      [&] (Regions::value_type & cPair) { cPair.second->setModified(bModified); });
    }

    emit changedAtlas();
}
#endif
