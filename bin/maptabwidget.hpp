/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_MAPTABWIDGET_HPP
#define RPGMAPPER_VIEW_MAPTABWIDGET_HPP


#include <memory>

#include <QTabWidget>

#include <rpgmapper/selection.hpp>
#include "mapscrollarea.hpp"


namespace rpgmapper {
namespace view {


class MapTabWidget : public QTabWidget {


    Q_OBJECT

    rpgmapper::model::SelectionPointer selection;
    std::map<QString, MapScrollArea *> mapScrollAreas;

public:

    explicit MapTabWidget(QWidget * parent = nullptr);

    void setSelection(rpgmapper::model::SelectionPointer & selection);

public slots:

    void closeCurrentMap();

    void mapRemoved(QString const &mapName);

    void mapSelected(QString const & mapName);

private:

    void connectSelectionSignals();

private slots:

    void mapCloseRequested(int nIndex);

signals:

    void hoverCoordinates(int x, int y);

};


}
}


#endif
