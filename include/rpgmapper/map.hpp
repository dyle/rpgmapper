/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_MAP_HPP
#define RPGMAPPER_MODEL_MAP_HPP


#include <memory>

#include <QJsonObject>
#include <QObject>
#include <QSize>
#include <QSharedPointer>
#include <QString>

#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/layer/axis_layer.hpp>
#include <rpgmapper/layer/background_layer.hpp>
#include <rpgmapper/layer/grid_layer.hpp>
#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/layer/tile_layer.hpp>
#include <rpgmapper/layer/text_layer.hpp>


namespace rpgmapper {
namespace model {

class Map;
class Region;

using MapPointer = QSharedPointer<Map>;

using Maps = std::map<QString, MapPointer>;

class Map : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    Map() = delete;

    explicit Map(QString const & name, Region * region = nullptr);

    ~Map() override = default;

    bool applyJsonObject(QJsonObject const & json);

    AxisLayerPointer & getAxisLayer();

    AxisLayerPointer const & getAxisLayer() const;

    BackgroundLayerPointer & getBackgroundLayer();

    BackgroundLayerPointer const & getBackgroundLayer() const;

    TileLayers & getBaseLayers();

    TileLayers const & getBaseLayers() const;

    CoordinateSystem const & getCoordinateSystem() const;

    GridLayerPointer & getGridLayer();

    GridLayerPointer const & getGridLayer() const;

    QJsonObject getJsonObject() const;

    QString const & getName() const;

    QSharedPointer<NumeralConverter> const & getNumeralXAxis() const;

    QSharedPointer<NumeralConverter> const & getNumeralYAxis() const;

    Region * getRegion();

    QString const & getRegionName() const;

    QSize getSize() const;

    TileLayers & getTileLayers();

    TileLayers const & getTileLayers() const;

    TextLayerPointer & getTextLayer();

    TextLayerPointer const & getTextLayer() const;

    virtual bool isValid() const { return true; }

    static MapPointer const & null();

    void resize(QSize const & size);

    void setName(QString const & name);

    void setNumeralXAxis(QString const & numeral);

    void setNumeralYAxis(QString const & numeral);

    void setCoordinateOffset(QPointF offset);

    void setOrigin(CoordinatesOrigin origin);

    QString tanslateToNumeralOnX(int x) const;

    QString tanslateToNumeralOnY(int y) const;

signals:

    void changed();

    void nameChanged(QString nameBefore, QString nameAfter);

    void numeralForAxisChanged(QString mapName);

    void resized(QString mapName);
};

class InvalidMap final : public Map {
public:
    InvalidMap() : Map{QString::Null{}, nullptr} {}
    bool isValid() const override { return false; }
};


}
}


#endif
