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


void ResourcesViewDialog::insertResource(QTreeWidgetItem * rootNode,
        rpgmapper::model::ResourcePointer const & resource) {
    
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
