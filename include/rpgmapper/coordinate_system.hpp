/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COORDINATE_SYSTEM_HPP
#define RPGMAPPER_MODEL_COORDINATE_SYSTEM_HPP

#include <tuple>

#include <QSize>

#include <rpgmapper/coordinates.hpp>
#include <rpgmapper/numerals.hpp>


namespace rpgmapper {
namespace model {


enum class CoordinateOrigin { topLeft, topRight, bottomLeft, bottomRight };

struct NumeralCoordinates {
    QString x;
    QString y;
};

class CoordinateSystem {

    CoordinateOrigin origin = CoordinateOrigin::bottomLeft;
    QSize size{10, 10};
    QSharedPointer<NumeralConverter> numeralXAxis;
    QSharedPointer<NumeralConverter> numeralYAxis;

public:

    CoordinateSystem();

    CoordinateOrigin getOrigin() const { return origin; }

    static constexpr QSize getMaximumSize() { return QSize{1000, 1000}; }

    static constexpr QSize getMinimumSize() { return QSize{1, 1}; }

    NumeralCoordinates getNumeralCoordinates(QPoint position) const;

    NumeralCoordinates getNumeralCoordinates(int x, int y) const { return getNumeralCoordinates(QPoint{x, y}); }

    QSharedPointer<NumeralConverter> const & getNumeralXAxis() const { return numeralXAxis; }

    QSharedPointer<NumeralConverter> const & getNumeralYAxis() const { return numeralYAxis; }

    QSize getSize() const { return size; }

    void setNumeralXAxis(QString numeral);

    void setNumeralYAxis(QString numeral);

    void setOrigin(CoordinateOrigin origin) { this->origin = origin; }

    Coordinates transpose(QPoint const & position) const;

    Coordinates transpose(int x, int y) const { return transpose(QPoint{x, y}); }

    CoordinatesF transpose(QPointF const & position) const;

    CoordinatesF transpose(float x, float y) const { return transpose(QPointF{x, y}); }

    CoordinatesF transpose(double x, double y) const { return transpose(QPointF{x, y}); }

    void resize(QSize const & size);

    void resize(int width, int height) { resize(QSize{width, height}); }
};


}
}

#endif
