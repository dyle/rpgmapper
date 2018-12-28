/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MAINWINDOW_HPP
#define RPGMAPPER_MAINWINDOW_HPP

#include <memory>

#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>

#include "aboutdialog.hpp"
#include "coordinateswidget.hpp"
#include "logdialog.hpp"
#include "mappropertiesdialog.hpp"
#include "mapwidget.hpp"
#include "resourcesviewdialog.hpp"
#include "zoomslider.hpp"


// fwd
class Ui_mainwindow;


namespace rpgmapper {
namespace view {


/**
 * This is the rpgmapper main window, holding the whole application in place.
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

    std::shared_ptr<Ui_mainwindow> ui;                          /**< The User Interface as created by the uic. */

    AboutDialog * aboutDialog = nullptr;                        /**< Pre-created about dialog. */
    QFileDialog * loadAtlasDialog = nullptr;                    /**< Pre-created load dialog. */
    LogDialog * logDialog = nullptr;                            /**< Pre-created log dialog. */
    MapPropertiesDialog * mapPropertiesDialog = nullptr;        /**< Pre-created map properties dialog. */
    ResourcesViewDialog * resourcesViewDialog = nullptr;        /**< Pre-created resource view dialog. */
    QFileDialog * saveAtlasDialog = nullptr;                    /**< Pre-created save dialog. */

    QStringList recentAtlasFileNames;                           /**< List of recent loaded/saved atlas files. */
    QString recentAtlasFolderName;                              /**< The last folder to load/save an atlas file. */
    int maximumRecentAtlasFiles = 10;                           /**< Maximum number of entries in the recent list. */
    QList<QAction *> recentFileLoadActions;                     /**< Menu-actions to load the atlas files. */

    CoordinatesWidget * coordinatesWidget = nullptr;            /**< Pre-created coordinate widgets. */
    
    ZoomSlider * zoomSlider = nullptr;                          /**< Map Widget Zoom Slider */

public:

    /**
     * Constructor.
     */
    MainWindow();

public slots:
    
    /**
     * The ResourceDB might have changed: apply set of new resources to all widgets.
     */
    void applyResources();
    
    /**
     * The user wants to edit the atlas properties.
     */
    void editAtlasProperties();

    /**
     * The user wants to edit the properties of a map.
     */
    void editMapProperties();

    /**
     * The user wants to edit the properties of a region.
     */
    void editRegionProperties();

    /**
     * Check which action can currently be enabled and which disabled.
     */
    void enableActions();
    
    /**
     * Enable/disable rotate actions.
     */
    void enableRotateActions();
    
    /**
     * Enable/disable undo and redo actions.
     */
    void enableUndoRedoActions();
    
    /**
     * Enable/disable zoom actions.
     */
    void enableZoomActions();
    
    /**
     * Redo the last undone command.
     */
    void redo();
    
    /**
     * Rotates the current selected tile counter clockwise.
     */
    void rotateTileLeft();
    
    /**
     * Rotates the current selected tile clockwise.
     */
    void rotateTileRight();
    
    /**
     * Adjust the window title.
     */
    void setApplicationWindowTitle();
    
    /**
     * Show the about dialog.
     */
    void showAboutDialog();
    
    /**
     * Make some map coordinates visible.
     *
     * @param   x       X-Coordinate as for top/left.
     * @param   y       Y-Coordinate as for top/left.
     */
    void showCoordinates(int x, int y);
    
    /**
     * Show the resources view dialog.
     */
    void showResourcesViewDialog();
    
    /**
     * Switches the visibility of the axis of the current map widget
     */
    void toogleCurrentAxisVisibility();
    
    /**
     * Switches the visibility of the grid of the current map widget
     */
    void toogleCurrentGridVisibility();
    
    /**
     * Undo the last command.
     */
    void undo();
    
    /**
     * Show/hide the color picker widget.
     *
     * @param   visible     show/hide flag for widget.
     */
    void visibleColorPicker(bool visible);
    
