/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_MAPWIDGET_HPP
#define RPGMAPPER_VIEW_MAPWIDGET_HPP

#include <list>
#include <memory>

#include <QPainter>
#include <QString>
#include <QWidget>

#include <rpgmapper/average.hpp>
#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/map.hpp>


namespace rpgmapper::view {


/**
 * This widget renders a map.
 */
class MapWidget : public QWidget {

    Q_OBJECT

    rpgmapper::model::Map * map = nullptr;        /**< The map displayed. */
    int tileSize;                                 /**< The current size of a single tile. */
    
    bool axisVisible;              /**< Visibility flag for the current axis. */
    bool gridVisible;              /**< Visibility flag for the current grid. */
    
    QPointF hoveredTilePosition;   /**< Position of the currently hovered tile on the map (measured from top/left). */
    
    /**
     * This holds the average time of the time durations in milliseconds.
     */
    rpgmapper::model::AverageOverSize<float> averagePaintDuration;
    
    bool leftMouseButtonDown = false;       /**< left mouse button down flag. */
    
public:

    /**
     * Constructor
     * @param   parent      Parent QWidget instance.
     */
    explicit MapWidget(QWidget * parent);
    
    /**
     * Returns the latest position of the tile hovered by the mouse.
     *
     * @return  the last known tile position hovered by the mouse.
     */
    QPointF getHoveredTilePosition() const {
        return hoveredTilePosition;
    }
    
    /**
     * Gets the name of the map this widget displays.
     *
     * @return  the name of the map displayed.
     */
    QString getMapName() const;
    
    /**
     * Returns the current tile size in pixels.
     *
     * @return  the current size of a single tile.
     */
    int getTileSize() const {
        return tileSize;
    }
    
    /**
     * Checks if the axis is currently visible on this map widget.
     *
     * @return  true, if an axis should be shown.
     */
    bool isAxisVisible() const {
        return axisVisible;
    }
    
    /**
     * Checks if the grid is currently visible on this map widget.
     *
     * @return  true, if an grid should be shown.
     */
    bool isGridVisible() const {
        return gridVisible;
    }
    
    /**
     * Shows/hides the axis.
     *
     * @param   visible         the new axis visibility.
     */
    void setAxisVisible(bool visible);
    
    /**
     * Shows/hides the grid.
     *
     * @param   visible         the new grid visibility.
     */
    void setGridVisible(bool visible);
    
    /**
     * Sets the map to display.
     *
     * @param   map             the map to render.
     */
    void setMap(rpgmapper::model::Map * map);

public slots:
    
    /**
     * The size of the map changed.
     */
    void mapSizeChanged();
    
    /**
     * Applies a new tile size to show.
     *
     * @param   tileSize        the new tile size.
     */
    void setTileSize(int tileSize);

protected:
    
    /**
     * The map widget has received the focus.
     *
     * @param   event       the focus event.
     */
    void focusInEvent(QFocusEvent * event);
    
    /**
     * The map widget has lost the focus.
     *
     * @param   event       the focus event.
     */
    void focusOutEvent(QFocusEvent * event);
    
    /**
     * The user pressed a key.
     *
     * @param   event       the key event.
     */
    void keyPressEvent(QKeyEvent * event);
    
    /**
     * Special handling of mouse move events.
     *
     * @param   event       the mouse move event.
     */
    void mouseMoveEvent(QMouseEvent * event) override;
    
    /**
     * The user pressed a mouse button on the map.
     *
     * @param   event       the mouse press event.
     */
    void mousePressEvent(QMouseEvent * event) override;
    
    /**
     * The user release a mouse button on the map.
     *
     * @param   event       the mouse press event.
     */
    void mouseReleaseEvent(QMouseEvent * event) override;
    
    /**
     * Special painting.
     *
     * @param   event       the paint event.
     */
    void paintEvent(QPaintEvent * event) override;
    
private:
    
    /**
     * Collects all layers, which are currently visible, in proper order.
     *
     * The order is:
     *      [0] - background
     *      [1] - base layers (maybe more than 1)
     *      [2] - grid
     *      [3] - axis
     *      [4] - tile layers (maybe more than 1)
     *      [5] - text
     */
    std::list<rpgmapper::model::layer::Layer const *> collectVisibleLayers() const;
    
    /**
     * Draws the hovering rectangle over a tile.
     *
     * @param   painter     painter used to draw.
     */
    void drawHoveredTile(QPainter & painter);
    
    /**
     * Erase all tiles under the current hovered field.
     */
    void eraseField();
    
    /**
     * Places the current selected tile of the current session at the hovered position on the map.
     */
    void placeCurrentSelectedTile();
    
    /**
     * The user engaged over a field.
     */
    void placeOrEraseTile();
    
    /**
     * Get the map coordinates by x and y as screen/widget coordinates.
     *
     * @param   x       x in the screen/widget area.
     * @param   y       y in the screen/widget area.
     * @return  the point as map coordinates and if it inside the map or not.
     */
    std::tuple<QPointF, bool> widgetToMapCoordinates(float x, float y) const;
    
signals:

    /**
     * The user hovers with the mouse over a field.
     *
     * @param   mapX        map X-coordinate the user currently hovers with the mouse.
     * @param   mapY        map Y-coordinate the user currently hovers with the mouse.
     */
    void hoverCoordinates(int mapX, int mapY);
    
    /**
     * The map widget has resized itself.
     */
    void resized();
    
    /**
     * Request to rotate the current tile left.
     */
    void rotateTileLeft();
    
    /**
     * Request to rotate the current tile right.
     */
    void rotateTileRight();
};


}


#endif
