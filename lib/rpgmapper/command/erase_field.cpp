/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/erase_field.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


EraseField::EraseField(rpgmapper::model::Map * map, QPointF position) : map{map}, position{position} {
}


void EraseField::execute() {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    remove(removedBaseTiles, map->getLayers().getBaseLayers());
    remove(removedTileTiles, map->getLayers().getTileLayers());
}


QString EraseField::getDescription() const {
    
    QString mapName;
    if (map) {
        mapName = map->getName();
    }
    
    return QString{"Erase fields on map %1 at (%2, %3)"}.arg(mapName).arg(position.x()).arg(position.y());
}


void EraseField::remove(std::map<int, rpgmapper::model::tile::Tiles> & backup,
        std::vector<QSharedPointer<rpgmapper::model::layer::TileLayer>> & layers) {

    for (unsigned int i = 0; i < layers.size(); ++i) {
        
        auto & layer = layers[i];
        if (layer->isFieldPresent(position)) {
            auto field = layer->getField(position);
            backup[i] = std::move(field->getTiles());
        }
    }
}


void EraseField::undo() {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
}
