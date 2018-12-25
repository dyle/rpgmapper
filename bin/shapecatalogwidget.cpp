/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/resource/shape.hpp>

#include "shapecatalogwidget.hpp"

using namespace rpgmapper::model::resource;
using namespace rpgmapper::view;


ShapeCatalogWidget::ShapeCatalogWidget(QWidget * parent) : QListWidget{parent} {
    setFlow(QListView::LeftToRight);
    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    setMovement(QListView::Static);
    setGridSize(QSize{48, 48});
}


void ShapeCatalogWidget::setCatalog(QString catalog) {
    
    this->catalog = catalog;
    
    auto resource = ResourceDB::getResource(catalog);
    if (!resource) {
        throw std::runtime_error{"Invalid shape catalog path (unknown) passed on to ShapeCatalogWidget."};
    }
    auto shapeCatalog = dynamic_cast<ShapeCatalog *>(resource.data());
    if (!shapeCatalog) {
        throw std::runtime_error{"Passed resource path is not a shape catalog path."};
    }
    
    setCatalog(shapeCatalog);
}


void ShapeCatalogWidget::setCatalog(rpgmapper::model::resource::ShapeCatalog * shapeCatalog) {
    
    clear();
    for (auto const & pair : shapeCatalog->getShapes()) {
        
        auto resource = ResourceDB::getResource(pair.second);
        auto shape = dynamic_cast<rpgmapper::model::resource::Shape *>(resource.data());
        if (shape) {
            
            auto item = new QListWidgetItem{this};
            item->setText(pair.first);
            item->setIcon(shape->getIcon(48));
            addItem(item);
        }
    }
}
