/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_ZOOM_SLIDER_HPP
#define RPGMAPPER_VIEW_ZOOM_SLIDER_HPP

#include <memory>

#include <QWidget>


// fwd
class Ui_ZoomSlider;


namespace rpgmapper {
namespace view {


/**
 * This widget is a small slider to zoom a map.
 */
class ZoomSlider : public QWidget {

    Q_OBJECT
    
    std::shared_ptr<Ui_ZoomSlider> ui;              /**< The User Interface as created by the uic. */
    
    static std::vector<int> const zoomTable;        /**< The final tile size zoom values. */
    static std::map<int, int> sizeTable;            /**< Tile size values to slider step. */

public:
    
    /**
     * Constructor.
     *
     * @param   parent      parent QWidget instance.
     */
    explicit ZoomSlider(QWidget * parent);
    
    /**
     * Gets the current zoomed tile size.
     *
     * @return  the current zoomed tile size.
     */
    int getTileSize() const;
    
    /**
     * Checks if we can still increase the tile size.
     *
     * @return  true, if we did not yet reached the maximum tile size.
     */
    bool isZoomInPossible() const;
    
    /**
     * Checks if we can still decrease the tile size.
     *
     * @return  true, if we did not yet reached the minimum tile size.
     */
    bool isZoomOutPossible() const;
    
    /**
     * Sets the current zoomed tile size.
     *
     * @param   tileSize        thew new tile size
     */
    void setTileSize(int tileSize);

public slots:
    
    /**
     * Decreases the zoom level.
     */
    void decrease();
    
    /**
     * Increases the zoom level.
     */
    void increase();
    
private:
    
    /**
     * Inits the static zoom tables.
     */
    void initZoomTable() const;
    
private slots:

    /**
     * The slider has changed its value.
     */
    void sliderChanged();

signals:
    
    /**
     * Zoom changed to
     *
     * @param   tileSize        the new tile.
     */
    void zoomChanged(int tileSize);
};


}
}


#endif
