/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_ABOUTDIALOG_HPP
#define RPGMAPPER_VIEW_ABOUTDIALOG_HPP

#include <memory>

#include <QDialog>


// fwd
class Ui_aboutDialog;


namespace rpgmapper {
namespace view {


/**
 * This dialog shows something about the rpgmapper application.
 */
class AboutDialog : public QDialog {

    Q_OBJECT

    std::shared_ptr<Ui_aboutDialog> ui;         /**< The User Interface as created by the uic. */

public:

    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit AboutDialog(QWidget * parent);
};


}
}


#endif
