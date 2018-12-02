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
#include <QObject>
#include <QRect>
#include <QSize>

#include <rpgmapper/json/json_io.hpp>
#include <rpgmapper/numerals.hpp>


namespace rpgmapper {
namespace model {


/**
 * These are the different positions we can place to origin on a CoordinateSystem.
 */
enum class CoordinatesOrigin { topLeft, topRight, bottomLeft, bottomRight };


/**
 * Converts an origin enum to a string.
 *
 * @param   origin      the origin position.
 * @return  a string describing the origin position.
 */
QString coordinatesOriginToString(CoordinatesOrigin origin);


/**
 * Converts a string to a known origin position.
 *
 * @param   string      the string describing the origin position.
 * @return  the origin position defined by the string.
 */
CoordinatesOrigin stringToCoordinatesOrigin(QString const & string);


/**
 * A coordinate system manages translation and naming of axis and points on a map.
 */
class CoordinateSystem : public QObject, public json::JSONIO {
    
    Q_OBJECT

    CoordinatesOrigin origin = CoordinatesOrigin::bottomLeft;       /**< Position of the origin. */
    QSize size{10, 10};                                             /**< Size of the coordinate system/map. */
    QSharedPointer<NumeralConverter> numeralXAxis;                  /**< Numerals used for the X-Axis. */
    QSharedPointer<NumeralConverter> numeralYAxis;                  /**< Numerals used for the Y-Axis. */
    QPointF offset{0.0, 0.0};                                       /**< Offset of the origin. */
    float margin{0.0};                                              /**< Margin in tile size steps. */

public:

    /**
     * Constructor.
     */
    CoordinateSystem();
    
    /**
     * Applies a JSON to this instance.
     *
     * @param   json    the JSON.
     * @return  true, if the found values in the JSON data has been applied.
     */
    bool applyJSON(QJsonObject const & json) override;
    
    /**
     * Gets the inner rect of the map.
     *
     * The inner rect of the map respects the margin and the axis labels (1 tile size unit)
     *
     * @param   tileSize        size of a single tile
     * @return  a rectangle holding  the outer dimension information
     */
    QRect getInnerRect(int tileSize) const;
    
    /**
     * Create a JSON structure from ourselves.
     *
     * @return      a valid JSON  structure from ourselves.
     */
    QJsonObject getJSON() const override;
    
    /**
     * Returns the margin as a factor of tile size.
     *
     * @return  the margin for the map.
     */
    float getMargin() const {
        return margin;
    }
    
    /**
     * Gets the maximum dimension of a map.
     *
     * @return  the maximum dimension of a map.
     */
    static constexpr QSize getMaximumSize() {
        return QSize{1000, 1000};
    }
    
    /**
     * Gets the minimum dimension of a map.
     *
     * @return  the minimum dimension of a map.
     */
    static constexpr QSize getMinimumSize() {
        return QSize{1, 1};
    }

    /**
     * Convert a point on the map to the numeral presentation.
     *
     * @param   position        the position on the map.
     * @return  A structure holding the strings for the X and Y position in the given numeral setting.
     */
    NumeralCoordinates getNumeralCoordinates(QPoint position) const;
    
    /**
     * Convert a point on the map to the numeral presentation.
     *
     * @param   x       the X-position on the map.
     * @param   y       the Y-position on the map.
     * @return  A structure holding the strings for the X and Y position in the given numeral setting.
     */
    NumeralCoordinates getNumeralCoordinates(int x, int y) const {
        return getNumeralCoordinates(QPoint{x, y});
    }

    /**
     * Returns the numeral converter used for the X-Axis.
     *
     * @return  the numeral converter for the X-Axis.
     */
    QSharedPointer<NumeralConverter> const & getNumeralXAxis() const {
        return numeralXAxis;
    }
    
    /**
     * Returns the numeral converter used for the Y-Axis.
     *
     * @return  the numeral converter for the Y-Axis.
     */
    QSharedPointer<NumeralConverter> const & getNumeralYAxis() const {
        return numeralYAxis;
    }

    /**
     * Returns the offset of the origin.
     *
     * @return  the offset values for the origin.
     */
    QPointF getOffset() const {
        return offset;
    }
    
    /**
     * Gets the position of the origin on the map.
     *
     * @return  the position of the origin on the map.
     */
    CoordinatesOrigin getOrigin() const {
        return origin;
    }

    /**
     * Gets the outer rect of the map.
     *
     * The outer rect of the map respects the margin an the axis labels (1 tile size unit)
     *
     * @param   tileSize        size of a single tile
     * @return  a rectangle holding  the outer dimension information
     */
    QRect getOuterRect(int tileSize) const;
    
    /**
     * Returns the current dimension of the map.
     *
     * @return  the current size of the map.
     */
    QSize getSize() const {
        return size;
    }
    
    /**
     * Checks if the given size is a valid one, suitable for a map.
     *
     * @param   size        a size to check.
     * @return  true, if this size can be used as a map size.
     */
    static bool isValidSize(QSize size);
    
    /**
     * Applies a new margin to the map.
     *
     * @param   newMargin       the new margin in units of tile size.
     */
    void setMargin(float newMargin);

