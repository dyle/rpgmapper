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
    TileInsertMode getInsertMode() const override;
    
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
    rpgmapper::model::resource::Shape * getShape() const;
    
    /**
     * Determines if the current tile is able to be placed at the map at the given position.
     *
     * @param   map             the map to place the tile on.
     * @param   position        the position to place the tile on the map.
     * @return  true, if the current tile can be placed at this position.
     */
    bool isPlaceable(rpgmapper::model::Map const * map, QPointF position) const override;
    
    /**
     * Places this tile within the layer stack of a map.
     *
     * @param   replaced        will receive the list of replaced tiles.
     * @param   map             the map to place the tile on.
     * @param   position        the position to place the tile on the map.
     * @return  The tile placed (maybe nullptr if failed to placed the tile).
     */
    TilePointer place(Tiles & replaced, rpgmapper::model::Map * map, QPointF position) override;
    
    /**
     * Removes exactly this tile from a map.
     */
    void remove() const override;
    
private:
    
    /**
     * Given a specific map returns the layer to place this tile on.
     *
     * @param   map     the map.
     * @return  the layer to place the tile on.
     */
    QSharedPointer<rpgmapper::model::layer::TileLayer> & getLayer(rpgmapper::model::Map * map) const;
    
    /**
     * Given a specific map returns the layer to place this tile on.
     *
     * Maybe nullptr if the layer is yet not present on the map.
     *
     * @param   map     the map.
     * @return  the layer to place the tile on.
     */
    QSharedPointer<rpgmapper::model::layer::TileLayer> const & getLayer(rpgmapper::model::Map const * map) const;
    
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
