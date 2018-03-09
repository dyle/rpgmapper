/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_MAPWIDGET_HPP
#define RPGMAPPER_VIEW_MAPWIDGET_HPP


#include <memory>

#include <QWidget>

#include <rpgmapper/average.hpp>
#include <rpgmapper/map.hpp>


namespace rpgmapper {
namespace view {


class MapWidget : public QWidget {

    Q_OBJECT

    QWeakPointer<rpgmapper::model::Map> map;
    rpgmapper::model::AverageOverSize<float> averagePaintDuration;

public:

    explicit MapWidget(QWidget * parent);

    void setMap(rpgmapper::model::MapPointer & map);

public slots:

    void mapChanged();

    void update();

protected:

    void mouseMoveEvent(QMouseEvent * event) override;

    void paintEvent(QPaintEvent * event) override;

signals:

    void hoverCoordinates(int mapX, int mapY);
};

}
}


#endif