    /**
     * Applies a new numeral converter to the X-Axis.
     *
     * @param   numeral     the name of the new X-Axis converter
     */
    void setNumeralXAxis(QString numeral);
    
    /**
     * Applies a new numeral converter to the Y-Axis.
     *
     * @param   numeral     the name of the new Y-Axis converter
     */
    void setNumeralYAxis(QString numeral);

    /**
     * Applies a new offset to the origin.
     *
     * @param   offset      the new offset values for the origin.
     */
    void setOffset(QPoint offset) {
        setOffset(QPointF{offset});
    }
    
    /**
     * Applies a new offset to the origin (float version).
     *
     * @param   offset      the new offset values for the origin.
     */
    void setOffset(QPointF offset);

    /**
     * Places the origin anew.
     *
     * @param   origin      the new position for the origin.
     */
    void setOrigin(CoordinatesOrigin origin);
    
    /**
     * Returns a x-axis numeral.
     *
     * @param   x       X-axis position
     * @return  The numeral used for x on the X-Axis.
     */
    QString tanslateToNumeralOnX(int x) const {
        return getNumeralXAxis()->convert(x);
    }
    
    /**
     * Returns a y-axis numeral.
     *
     * @param   y       Y-axis position
     * @return  The numeral used for y on the Y-Axis.
     */
    QString tanslateToNumeralOnY(int y) const {
        return getNumeralYAxis()->convert(y);
    }
    
    /**
     * Transposes the given point to map coordinates respecting the origin position.
     *
     * @param   x       the X value of the position.
     * @param   y       the Y value of the position.
     * @return  position within the maps coordination space.
     */
    QPointF transposeToMapCoordinates(int x, int y) const {
        return transposeToMapCoordinates(QPointF{static_cast<double>(x), static_cast<double>(y)});
    }
    
    /**
     * Transposes the given point to map coordinates respecting the origin position.
     *
     * @param   x       the X value of the position.
     * @param   y       the Y value of the position.
     * @return  position within the maps coordination space.
     */
    QPointF transposeToMapCoordinates(double x, double y) const {
        return transposeToMapCoordinates(QPointF{x, y});
    }
    
    /**
     * Transposes the given point to map coordinates respecting the origin position.
     *
     * @param   position        position having top-left as 0,0 (screen coordinates)
     * @return  position within the maps coordination space.
     */
    QPointF transposeToMapCoordinates(QPointF position) const;
    
    /**
     * Transposes the given point to screen coordinates respecting the origin position.
     *
     * @param   x       the X value of the position.
     * @param   y       the Y value of the position.
     * @return  screen coordinate position (top-left as 0,0).
     */
    QPointF transposeToScreenCoordinates(int x, int y) const {
        return transposeToScreenCoordinates(QPointF{static_cast<double>(x), static_cast<double>(y)});
    }
    
    /**
     * Transposes the given point to screen coordinates respecting the origin position.
     *
     * @param   x       the X value of the position.
     * @param   y       the Y value of the position.
     * @return  screen coordinate position (top-left as 0,0).
     */
    QPointF transposeToScreenCoordinates(double x, double y) const {
        return transposeToScreenCoordinates(QPointF{x, y});
    }
    
    /**
     * Transposes the given point to screen coordinates respecting the origin position.
     *
     * @param   position        position on the map.
     * @return  screen coordinate position (top-left as 0,0).
     */
    QPointF transposeToScreenCoordinates(QPointF position) const;
    
    /**
     * Resizes the map.
     *
     * @param   size        the new size of the map.
     */
    void resize(QSize size);
    
    
    /**
     * Resizes the map.
     *
     * @param   width       new width of the map.
     * @param   height      new height of the map.
     */
    void resize(int width, int height) {
        resize(QSize{width, height});
    }

signals:

    /**
     * The margin value changed.
     */
    void marginChanged();
    
    /**
     * The X-Axis numeral converter has changed.
     */
    void numeralXAxisChanged();
    
    /**
     * The Y-Axis numeral converter has changed.
     */
    void numeralYAxisChanged();

    /**
     * The offset of the origin changed.
     *
     * @param   offset      the new offset.
     */
    void offsetChanged(QPointF offset);
    
    /**
     * The position of the origin changed.
     *
     * @param   origin      the new origin.
     */
    void originChanged(CoordinatesOrigin origin);
    
    /**
     * The size of the map changed.
     *
     * @param   size        the new size of the map.
     */
    void sizeChanged(QSize size);
    
private:

    /**
     * Applies numerals found in a JSON.
     *
     * @param   json        the JSON holding the numerals.
     * @return  true, if the found JSON values have been applies.
     */
    bool applyJSONNumerals(QJsonObject const & json);
    
    /**
     * Applies the origin offset found in a JSON.
     *
     * @param   json        the JSON holding the origin offset.
     * @return  true, if the found JSON values have been applies.
     */
    bool applyJSONOffset(QJsonObject const & json);
    
    /**
     * Applies the size found in a JSON.
     *
     * @param   json        the JSON holding the size.
     * @return  true, if the found JSON values have been applies.
     */
    bool applyJSONSize(QJsonObject const & json);
    
    /**
     * Transposes a position.
     *
     * @param   position        the position to transpose..
     * @return  the transposed point..
     */
    QPointF transpose(QPointF const & position) const;
};


}
}


#endif
