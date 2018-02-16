/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_MAPTABWIDGET_HPP
#define RPGMAPPER_VIEW_MAPTABWIDGET_HPP


#include <memory>

#include <QTabWidget>


namespace rpgmapper {
namespace view {


class MapTabWidget : public QTabWidget {


    Q_OBJECT

    class Impl;
    std::shared_ptr<MapTabWidget::Impl> impl;

public:


    explicit MapTabWidget(QWidget * parent = nullptr);


public slots:


//    void closeCurrentMap();
//
//    void deletedMap(rpgmapper::model::mapid_t nMapId);
//
//    void selectMap(rpgmapper::model::mapid_t nMapId);


private slots:


//    void mapCloseRequested(int nIndex);


signals:


//    void hoverCoordinates(int x, int y);


private:



};


}
}


#endif
