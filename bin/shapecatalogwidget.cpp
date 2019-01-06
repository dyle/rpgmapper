/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/resource/shape.hpp>

#include "shapecatalogwidget.hpp"

using namespace rpgmapper::model::resource;
using namespace rpgmapper::view;


ShapeCatalogWidget::ShapeCatalogWidget(QWidget * parent) : QListWidget{parent} {
    
    setFlow(QListView::LeftToRight);
    setIconSize(QSize{48, 48});
    setMovement(QListView::Static);
    setResizeMode(QListView::Adjust);
    setSelectionRectVisible(false);
    setSpacing(6);
    setUniformItemSizes(true);
    setViewMode(QListView::IconMode);
    setWordWrap(true);
    
    connect(this, &QListWidget::itemClicked, this, &ShapeCatalogWidget::newShapeSelected);
}


void ShapeCatalogWidget::newShapeSelected() {

    auto pair = itemToShape.find(currentItem());
    if (pair == itemToShape.end()) {
        throw std::runtime_error{"Items points to not recognized shape path."};
    }
    
    emit shapeSelected((*pair).second);
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
    itemToShape.clear();
    for (auto const & pair : shapeCatalog->getShapes()) {
        
        auto resource = ResourceDB::getResource(pair.second);
        auto shape = dynamic_cast<rpgmapper::model::resource::Shape *>(resource.data());
        if (shape) {
            
            auto item = new QListWidgetItem{this};
            item->setIcon(shape->getIcon(48));
            item->setText(pair.first);
            addItem(item);
            
            itemToShape[item] = shape->getPath();
        }
    }
}
