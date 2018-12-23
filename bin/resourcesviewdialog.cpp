/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QList>
#include <QMessageBox>

#include <rpgmapper/resource/resource.hpp>
#include <rpgmapper/resource/resource_collection.hpp>
#include <rpgmapper/resource/resource_db.hpp>

#include "resourcesviewdialog.hpp"
#include "ui_resourcesviewdialog.h"

using namespace rpgmapper::model;
using namespace rpgmapper::model::resource;
using namespace rpgmapper::view;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


/**
 * Columns of the resource view
 */
enum class ResourceViewColumns {
    path = 0,
    name = 1,
    mimeType = 2,
    updateCounter = 3,
    itemType = 4
};


ResourcesViewDialog::ResourcesViewDialog(QWidget * parent) : QDialog{parent} {
    
    ui = std::make_shared<Ui_resourcesViewDialog>();
    ui->setupUi(this);
    
    localResourcesRootNode = new QTreeWidgetItem{};
    localResourcesRootNode->setText(0, tr("Local resources"));
    localResourcesRootNode->setText(static_cast<int>(ResourceViewColumns::itemType), "root");
    userResourcesRootNode = new QTreeWidgetItem{};
    userResourcesRootNode->setText(0, tr("User resources"));
    userResourcesRootNode->setText(static_cast<int>(ResourceViewColumns::itemType), "root");
    systemResourcesRootNode = new QTreeWidgetItem{};
    systemResourcesRootNode->setText(0, tr("System resources"));
    systemResourcesRootNode->setText(static_cast<int>(ResourceViewColumns::itemType), "root");
    
    ui->resourceTreeWidget->hideColumn(static_cast<int>(ResourceViewColumns::updateCounter));
    ui->resourceTreeWidget->hideColumn(static_cast<int>(ResourceViewColumns::itemType));
    ui->resourceTreeWidget->addTopLevelItem(localResourcesRootNode);
    ui->resourceTreeWidget->addTopLevelItem(userResourcesRootNode);
    ui->resourceTreeWidget->addTopLevelItem(systemResourcesRootNode);
    ui->saveButton->setEnabled(false);
    
    saveDialog = new QFileDialog{this};
    saveDialog->setFileMode(QFileDialog::AnyFile);
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);
    saveDialog->setWindowTitle(tr("Save resource"));

    connect(ui->resourceTreeWidget, &QTreeWidget::currentItemChanged, this, &ResourcesViewDialog::currentItemChanged);
    connect(ui->resourceTreeWidget, &QTreeWidget::itemDoubleClicked, this, &ResourcesViewDialog::saveCurrentResource);
    connect(ui->saveButton, &QPushButton::clicked, this, &ResourcesViewDialog::saveCurrentResource);
}


void ResourcesViewDialog::currentItemChanged() {
    auto currentItem = ui->resourceTreeWidget->currentItem();
    auto isResource = (currentItem != nullptr) &&
                      (currentItem->text(static_cast<int>(ResourceViewColumns::itemType)) == "resource");
    ui->saveButton->setEnabled(isResource);
}


void ResourcesViewDialog::dropResources(QTreeWidgetItem * node) {
    
    if (!node) {
        dropResources(localResourcesRootNode);
        dropResources(userResourcesRootNode);
        dropResources(systemResourcesRootNode);
    }
    else {
        for (int i = 0; i < node->childCount(); ++i) {
            dropResources(node->child(i));
        }
        if ((node->childCount() == 0) && !isUpdated(node) && (node->parent() != nullptr)) {
            node->parent()->removeChild(node);
            delete node;
        }
    }
}


QTreeWidgetItem * ResourcesViewDialog::ensureCategoryNode(QTreeWidgetItem * rootNode, ResourceType type) {
    
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
        categoryNode->setText(static_cast<int>(ResourceViewColumns::itemType), "category");
        categoryNode->setIcon(0, getIconForResourceType(type));
    }
    
    categoryNode->setText(static_cast<int>(ResourceViewColumns::updateCounter), QString::number(updateCounter));
    return categoryNode;
}


