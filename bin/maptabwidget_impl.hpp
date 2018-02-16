/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_MAPTABWIDGET_IMPL_HPP
#define RPGMAPPER_VIEW_MAPTABWIDGET_IMPL_HPP


#include <memory>

#include "ui_mainwindow.h"


namespace rpgmapper {
namespace view {


class MainWindow;

class MainWindow::Impl final {

    // std::map<mapid_t, MapScrollArea *> m_cMapViews;     /**< all current map views */

public:

    Impl() = default;
};


}
}


#endif
