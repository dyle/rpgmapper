/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_SHAPE_TILE_HPP
#define RPGMAPPER_MODEL_TILE_SHAPE_TILE_HPP

#include <rpgmapper/layer/layer_stack.hpp>
#include <rpgmapper/resource/resource_pointer.hpp>
#include <rpgmapper/resource/shape.hpp>
#include <rpgmapper/tile/tile.hpp>


namespace rpgmapper {
namespace model {
namespace tile {

/**
 * A ShapeTile is a tile drawing a shape.
 *
 * Attributes:
 *
 *      "path"     - The resource path used for the shape resource.
 */
class ShapeTile : public Tile {
    
    TileInsertMode insertMode = TileInsertMode::additive;        /**< The insert mode of this tile. */

public:
    
    /**
     * Constructor.
     */
    explicit ShapeTile();
    
    /**
     * Constructor.
     */
    explicit ShapeTile(Attributes & attributes);
    
    /**
     * Equality operator
     *
     * @param   rhs     right hand side
     * @return  true if (*this) == rhs.
     */
    bool operator==(Tile const & rhs) const override;
    
    /**
     * Creates the placer command to place this tile on a map.
     *
     * @param   mapName         the map name to place the tile.
     * @param   position        the position where to place the tile.
     * @return  a placer command which can be executed to place this tile.
     */
    rpgmapper::model::command::CommandPointer createPlacerCommand(QString mapName, QPointF position) const override;
    
    /**
     * Draws the tile.
     *
     * @param   painter         painter used for drawing
     * @param   tileSize        the tile size.
     */
    void draw(QPainter & painter, int tileSize) override;
    
    /**
     * Returns the insert mode of this particular tile when placed on a field.
     *
     * @return  the insert mode enum value of this tile.
     */
    TileInsertMode getInsertMode() const override {
        return insertMode;
    }
    
    /**
     * Gets the resource path to the shape information.
     *
     * @return  the resource path.
     */
    QString getPath() const;
    
    /**
     * Gets the shape attached to this tile.
     *
     * @return  the shape attached to this tile.
     */
    rpgmapper::model::resource::ResourcePointer getShape() const;
    
    /**
     * Determines if the current tile is able to be placed at the map at the given position.
     *
     * @param   map             the map to place the tile on.
     * @param   position        the position to place the tile on the map.
     * @return  true, if the current tile can be placed at this position.
     */
    bool isPlaceable(rpgmapper::model::MapPointer map, QPointF position) const;
    
    /**
     * Places this tile within the layer stack of a map.
     *
     * @param   placed          will be set to true, if the tile has been placed.
     * @param   map             the map to place the tile on.
     * @param   position        the position to place the tile on the map.
     * @return  The list of tiles replaced.
     */
    Tiles place(bool & placed, rpgmapper::model::MapPointer map, QPointF position) override;
    
    /**
     * Removes exactly this tile from a map.
     */
    void remove() const override;
    
private:
    
    
    /**
     * Given a specfic map returns the layer to place this tile on.
     *
     * @param   map     the map.
     * @return  the layer to place the tile on.
     */
    QSharedPointer<rpgmapper::model::layer::TileLayer> & getLayer(rpgmapper::model::MapPointer map) const;
    
    
    /**
     * Prepare the given vector or layers to contain at least the specified number of layers.
     *
     * @param   layers      the layer container.
     * @param   index       the minimum index of layers requested.
     */
    void prepareLayers(std::vector<QSharedPointer<rpgmapper::model::layer::TileLayer>> & layers,
            unsigned int index) const;
    
};


}
}
}


#endif
