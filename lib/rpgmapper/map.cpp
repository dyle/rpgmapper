/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include "map_impl.hpp"

using namespace rpgmapper::model;


Map::Map(QString const & name, Region * region) : QObject{region} {
    impl = std::make_shared<Map::Impl>(this, region);
    impl->setName(name);
}


bool Map::applyJsonObject(QJsonObject const & json) {
    return impl->applyJsonObject(json);
}


AxisLayerPointer const & Map::getAxisLayer() const {
    return impl->getAxisLayer();
}


BackgroundLayerPointer const & Map::getBackgroundLayer() const {
    return impl->getBackgroundLayer();
}


TileLayers const & Map::getBaseLayers() const {
    return impl->getBaseLayers();
}


CoordinateSystem const & Map::getCoordinateSystem() const {
    return impl->getCoordinateSystem();
}


GridLayerPointer const & Map::getGridLayer() const {
    return impl->getGridLayer();
}


QString Map::getInvalidCharactersInName() {
    return Map::Impl::getInvalidCharactersInName();
}


QJsonObject Map::getJsonObject(rpgmapper::model::io::Content & content) const {
    return impl->getJsonObject(content);
}


QString const & Map::getName() const {
    return impl->getName();
}


QSharedPointer<NumeralConverter> const & Map::getNumeralXAxis() const {
    return impl->getNumeralXAxis();
}


QSharedPointer<NumeralConverter> const & Map::getNumeralYAxis() const {
    return impl->getNumeralYAxis();
}


Region * Map::getRegion() {
    return impl->getRegion();
}


Region const * Map::getRegion() const {
    return impl->getRegion();
}


QString const & Map::getRegionName() const {
    return impl->getRegionName();
}


ResourceDBPointer & Map::getResourceDB() {
    return getRegion()->getResourceDB();
}


ResourceDBPointer const & Map::getResourceDB() const {
    return getRegion()->getResourceDB();
}


QSize Map::getSize() const {
    return impl->getSize();
}


TextLayerPointer const & Map::getTextLayer() const {
    return impl->getTextLayer();
}


TileLayers const & Map::getTileLayers() const {
    return impl->getTileLayers();
}


bool Map::isNameValid(QString name) {
    return Map::Impl::isNameValid(name);
}


MapPointer const & Map::null() {
    static MapPointer nullMap{new InvalidMap};
    return nullMap;
}


void Map::resize(QSize const & size) {
    if (size == getSize()) {
        return;
    }
    impl->resize(size);
    emit resized(getName());
}


void Map::setCoordinateOffset(QPointF offset) {
    impl->setOffsetF(offset);
    emit changed();
}


void Map::setName(QString const & name) {
    QString nameBefore = impl->getName();
    if (nameBefore == name) {
        return;
    }
    impl->setName(name);
    emit nameChanged(nameBefore, name);
    emit changed();
}


void Map::setNumeralXAxis(QString const & numeral) {
    impl->setNumeralXAxis(numeral);
    emit numeralForAxisChanged(getName());
    emit changed();
}


void Map::setNumeralYAxis(QString const & numeral) {
    impl->setNumeralYAxis(numeral);
    emit numeralForAxisChanged(getName());
    emit changed();
}


void Map::setOrigin(CoordinatesOrigin origin) {
    if (origin != impl->getCoordinateSystem().getOrigin()) {
        impl->getCoordinateSystem().setOrigin(origin);
        emit changed();
    }
}


QString Map::tanslateToNumeralOnX(int x) const {
    return getNumeralXAxis()->convert(x);
}


QString Map::tanslateToNumeralOnY(int y) const {
    return getNumeralYAxis()->convert(y);
}
