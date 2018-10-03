/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COORDINATE_SYSTEM_HPP
#define RPGMAPPER_MODEL_COORDINATE_SYSTEM_HPP

#include <tuple>

#include <QJsonObject>
#include <QPoint>
#include <QPointF>
#include <QSize>

#include <rpgmapper/numerals.hpp>
#include <rpgmapper/io/content.hpp>


namespace rpgmapper {
namespace model {


enum class CoordinatesOrigin { topLeft, topRight, bottomLeft, bottomRight };


QString coordinatesOriginToString(CoordinatesOrigin origin);


CoordinatesOrigin stringToCoordinatesOrigin(QString const & string);


struct NumeralCoordinates {
    QString x;
    QString y;
};


class CoordinateSystem {

    CoordinatesOrigin origin = CoordinatesOrigin::bottomLeft;
    QSize size{10, 10};
    QSharedPointer<NumeralConverter> numeralXAxis;
    QSharedPointer<NumeralConverter> numeralYAxis;
    QPointF offset{0.0, 0.0};

public:

    CoordinateSystem();

    virtual bool applyJsonObject(QJsonObject const & json);

    QJsonObject getJsonObject(rpgmapper::model::io::Content & content) const;

    static constexpr QSize getMaximumSize() {
        return QSize{1000, 1000};
    }

    static constexpr QSize getMinimumSize() {
        return QSize{1, 1};
    }

    NumeralCoordinates getNumeralCoordinates(QPoint position) const;

    NumeralCoordinates getNumeralCoordinates(int x, int y) const {
        return getNumeralCoordinates(QPoint{x, y});
    }

    QSharedPointer<NumeralConverter> const & getNumeralXAxis() const {
        return numeralXAxis;
    }

    QSharedPointer<NumeralConverter> const & getNumeralYAxis() const {
        return numeralYAxis;
    }

    QPoint getOffset() const {
        return QPoint{static_cast<int>(offset.x()), static_cast<int>(offset.y())};
    }

    QPointF getOffsetF() const {
        return offset;
    }

    CoordinatesOrigin getOrigin() const {
        return origin;
    }

    QSize getSize() const {
        return size;
    }

    void setNumeralXAxis(QString numeral);

    void setNumeralYAxis(QString numeral);

    void setOffset(QPoint offset) {
        this->offset = offset;
    }

    void setOffsetF(QPointF offset) {
        this->offset = offset;
    }

    void setOrigin(CoordinatesOrigin origin) {
        this->origin = origin;
    }

    QPoint transposeToMapCoordinates(QPoint const & position) const;

    QPoint transposeToMapCoordinates(int x, int y) const {
        return transposeToMapCoordinates(QPoint{x, y});
    }

    QPointF transposeToMapCoordinates(QPointF const & position) const;

    QPointF transposeToMapCoordinates(float x, float y) const {
        return transposeToMapCoordinates(QPointF{x, y});
    }

    QPointF transposeToMapCoordinates(double x, double y) const {
        return transposeToMapCoordinates(QPointF{x, y});
    }

    QPoint transposeToScreenCoordinates(QPoint const & position) const;

    QPoint transposeToScreenCoordinates(int x, int y) const {
        return transposeToScreenCoordinates(QPoint{x, y});
    }

    QPointF transposeToScreenCoordinates(QPointF const & position) const;

    QPointF transposeToScreenCoordinates(float x, float y) const {
        return transposeToScreenCoordinates(QPointF{x, y});
    }

    QPointF transposeToScreenCoordinates(double x, double y) const {
        return transposeToScreenCoordinates(QPointF{x, y});
    }

    void resize(QSize const & size);

    void resize(int width, int height) {
        resize(QSize{width, height});
    }

private:

    bool applyJsonNumerals(QJsonObject const & json);

    bool applyJsonOffset(QJsonObject const & json);

    bool applyJsonSize(QJsonObject const & json);

    QPoint transpose(QPoint const & position) const;

    QPointF transpose(QPointF const & position) const;
};


}
}


#endif