    /**
     * Show/hide the current tile dock.
     *
     * @param   visible     show/hide flog for the current tile dock.
     */
    void visibleCurrentTile(bool visible);

    /**
     * Show/hide the minimap.
     *
     * @param   visible     show/hide flag for the minimap.
     */
    void visibleMinimap(bool visible);

    /**
     * Show/hide structure widget
     *
     * @param   visible     show/hide structure widget.
     */
    void visibleStructure(bool visible);

    /**
     * Show/hide tile chooser.
     *
     * @param   visible     show/hide tile chooser.
     */
    void visibleTiles(bool visible);

protected:

    /**
     * Handle application close event.
     *
     * @param   event       the close event.
     */
    void closeEvent(QCloseEvent * event) override;

    /**
     * Hanlde application show event.
     *
     * @param   event       the show event.
     */
    void showEvent(QShowEvent * event) override;

private:

    /**
     * Adds a filename to the list of recently used files.
     *
     * @param   fileName        a new recently used filename.
     */
    void addRecentFileName(QString const & fileName);

    /**
     * TODO: ?
     */
    void addUnusedActions();

    /**
     * Centers the window in the middle of the desktop.
     */
    void centerWindow();

    /**
     * Connect all actions known to the application.
     */
    void connectActions();

    /**
     * Connect the relevant signals of the model instance.
     */
    void connectModelSignals();

    /**
     * Clear the actions of the recent files.
     */
    void clearRecentFileActions();

    /**
     * Create the QActions for the recent files.
     */
    void createRecentFileActions();
    
    /**
     * Gets the current map widget shown.
     *
     * @return  the current map widget in the center.
     */
    MapWidget * getCurrentMapWidget();
    
    /**
     * Loads an atlas.
     * @param   fileName        the filename to load
     */
    void loadAtlas(QString fileName);

    /**
     * Load application settings.
     */
    void loadSettings();

    /**
     * Saves the current atlas to disk.
     *
     * @param   fileName        file to save the atlas to.
     * @return  true, if successfully saved
     */
    bool saveAtlas(QString fileName);

    /**
     * Saves the current application settings to disk.
     */
    void saveSettings();

    /**
     * Saves the list of recently used files to a settings instance.
     *
     * @param   settings        settings instance to be filled with the list.
     */
    void saveSettingsRecentFiles(QSettings & settings);

    /**
     * Save the current window size and position to a settings instance.
     *
     * @param   settings        settings instance to be filled.
     */
    void saveSettingsWindow(QSettings & settings);

    /**
     * Pre-create all dialogs.
     */
    void setupDialogs();

private slots:

    /**
     * Clears the list of recently used files.
     */
    void clearListOfRecentFiles();
    
    /**
     * The user selected a color.
     *
     * @param   color       the color the user selected.
     */
    void colorSelected(QColor color);
    
    /**
     * The user wants to create a totally new atlas.
     */
    void createNewAtlas();
    
    /**
     * A new map has been created.
     */
    void createNewMap();

    /**
     * A new region has been created.
     */
    void createNewRegion();
    
    /**
     * A map has been deleted.
     */
    void deleteMap();

    /**
     * A region has been deleted.
     */
    void deleteRegion();

    /**
     * A command has been executed.
     */
    void executedCommand();
    
    /**
     * Load action.
     */
    void load();

    /**
     * Loads the last used file.
     */
    void loadRecentFile();
    
    /**
     * Save atlas action.
     *
     * @return  true, if successfully saved
     */
    bool save();

    /**
     * Save atlas with a name action.
     *
     * @return  true, if successfully saved
     */
    bool saveAs();
    
    /**
     * The user selected a new tile.
     */
    void selectedTile();
    
    /**
     * The user selected a shape.
     *
     * @param   shapePath       resource path to the shape selected.
     */
    void shapeSelected(QString shapePath);
    
    /**
     * View the current map.
     */
    void viewCurrentMap();
    
    /**
     * Zoom of the active map changed.
     */
    void zoomChanged();
};


}
}


#endif
