/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_background_image.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapBackgroundImage::SetMapBackgroundImage(QString mapName, QImage newImage)
    : mapName{std::move(mapName)}, newImage{std::move(newImage)} {
}


void SetMapBackgroundImage::execute() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        oldImage = map->getBackgroundLayer()->getImage();
        map->getBackgroundLayer()->setImage(newImage);
    }
*/
}


QString SetMapBackgroundImage::getDescription() const {
    return QString{"Set background image of map %1"}.arg(mapName);
}


void SetMapBackgroundImage::undo() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        map->getBackgroundLayer()->setImage(oldImage);
    }
*/
}
