/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_ORIGINCORNERWIDGET_HPP
#define RPGMAPPER_VIEW_ORIGINCORNERWIDGET_HPP


#include <memory>

#include <QDialog>

#include <rpgmapper/coordinate_system.hpp>

using namespace rpgmapper::model;


class Ui_coordinatesOriginWidget;

namespace rpgmapper {
namespace view {


class CoordinatesOriginWidget : public QWidget {

    Q_OBJECT

    std::shared_ptr<Ui_coordinatesOriginWidget> ui;

public:

    explicit CoordinatesOriginWidget(QWidget * parent);

    CoordinatesOrigin origin() const;

public slots:

    void setOrigin(CoordinatesOrigin origin);

};


}
}


#endif
