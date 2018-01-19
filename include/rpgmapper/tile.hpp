/*
 * tile.hpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef MODEL_TILE_HPP
#define MODEL_TILE_HPP


// ------------------------------------------------------------
// incs


#include <QJsonObject>

// rpgmapper
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * Load a tile from json.
 *
 * @param   cJSON       the json instance to load from
 */
Tile loadFromJson(QJsonObject const & cJSON);


/**
 * Save a tile to json.
 *
 * @param   cTile       the tile to save
 */
QJsonObject saveToJson(Tile const & cTile);


}
}


#endif
