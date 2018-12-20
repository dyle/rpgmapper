/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_RESOURCEVIEWDIALOG_HPP
#define RPGMAPPER_VIEW_RESOURCEVIEWDIALOG_HPP

#include <memory>

#include <QDialog>
#include <QIcon>
#include <QTreeWidgetItem>

#include <rpgmapper/resource_collection_pointer.hpp>
#include <rpgmapper/resource_pointer.hpp>
#include <rpgmapper/resource_type.hpp>


// fwd
class Ui_resourcesViewDialog;


namespace rpgmapper {
namespace view {


/**
* This dialog shows all the current resources.
*/
class ResourcesViewDialog : public QDialog {

    Q_OBJECT
    
    std::shared_ptr<Ui_resourcesViewDialog> ui;      /**< The User Interface as created by the uic. */
    
    QTreeWidgetItem * localResourcesRootNode = nullptr;     /**< Tree node for the local resources */
    QTreeWidgetItem * userResourcesRootNode = nullptr;      /**< Tree node for the user resources */
    QTreeWidgetItem * systemResourcesRootNode = nullptr;    /**< Tree node for the system resources */
    
    unsigned int updateCounter = 0;                 /**< Current update run. */

public:
    
    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit ResourcesViewDialog(QWidget * parent);

public slots:
    
    /**
     * Reinit view of used resources.
     */
    void updateResourcesView();

protected:
    
    /**
     * The dialog received a show event.
     *
     * @param   event       the show event involved.
     */
    void showEvent(QShowEvent * event) override;
    
private:
    
    /**
     * Retrieves the icon for a resource type.
     *
     * @param   type        the resource type.
     * @return  the icon for this resource type.
     */
    QIcon getIconForResourceType(rpgmapper::model::ResourceType type) const;
    
    /**
     * Returns the category node under the root node (and create one if not existing).
     *
     * @param   rootNode        the root node under which to create the category.
     * @param   type            the resource type (== category).
     * @return  a tree widget item holding the category node.
     */
    QTreeWidgetItem * ensureCategoryNode(QTreeWidgetItem * rootNode, rpgmapper::model::ResourceType type);
    
    /**
     * Searches a path under a root node tree widget item.
     *
     * @param   rootNode            the root node item to search underneath.
     * @param   path                the resource path to search.
     * @return  the tree widget item, or nullptr if not found.
     */
    QTreeWidgetItem * findResource(QTreeWidgetItem * rootNode, QString path) const;

    /**
     * Inserts and/or updates a single resource under the given root node.
     *
     * @param   rootNode        the root node under which the resource is/should be located.
     * @param   resource        the resource.
     */
    void insertResource(QTreeWidgetItem * rootNode, rpgmapper::model::ResourcePointer const & resource);
    
    /**
     * Inserts and/or updates all resources of a resource collection.
     *
     * @param   rootNode        the root node to insert the resources under.
     * @param   resources       the resources to add.
     */
    void insertResources(QTreeWidgetItem * rootNode, rpgmapper::model::ResourceCollectionPointer const & resources);
};


}
}


#endif
