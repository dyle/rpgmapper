/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_AXIS_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_AXIS_LAYER_HPP


#include <QColor>
#include <QFont>

#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {


class AxisLayer;
using AxisLayerPointer = QSharedPointer<AxisLayer>;

class AxisLayer : public Layer {

Q_OBJECT

public:

    explicit AxisLayer(rpgmapper::model::Map * map, QObject * parent = nullptr);

    ~AxisLayer() override = default;

    void draw(QPainter & painter, int tileSize) const override;

    QColor getColor() const;

    QFont getFont() const;

    QJsonObject getJsonObject(rpgmapper::model::io::Content & content) const override;

    void setColor(QColor color);

    void setFont(QFont font);

private:

    void drawXAnnotation(QPainter & painter, int tileSize) const;

    void drawYAnnotation(QPainter & painter, int tileSize) const;
};


}
}


#endif
