/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_MAINWINDOW_IMPL_HPP
#define RPGMAPPER_VIEW_MAINWINDOW_IMPL_HPP


#include <memory>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"


namespace rpgmapper {
namespace view {


class MainWindow::Impl final {

    MainWindow * mainWindow = nullptr;
    std::shared_ptr<Ui_mainwindow> ui;
    AtlasPointer atlas;

public:

    explicit Impl(MainWindow * mainWindow);

    AtlasPointer getAtlas() { return atlas; }

    AtlasPointer const getAtlas() const { return atlas; }
};


}
}


#endif
