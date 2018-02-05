/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef VIEW_ABOUTDIALOG_HPP
#define VIEW_ABOUTDIALOG_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QDialog>


// ------------------------------------------------------------
// decl


// fwd
class Ui_aboutdialog;


namespace rpgmapper {
namespace view {


/**
 * the rpgmapper main window
 */
class AboutDialog : public QDialog {


    Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent         parent widget instance
     */
    AboutDialog(QWidget * cParent);


private:


    std::shared_ptr<Ui_aboutdialog> ui;         /**< User interface. */

};


}
}


#endif
