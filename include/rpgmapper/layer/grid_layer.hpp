/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_GRID_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_GRID_LAYER_HPP


#include <QColor>
#include <QFont>

#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {

class GridLayer : public Layer {

    Q_OBJECT

public:

    explicit GridLayer(rpgmapper::model::Map * map, QObject * parent = nullptr);

    ~GridLayer() override = default;

    void draw(QPainter & painter, int tileSize) const override;

private:

    void drawBorder(QPainter & painter, int tileSize) const;

    void drawXAnnotation(QPainter & painter, int tileSize) const;

    void drawXAxis(QPainter & painter, int tileSize) const;

    void drawYAnnotation(QPainter & painter, int tileSize) const;

    void drawYAxis(QPainter & painter, int tileSize) const;

    QColor gridColor() const;

    QFont gridFont() const;
};

using GridLayerPointer = QSharedPointer<GridLayer>;


}
}


#endif
