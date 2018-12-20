/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QList>

#include <rpgmapper/resource.hpp>
#include <rpgmapper/resource_collection.hpp>
#include <rpgmapper/resource_db.hpp>

#include "resourcesviewdialog.hpp"
#include "ui_resourcesviewdialog.h"

using namespace rpgmapper::model;
using namespace rpgmapper::view;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


ResourcesViewDialog::ResourcesViewDialog(QWidget * parent) : QDialog{parent} {
    
    ui = std::make_shared<Ui_resourcesViewDialog>();
    ui->setupUi(this);
    
    localResourcesRootNode = new QTreeWidgetItem{};
    localResourcesRootNode->setText(0, tr("Local resources"));
    userResourcesRootNode = new QTreeWidgetItem{};
    userResourcesRootNode->setText(0, tr("User resources"));
    systemResourcesRootNode = new QTreeWidgetItem{};
    systemResourcesRootNode->setText(0, tr("System resources"));
    
    ui->resourceTreeWidget->addTopLevelItem(localResourcesRootNode);
    ui->resourceTreeWidget->addTopLevelItem(userResourcesRootNode);
    ui->resourceTreeWidget->addTopLevelItem(systemResourcesRootNode);
}


QTreeWidgetItem* ResourcesViewDialog::ensureCategoryNode(QTreeWidgetItem * rootNode,
        rpgmapper::model::ResourceType type) {
    
    QTreeWidgetItem * categoryNode = nullptr;
    auto categoryName = getResourceTypeName(type, true);
    auto items = ui->resourceTreeWidget->findItems(categoryName, Qt::MatchFixedString | Qt::MatchRecursive, 0);
    for (auto iter = items.begin(); (iter != items.end()) && !categoryNode; ++iter) {
        if ((*iter)->parent() == rootNode) {
            categoryNode = (*iter);
        }
    }
    
    if (!categoryNode) {
        categoryNode = new QTreeWidgetItem{rootNode};
        categoryNode->setText(0, categoryName);
        categoryNode->setIcon(0, getIconForResourceType(type));
    }
    
    categoryNode->setText(2, QString::number(updateCounter));
    return categoryNode;
}


QTreeWidgetItem* ResourcesViewDialog::findResource(QTreeWidgetItem * rootNode, QString path) const {

    QTreeWidgetItem * foundResource = nullptr;
    auto items = ui->resourceTreeWidget->findItems(path, Qt::MatchExactly, 0);
    for (auto iter = items.begin(); (iter != items.end()) && !foundResource; ++iter) {
        if ((*iter)->parent() && (*iter)->parent()->parent() == rootNode) {
            foundResource = (*iter);
        }
    }

    return foundResource;
}


QIcon ResourcesViewDialog::getIconForResourceType(rpgmapper::model::ResourceType type) const {

    QIcon icon;
    
    switch (type) {
        
        case ResourceType::unknown:
            break;
        
        case ResourceType::background:
            icon = QIcon(":/icons/gfx/background.png");
            break;
    
        case ResourceType::colorpalette:
            icon = QIcon(":/icons/gfx/colorpalette.png");
            break;
    
        case ResourceType::shape:
            icon = QIcon(":/icons/gfx/shapes.png");
            break;
    }
    
    return icon;
}


void ResourcesViewDialog::insertResource(QTreeWidgetItem * rootNode,
        rpgmapper::model::ResourcePointer const & resource) {
    
    auto item = findResource(rootNode, resource->getPath());
    if (!item) {
        auto categoryNode = ensureCategoryNode(rootNode, resource->getType());
        item = new QTreeWidgetItem{categoryNode};
    }
    
    item->setText(0, resource->getPath());
    item->setText(1, resource->getName());
    item->setText(2, QString::number(updateCounter));
}


void ResourcesViewDialog::insertResources(QTreeWidgetItem * rootNode,
        rpgmapper::model::ResourceCollectionPointer const & resources) {
    
    if (!rootNode) {
        throw std::runtime_error{"No root node tree widget item to insert resources."};
    }
    
    for (auto const & pair : resources->getResources()) {
        insertResource(rootNode, pair.second);
    }
}


void ResourcesViewDialog::showEvent(UNUSED QShowEvent * event) {
    updateResourcesView();
}


void ResourcesViewDialog::updateResourcesView() {
    
    ++updateCounter;
    
    insertResources(localResourcesRootNode, ResourceDB::getLocalResources());
    insertResources(userResourcesRootNode, ResourceDB::getUserResources());
    insertResources(systemResourcesRootNode, ResourceDB::getSystemResources());
}
