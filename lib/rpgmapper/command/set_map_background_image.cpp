/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_background_image.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundImage::SetMapBackgroundImage(rpgmapper::model::Map * map, QString newImage)
    : map{map},
      newImage{std::move(newImage)} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapBackgroundImage::execute() {
    oldImage = map->getLayers().getBackgroundLayer()->getImageResource();
    map->getLayers().getBackgroundLayer()->setImageResource(newImage);
}


QString SetMapBackgroundImage::getDescription() const {
    auto mapName = map->getName();
    return QString{"Set background image of map %1"}.arg(mapName);
}


void SetMapBackgroundImage::undo() {
    map->getLayers().getBackgroundLayer()->setImageResource(oldImage);
}
