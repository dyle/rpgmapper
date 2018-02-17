/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_COORDINATEWIDGET_HPP
#define RPGMAPPER_VIEW_COORDINATEWIDGET_HPP


#include <memory>

#include <QWidget>

#include <rpgmapper/coordinate_system.hpp>

class Ui_coordinatesWidget;


namespace rpgmapper {
namespace view {


class CoordinatesWidget : public QWidget {

    Q_OBJECT

    std::shared_ptr<Ui_coordinatesWidget> ui;

public:

    explicit CoordinatesWidget(QWidget * parent);

public slots:

    void clear();

    void showCoordinates(rpgmapper::model::NumeralCoordinates const & coordinates);
};


}
}


#endif
