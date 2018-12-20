/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_RESOURCEVIEWDIALOG_HPP
#define RPGMAPPER_VIEW_RESOURCEVIEWDIALOG_HPP

#include <memory>

#include <QDialog>


// fwd
class Ui_resourcesViewDialog;


namespace rpgmapper {
namespace view {


/**
* This dialog shows all the current resources.
*/
class ResourcesViewDialog : public QDialog {

    Q_OBJECT
    
    std::shared_ptr<Ui_resourcesViewDialog> ui;       /**< The User Interface as created by the uic. */

public:
    
    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit ResourcesViewDialog(QWidget * parent);
};


}
}


#endif
