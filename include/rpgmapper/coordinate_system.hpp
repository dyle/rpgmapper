/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COORDINATE_SYSTEM_HPP
#define RPGMAPPER_MODEL_COORDINATE_SYSTEM_HPP

#include <QSize>

#include <rpgmapper/coordinates.hpp>


namespace rpgmapper {
namespace model {


enum class CoordinateOrigin { topLeft, topRight, bottomLeft, bottomRight };

class CoordinateSystem {

    CoordinateOrigin origin = CoordinateOrigin::bottomLeft;
    QSize size{10, 10};

public:

    CoordinateSystem() = default;

    CoordinateOrigin getOrigin() const { return origin; }

    static constexpr QSize getMaximumSize() { return QSize{1000, 1000}; }

    static constexpr QSize getMinimumSize() { return QSize{1, 1}; }

    QSize getSize() const { return size; }

    void setOrigin(CoordinateOrigin origin) { this->origin = origin; }

    UserCoordinate transpose(ScreenCoordinate const & position) const;

    UserCoordinate transpose(int x, int y) const { return transpose(ScreenCoordinate{x, y}); }

    UserCoordinateF transpose(ScreenCoordinateF const & position) const;

    UserCoordinateF transpose(float x, float y) const { return transpose(ScreenCoordinateF{x, y}); }

    UserCoordinateF transpose(double x, double y) const { return transpose(ScreenCoordinateF{x, y}); }

    void resize(QSize const & size);

};


}
}

#endif
