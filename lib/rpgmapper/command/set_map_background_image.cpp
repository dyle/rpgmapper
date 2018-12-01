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


SetMapBackgroundImage::SetMapBackgroundImage(QString mapName, QString newImage)
    : mapName{std::move(mapName)}, newImage{std::move(newImage)} {
}


void SetMapBackgroundImage::execute() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    
    oldImage = map->getLayers().getBackgroundLayer()->getImageResource();
    map->getLayers().getBackgroundLayer()->setImageResource(newImage);
}


QString SetMapBackgroundImage::getDescription() const {
    return QString{"Set background image of map %1"}.arg(mapName);
}


void SetMapBackgroundImage::undo() {
    
    auto map = Session::getCurrentSession()->findMap(mapName);
    if (!map->isValid()) {
        throw rpgmapper::model::exception::invalid_map();
    }
    map->getLayers().getBackgroundLayer()->setImageResource(oldImage);
}
