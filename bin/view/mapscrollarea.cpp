/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// ------------------------------------------------------------
// incs

// rpgmapper
#include "mapscrollarea.hpp"

using namespace rpgmapper::view;


// ------------------------------------------------------------
// code


/**
 * Ctor
 *
 * @param   cParent         parent widget
 * @param   cMapWidget      the map widget enclosed
 */
MapScrollArea::MapScrollArea(QWidget * cParent, MapWidget * cMapWidget) : QScrollArea{cParent} {

    setBackgroundRole(QPalette::Dark);
    setWidget(cMapWidget);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    cMapWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}
