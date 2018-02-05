/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// ------------------------------------------------------------
// defs


#ifndef MODEL_LAYER_BACKGROUND_HPP
#define MODEL_LAYER_BACKGROUND_HPP


// ------------------------------------------------------------
// incs

// rpgmapper
#include <rpgmapper/layer.hpp>
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A layer on a map.
 */
class BackgroundLayer : public Layer {


    Q_OBJECT


public:


    /**
     * Ctor.
     *
     * @param   cMap        parent object
     * @param   nId         id of the layer
     */
    explicit BackgroundLayer(Map * cMap, layerid_t nId);


private:


    /**
     * Retrieve the background color.
     *
     * @return  the color encoded in the tiles of this layer
     */
    QColor backgroundColor() const;


    /**
     * Draw the current layer given the painter.
     *
     * @param   cPainter        painter instance to draw this layer
     * @param   nTileSize       dimension of a single tile
     */
    void drawLayer(QPainter & cPainter, int nTileSize) const override;

};


}
}


#endif
