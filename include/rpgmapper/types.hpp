/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_TYPES_HPP
#define RPGMAPPER_MODEL_TYPES_HPP


#include <QPoint>
#include <QSharedPointer>
#include <QVariant>


namespace rpgmapper {
namespace model {


constexpr int const MAXIMUM_MAP_HEIGHT = 1000;
constexpr int const MAXIMUM_MAP_WIDTH = 1000;
constexpr int const MINIMUM_MAP_HEIGHT = 1;
constexpr int const MINIMUM_MAP_WIDTH = 1;


typedef std::map<QString, QString> Attributes;

class AtlasInstance;
typedef QSharedPointer<AtlasInstance> Atlas;

class Changeable;

class LayerInstance;
typedef QSharedPointer<LayerInstance> Layer;

enum class layer_type {
    background,
    grid,
    tile,
    text
};

typedef int layerid_t;
typedef std::map<layerid_t, Layer> Layers;


class MapInstance;
typedef QSharedPointer<MapInstance> Map;
typedef int mapid_t;
typedef std::map<mapid_t, Map> Maps;

class NameableInstance;
typedef QSharedPointer<NameableInstance> Nameable;

class RegionInstance;
typedef QSharedPointer<RegionInstance> Region;

typedef int regionid_t;
typedef std::map<regionid_t, Region> Regions;


typedef std::map<QString, QString> Tile;
typedef std::vector<Tile> Tiles;


typedef int coordinate_t;

class Field {

    QPoint position;
    Tiles tiles;

public:

    static coordinate_t getCoordinate(QPoint const & position) {
        return (position.y() * MAXIMUM_MAP_WIDTH) + position.x();
    }

    bool isEmpty() const { return tiles.empty(); }
};

typedef std::map<coordinate_t, Field> Fields;


}
}


#endif
