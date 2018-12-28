#include <utility>

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/tile/tile.hpp>

using namespace rpgmapper::model::tile;


/**
 * Normalize a degree value.
 *
 * @param   degree      input degree.
 * @return  a degree value in the range of 0.0 - 360.0
 */
static double normalizeDegree(double degree);


Tile::Tile() {
    initAttributes();
}


Tile::Tile(Tile::Attributes & attributes) : attributes{attributes} {
}


double Tile::getRotation() const {
    
    auto pair = attributes.find("rotation");
    if (pair == attributes.end()) {
        return 0.0;
    }
    return (*pair).second.toDouble();
}


double Tile::getStretch() const {
    
    auto pair = attributes.find("stretch");
    if (pair == attributes.end()) {
        return 1.0;
    }
    return (*pair).second.toDouble();
}


QString Tile::getType() const {
    
    auto const & attributes = getAttributes();
    auto iter = attributes.find("type");
    if (iter == attributes.end()) {
        return QString::null;
    }
    return (*iter).second;
}


void Tile::initAttributes() {
    getAttributes()["rotation"] = "0.0";
    getAttributes()["stretch"] = "1.0";
}


void Tile::rotateLeft() {
    auto rotation = getRotation() - 90.0;
    rotation = normalizeDegree(rotation);
    getAttributes()["rotation"] = QString::number(rotation);
}


void Tile::rotateRight() {
    auto rotation = getRotation() + 90.0;
    rotation = normalizeDegree(rotation);
    getAttributes()["rotation"] = QString::number(rotation);
}


void Tile::setMap(rpgmapper::model::MapPointer map) {
    this->map = std::move(map);
}


void Tile::setPosition(QPointF position) {
    this->position = position;
}


double normalizeDegree(double degree) {
    
    while (degree < 0) {
        degree += 360.0;
    }
    while (degree >= 360.0) {
        degree -= 360.0;
    }
    return degree;
}