QTreeWidgetItem* ResourcesViewDialog::findResource(QTreeWidgetItem * rootNode, QString path) const {

    QTreeWidgetItem * foundResource = nullptr;
    auto items = ui->resourceTreeWidget->findItems(path, Qt::MatchExactly | Qt::MatchRecursive, 0);
    for (auto iter = items.begin(); (iter != items.end()) && !foundResource; ++iter) {
        if ((*iter)->parent() && (*iter)->parent()->parent() == rootNode) {
            foundResource = (*iter);
        }
    }

    return foundResource;
}


QIcon ResourcesViewDialog::getIconForResourceType(ResourceType type) const {

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


void ResourcesViewDialog::insertResource(QTreeWidgetItem * rootNode, ResourcePointer const & resource) {

    auto item = findResource(rootNode, resource->getPath());
    if (!item) {
        auto categoryNode = ensureCategoryNode(rootNode, resource->getType());
        item = new QTreeWidgetItem{categoryNode};
    }
    
    item->setText(static_cast<int>(ResourceViewColumns::path), resource->getPath());
    item->setText(static_cast<int>(ResourceViewColumns::name), resource->getName());
    item->setText(static_cast<int>(ResourceViewColumns::mimeType), resource->getMimeType().name());
    item->setText(static_cast<int>(ResourceViewColumns::updateCounter), QString::number(updateCounter));
    item->setText(static_cast<int>(ResourceViewColumns::itemType), "resource");
}


void ResourcesViewDialog::insertResources(QTreeWidgetItem * rootNode, ResourceCollectionPointer const & resources) {
    
    if (!rootNode) {
        throw std::runtime_error{"No root node tree widget item to insert resources."};
    }
    
    for (auto const & pair : resources->getResources()) {
        insertResource(rootNode, pair.second);
    }
}


bool ResourcesViewDialog::isUpdated(QTreeWidgetItem * node) const {
    
    if (node) {
        return node->text(static_cast<int>(ResourceViewColumns::updateCounter)).toUInt() == updateCounter;
    }
    return false;
}


void ResourcesViewDialog::saveCurrentResource() {
    
    auto currentItem = ui->resourceTreeWidget->currentItem();
    if (!currentItem) {
        return;
    }
    if (currentItem->text(static_cast<int>(ResourceViewColumns::itemType)) != "resource") {
        return;
    }
    
    auto resourcePath = currentItem->text(static_cast<int>(ResourceViewColumns::path));
    auto resource = ResourceDB::getResource(resourcePath);
    if (!resource) {
        throw std::runtime_error{"Could not locate resource in resource DB."};
    }
    
    saveDialog->selectFile(resource->getName());
    auto answer = saveDialog->exec();
    if ((answer == 0) || saveDialog->selectedFiles().empty()) {
        return;
    }
    auto fileName = saveDialog->selectedFiles().first();
    
    QFile file{fileName};
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this,
                              tr("Save resource"),
                              tr("Failed to open file to save resource."),
                              QMessageBox::Ok);
        return;
    }
    
    file.write(resource->getData());
    file.close();
    
    lastFolderUsed = QFileInfo{file}.dir().absolutePath();
}


void ResourcesViewDialog::setLastFolderUsed(QString folder) {
    
    QFileInfo fileInfo{folder};
    if (fileInfo.exists() && fileInfo.isDir()) {
        lastFolderUsed = folder;
        saveDialog->setDirectory(lastFolderUsed);
    }
}


void ResourcesViewDialog::showEvent(UNUSED QShowEvent * event) {
    
    updateResourcesView();
    
    static bool firstShow = true;
    if (firstShow) {
    
        ui->resourceTreeWidget->expandAll();
        for (int i = 0; i < static_cast<int>(ResourceViewColumns::updateCounter); ++i) {
            ui->resourceTreeWidget->resizeColumnToContents(i);
        }
        firstShow = false;
    }
}


void ResourcesViewDialog::updateResourcesView() {
    
    ++updateCounter;
    
    insertResources(localResourcesRootNode, ResourceDB::getLocalResources());
    insertResources(userResourcesRootNode, ResourceDB::getUserResources());
    insertResources(systemResourcesRootNode, ResourceDB::getSystemResources());
    
    dropResources();
    
    ui->resourceTreeWidget->update();
}
