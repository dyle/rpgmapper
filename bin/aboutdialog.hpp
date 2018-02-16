/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_ABOUTDIALOG_HPP
#define RPGMAPPER_VIEW_ABOUTDIALOG_HPP


#include <memory>

#include <QDialog>


class Ui_aboutDialog;


namespace rpgmapper {
namespace view {


class AboutDialog : public QDialog {

    Q_OBJECT

    std::shared_ptr<Ui_aboutDialog> ui;

public:

    explicit AboutDialog(QWidget * parent);

};


}
}


#endif
