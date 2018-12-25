/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_SHAPECATALOGWIDGET_HPP
#define RPGMAPPER_VIEW_SHAPECATALOGWIDGET_HPP

#include <QListWidget>
#include <QString>

#include <rpgmapper/resource/shape_catalog.hpp>


namespace rpgmapper {
namespace view {


/**
 * This widget displays a list of all shapes of a single shape catalog.
 */
class ShapeCatalogWidget : public QListWidget {

    Q_OBJECT
    
    QString catalog;        /**< The reosurce path to the catalog displayed. */

public:
    
    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit ShapeCatalogWidget(QWidget * parent = nullptr);

public slots:
    
    /**
     * Sets a new shape catalog.
     *
     * @param catalog
     */
    void setCatalog(QString catalog);
    
private:
    
    /**
     * Sets a new shape catalog.
     *
     * @param   shapeCatalog        the new shape catalog to display.
     */
    void setCatalog(rpgmapper::model::resource::ShapeCatalog * shapeCatalog);
};


}
}


#endif
