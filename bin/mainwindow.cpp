/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QStatusBar>

#include <rpgmapper/command/create_map.hpp>
#include <rpgmapper/command/create_region.hpp>
#include <rpgmapper/command/processor.hpp>
#include <rpgmapper/command/remove_map.hpp>
#include <rpgmapper/command/remove_region.hpp>
#include <rpgmapper/command/set_atlas_name.hpp>
#include <rpgmapper/command/set_region_name.hpp>
#include <rpgmapper/tile/tile_factory.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/atlas_name_validator.hpp>
#include <rpgmapper/region_name_validator.hpp>
#include <rpgmapper/session.hpp>

#include "mainwindow.hpp"
#include "shapecatalogsbox.hpp"
#include "visibility_action_filter.hpp"
#include "zoomslider.hpp"

#include "ui_mainwindow.h"

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;
using namespace rpgmapper::model::resource;
using namespace rpgmapper::model::tile;
using namespace rpgmapper::view;


MainWindow::MainWindow() : QMainWindow{} {

    ui = std::make_shared<Ui_mainwindow>();
    ui->setupUi(this);
    
    zoomSlider = new ZoomSlider{this};
    ui->mainToolBar->insertWidget(ui->actionShowAxis, zoomSlider);

    coordinatesWidget = new CoordinatesWidget{this};
    statusBar()->addPermanentWidget(coordinatesWidget);
    statusBar()->setSizeGripEnabled(false);
    statusBar()->setVisible(true);

    ui->mapTabWidget->clear();
    ui->atlasTreeNewMapToolButton->setDefaultAction(ui->actionCreateNewMap);
    ui->atlasTreeNewRegionToolButton->setDefaultAction(ui->actionCreateNewRegion);
    ui->atlasTreeDeleteMapToolButton->setDefaultAction(ui->actionDeleteMap);
    ui->atlasTreeDeleteRegionToolButton->setDefaultAction(ui->actionDeleteRegion);

    setupDialogs();
    connectActions();
    connectModelSignals();
    loadSettings();
    setApplicationWindowTitle();
    
    ui->atlasTreeWidget->selectFirstMap();
}


void MainWindow::addRecentFileName(QString const & fileName) {

    if (fileName.isEmpty()) {
        return;
    }

    if (!recentAtlasFileNames.contains(fileName)) {
        recentAtlasFileNames.push_front(fileName);
        while (recentAtlasFileNames.size() > maximumRecentAtlasFiles) {
            recentAtlasFileNames.removeLast();
        }
    }

    QFileInfo fileInfo(fileName);
    if (fileInfo.isFile()) {
        recentAtlasFolderName = fileInfo.absoluteDir().absolutePath();
    }

    createRecentFileActions();
}


void MainWindow::addUnusedActions() {
    addAction(ui->actionCloseMap);
    addAction(ui->actionCreateNewMap);
    addAction(ui->actionDeleteMap);
    addAction(ui->actionRedraw);
}


void MainWindow::applyResources() {
    mapPropertiesDialog->collectBackgroundImages();
    ui->shapeToolBox->applyResources();
    ui->colorPickerDockWidgetContents->loadPalettes();
}


void MainWindow::centerWindow() {

    auto desktop = dynamic_cast<QApplication *>(QApplication::instance())->desktop();
    auto width = static_cast<int>(desktop->width() * 0.8);
    auto height = static_cast<int>(desktop->height() * 0.8);
    int x = (desktop->width() - width) / 2;
    int y = (desktop->height() - height) / 2;

    resize(QSize{width, height});
    move(QPoint{x, y});
}


void MainWindow::clearListOfRecentFiles() {

    for (auto & cAction: recentFileLoadActions) {
        delete cAction;
    }
    recentFileLoadActions.clear();
    recentAtlasFileNames.clear();

    enableActions();
}


void MainWindow::clearRecentFileActions() {

    for (auto & actionInMenu : ui->openRecentMenu->actions()) {
        if (actionInMenu != ui->actionClearRecentList) {
            ui->openRecentMenu->removeAction(actionInMenu);
        }
    }
    for (auto & action : recentFileLoadActions) {
        action->deleteLater();
    }
    recentFileLoadActions.clear();
}


void MainWindow::closeEvent(QCloseEvent * event) {
    saveSettings();
    QMainWindow::closeEvent(event);
}


void MainWindow::colorSelected(QColor color) {
    auto tile = TileFactory::create(TileType::color, {{"color", color.name()}});
    auto session = Session::getCurrentSession();
    session->setCurrentTile(tile);
}


void MainWindow::connectActions() {

    addUnusedActions();

    connect(ui->actionClearRecentList, &QAction::triggered, this, &MainWindow::clearListOfRecentFiles);
    connect(ui->actionCloseMap, &QAction::triggered, ui->mapTabWidget, &MapTabWidget::closeCurrentMap);
    connect(ui->actionCreateNew, &QAction::triggered, this, &MainWindow::createNewAtlas);
    connect(ui->actionCreateNewMap, &QAction::triggered, this, &MainWindow::createNewMap);
    connect(ui->actionCreateNewRegion, &QAction::triggered, this, &MainWindow::createNewRegion);
    connect(ui->actionDeleteMap, &QAction::triggered, this, &MainWindow::deleteMap);
    connect(ui->actionDeleteRegion, &QAction::triggered, this, &MainWindow::deleteRegion);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionOpenAtlasFile, &QAction::triggered, this, &MainWindow::load);
    connect(ui->actionRedraw, &QAction::triggered, ui->mapTabWidget, &MapTabWidget::redrawCurrentMap);
    connect(ui->actionRotateTileLeft, &QAction::triggered, this, &MainWindow::rotateTileLeft);
    connect(ui->actionRotateTileRight, &QAction::triggered, this, &MainWindow::rotateTileRight);
    connect(ui->actionShowAboutDialog, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(ui->actionShowAtlasProperties, &QAction::triggered, this, &MainWindow::editAtlasProperties);
    connect(ui->actionShowMapProperties, &QAction::triggered, this, &MainWindow::editMapProperties);
    connect(ui->actionShowRegionProperties, &QAction::triggered, this, &MainWindow::editRegionProperties);
    connect(ui->actionSaveAtlasFile, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionSaveAtlasFileAs, &QAction::triggered, this, &MainWindow::saveAs);
    connect(ui->actionViewResources, &QAction::triggered, this, &MainWindow::showResourcesViewDialog);

    connect(ui->actionViewMap, &QAction::triggered, this, &MainWindow::viewCurrentMap);
    connect(ui->actionViewColorPicker, &QAction::triggered, this, &MainWindow::visibleColorPicker);
    connect(ui->actionViewMinimap, &QAction::triggered, this, &MainWindow::visibleMinimap);
    connect(ui->actionViewShapesDock, &QAction::triggered, this, &MainWindow::visibleTiles);
    connect(ui->actionViewStructureTree, &QAction::triggered, this, &MainWindow::visibleStructure);
    connect(ui->actionViewCurrentTile, &QAction::triggered, this, &MainWindow::visibleCurrentTile);
    new VisibilityActionFiler(ui->miniMapDockWidget, ui->actionViewMinimap, this);
    new VisibilityActionFiler(ui->atlasStructureDockWidget, ui->actionViewStructureTree, this);
    new VisibilityActionFiler(ui->shapesDockWidget, ui->actionViewShapesDock, this);
    new VisibilityActionFiler(ui->colorPickerDockWidget, ui->actionViewColorPicker, this);
    new VisibilityActionFiler(ui->currentTileWidget, ui->actionViewCurrentTile, this);
    
    connect(ui->actionShowAxis, &QAction::toggled, this, &MainWindow::toogleCurrentAxisVisibility);
    connect(ui->actionShowGrid, &QAction::toggled, this, &MainWindow::toogleCurrentGridVisibility);

    connect(ui->atlasTreeWidget, &StructuralTreeWidget::doubleClickedAtlas,
            ui->actionShowAtlasProperties, &QAction::trigger);
    connect(ui->atlasTreeWidget, &StructuralTreeWidget::doubleClickedMap,
            ui->actionShowMapProperties, &QAction::trigger);
    connect(ui->atlasTreeWidget, &StructuralTreeWidget::doubleClickedRegion,
            ui->actionShowRegionProperties, &QAction::trigger);
    connect(ui->atlasTreeWidget, &StructuralTreeWidget::selectedMap, ui->mapTabWidget, &MapTabWidget::selectMap);

    connect(ui->mapTabWidget, &QTabWidget::currentChanged, this, &MainWindow::enableActions);
    connect(ui->mapTabWidget, &MapTabWidget::hoverCoordinates, this, &MainWindow::showCoordinates);
    connect(ui->mapTabWidget, &MapTabWidget::decreaseZoom, zoomSlider, &ZoomSlider::decrease);
    connect(ui->mapTabWidget, &MapTabWidget::increaseZoom, zoomSlider, &ZoomSlider::increase);
    connect(ui->mapTabWidget, &MapTabWidget::rotateTileLeft, this, &MainWindow::rotateTileLeft);
    connect(ui->mapTabWidget, &MapTabWidget::rotateTileRight, this, &MainWindow::rotateTileRight);
    
    connect(ui->colorPickerDockWidgetContents, &ColorChooserWidget::colorSelected, this, &MainWindow::colorSelected);
    
    connect(ui->shapeToolBox, &ShapeCatalogsBox::shapeSelected, this, &MainWindow::shapeSelected);
    
    connect(zoomSlider, &ZoomSlider::zoomChanged, this, &MainWindow::zoomChanged);
}


void MainWindow::connectModelSignals() {
    
    auto session = Session::getCurrentSession();
    auto atlas = session->getAtlas();
    auto processor = session->getCommandProcessor();
    
    connect(processor.data(), &Processor::commandExecuted, this, &MainWindow::executedCommand);
    connect(atlas.data(), &Nameable::nameChanged, this, &MainWindow::setApplicationWindowTitle);
    
    connect(session.data(),
            &Session::newLastAppliedTile,
            ui->colorPickerDockWidgetContents,
            &ColorChooserWidget::appliedTile);
    connect(session.data(), &Session::selectedAtlas, this, &MainWindow::enableActions);
    connect(session.data(), &Session::selectedMap, this, &MainWindow::enableActions);
    connect(session.data(), &Session::selectedMap, ui->atlasTreeWidget, &StructuralTreeWidget::selectMap);
    connect(session.data(), &Session::selectedRegion, this, &MainWindow::enableActions);
    connect(session.data(), &Session::selectedRegion, ui->atlasTreeWidget, &StructuralTreeWidget::selectRegion);
    connect(session.data(), &Session::selectedTile, this, &MainWindow::selectedTile);
}


void MainWindow::createNewAtlas() {
    
    auto session = Session::getCurrentSession();
    bool createNew = !session->isModified();
    
    if (session->isModified()) {
        
        auto answer = QMessageBox::question(this, tr("Save Atlas"), tr("The current atlas has modifications. Save?"));
        if (answer == QMessageBox::Yes) {
            createNew = save();
        }
        else
        if (answer == QMessageBox::No) {
            createNew = true;
        }
    }
    
    if (createNew) {
    
        Session::setCurrentSession(Session::init());
        applyResources();
        
        ui->mapTabWidget->removeAllMaps();
        ui->atlasTreeWidget->resetStructure();
        connectModelSignals();
        setApplicationWindowTitle();
        ui->atlasTreeWidget->selectFirstMap();
    }
}


void MainWindow::createNewMap() {
    
    auto session = Session::getCurrentSession();
    auto regionName = session->getCurrentRegionName();
    if (!regionName.isEmpty()) {
        auto processor = session->getCommandProcessor();
        auto command = CommandPointer{new CreateMap{regionName, session->createNewMapName()}};
        processor->execute(command);
    }
}


void MainWindow::createNewRegion() {
    
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    auto newRegionName = session->createNewRegionName();
    auto command = CommandPointer{new CreateRegion{newRegionName}};
    processor->execute(command);
    session->selectRegion(newRegionName);
}


void MainWindow::createRecentFileActions() {

    clearRecentFileActions();

    for (auto const & fileName: recentAtlasFileNames) {

        auto loadRecentFileAction = new QAction(this);
        loadRecentFileAction->setObjectName(fileName);
        loadRecentFileAction->setText(fileName);
        connect(loadRecentFileAction, &QAction::triggered, this, &MainWindow::loadRecentFile);

        recentFileLoadActions.push_back(loadRecentFileAction);
    }

    ui->openRecentMenu->insertActions(ui->actionClearRecentList, recentFileLoadActions);
    ui->openRecentMenu->insertSeparator(ui->actionClearRecentList);

    enableActions();
}


void MainWindow::deleteMap() {
    
    auto session = Session::getCurrentSession();
    auto mapName = session->getCurrentMapName();
    if (!session->findMap(mapName)->isValid()) {
        throw std::runtime_error{"Current selected map vanished while tyring to delete it."};
    }
    
    auto command = CommandPointer{new RemoveMap{mapName}};
    auto processor = session->getCommandProcessor();
    processor->execute(command);
    
    ui->mapTabWidget->removeMap(mapName);
}


void MainWindow::deleteRegion() {
    
    auto session = Session::getCurrentSession();
    auto regionName = session->getCurrentRegionName();
    auto region = session->findRegion(regionName);
    if (!region->isValid()) {
        throw std::runtime_error{"Current selected region vanished while tyring to delete it."};
    }
    
    auto mapNamesOfRegion = region->getMapNames();
    if (!mapNamesOfRegion.empty()) {
        auto question = tr("Region '%1' has maps.\nThis will remove them all too. Continue?").arg(region->getName());
        auto answer = QMessageBox::question(this, tr("Delete region and all maps in it?"), question);
        if (answer != QMessageBox::Yes) {
            return;
        }
    }
    
    auto command = CommandPointer{new RemoveRegion{region->getName()}};
    auto processor = session->getCommandProcessor();
    processor->execute(command);
    
    for (const auto & map : mapNamesOfRegion) {
        ui->mapTabWidget->removeMap(map);
    }
    
    session->selectAtlas();
}


void MainWindow::editAtlasProperties() {

    QString message = tr("Choose new name of atlas.");
    
    auto session = Session::getCurrentSession();
    auto atlas = session->getAtlas();
    auto processor = session->getCommandProcessor();

    bool abortLoop = false;
    do {

        bool ok = false;
        auto atlasName = QInputDialog::getText(this,
                                               tr("Atlas Properties"),
                                               message,
                                               QLineEdit::Normal,
                                               atlas->getName(),
                                               &ok);
        if (!ok) {
            abortLoop = true;
        }
        else {
            if (!AtlasNameValidator::isValid(atlasName)) {
                QMessageBox::critical(this,
                                      tr("Refused to change name of atlas"),
                                      tr("Name is empty or contains invalid characters."));
            }
            else {
                auto command = CommandPointer{new SetAtlasName{atlasName}};
                processor->execute(command);
                abortLoop = true;
            }
        }
        
    } while (!abortLoop);
}


void MainWindow::editMapProperties() {
    
    auto session = Session::getCurrentSession();
    auto mapName = session->getCurrentMapName();
    
    if (!mapName.isEmpty()) {
        mapPropertiesDialog->setMap(mapName);
        mapPropertiesDialog->exec();
    }
}


void MainWindow::editRegionProperties() {

    QString message = tr("Choose new name of region.");
    
    auto session = Session::getCurrentSession();
    auto regionName = session->getCurrentRegionName();
    if (regionName.isEmpty()) {
        return;
    }
    auto processor = session->getCommandProcessor();
    
    bool abortLoop = false;
    do {

        bool ok = false;
        auto newRegionName = QInputDialog::getText(this,
                                                   tr("Region Properties"),
                                                   message,
                                                   QLineEdit::Normal,
                                                   regionName,
                                                   &ok);
        if (!ok) {
            abortLoop = true;
        }
        else {
            if (!RegionNameValidator::isValid(newRegionName)) {
                QMessageBox::critical(this,
                                      tr("Refused to change name of region"),
                                      tr("Name is empty or contains invalid characters."));
            }
            else
            if (session->findRegion(newRegionName)->isValid()) {
                QMessageBox::critical(this,
                                      tr("Refused to change name of region"),
                                      tr("A region with this name already exists."));
            }
            else {
                auto command = CommandPointer{new SetRegionName{regionName, newRegionName}};
                processor->execute(command);
                session->selectRegion(newRegionName);
                abortLoop = true;
            }
        }

    } while (!abortLoop);
}


void MainWindow::enableActions() {
    
    auto session = Session::getCurrentSession();
    auto currentMapName = session->getCurrentMapName();
    auto currentRegionName = session->getCurrentRegionName();
    auto currentTile = session->getCurrentTile();
    
    ui->actionClearRecentList->setEnabled(!recentAtlasFileNames.empty());
    ui->actionCloseMap->setEnabled(ui->mapTabWidget->currentWidget() != nullptr);
    ui->actionCreateNewMap->setEnabled(!currentRegionName.isEmpty());
    ui->actionDeleteMap->setEnabled(!currentMapName.isEmpty());
    ui->actionDeleteRegion->setEnabled(!currentRegionName.isEmpty());
    ui->actionShowMapProperties->setEnabled(!currentMapName.isEmpty());
    ui->actionShowRegionProperties->setEnabled(!currentRegionName.isEmpty());
    ui->actionViewMap->setEnabled(!currentMapName.isEmpty());
    
    auto mapWidget = getCurrentMapWidget();
    ui->actionShowAxis->setEnabled(mapWidget);
    ui->actionShowGrid->setEnabled(mapWidget);
    if (mapWidget) {
        zoomSlider->setTileSize(mapWidget->getTileSize());
        ui->actionShowAxis->setChecked(mapWidget->isAxisVisible());
        ui->actionShowGrid->setChecked(mapWidget->isGridVisible());
    }
    
    ui->actionRotateTileLeft->setEnabled(currentTile != nullptr);
    ui->actionRotateTileRight->setEnabled(currentTile != nullptr);
}


void MainWindow::executedCommand() {
    setApplicationWindowTitle();
}


MapWidget * MainWindow::getCurrentMapWidget() {
    auto * mapScrollArea = dynamic_cast<MapScrollArea *>(ui->mapTabWidget->currentWidget());
    return mapScrollArea ? dynamic_cast<MapWidget *>(mapScrollArea->widget()) : nullptr;
}

void MainWindow::load() {

    auto nAnswer = loadAtlasDialog->exec();
    if ((nAnswer == 0) || loadAtlasDialog->selectedFiles().empty()) {
        return;
    }
    loadAtlas(loadAtlasDialog->selectedFiles().first());
}


void MainWindow::loadAtlas(QString fileName) {

    QFile file{fileName};
    QStringList log;
    
    SessionPointer newSession;
    if (!Session::load(newSession, file, log)) {
        logDialog->setWindowTitle(tr("Load atlas failure"));
        logDialog->clear();
        logDialog->setMessage(tr("Failed to load atlas file."));
        logDialog->setLog(log);
        logDialog->exec();
    }
    else {
    
        Session::setCurrentSession(newSession);
        applyResources();
        
        ui->mapTabWidget->removeAllMaps();
        ui->atlasTreeWidget->resetStructure();
        connectModelSignals();
        setApplicationWindowTitle();
        
        addRecentFileName(fileName);
    }
}


void MainWindow::loadRecentFile() {

    auto action = dynamic_cast<QAction *>(sender());
    if (!action) {
        return;
    }

    // we could use cAction->text(). However, Qt automagically adds
    // the shortcut literal '&' to the text, disturbing the file name.
    loadAtlas(action->objectName());
}


void MainWindow::loadSettings() {

    QSettings settings{"rpgmapper", "rpgmapper"};

    if (settings.contains("geometry")) {
        restoreGeometry(settings.value("geometry").toByteArray());
    }
    else {
        centerWindow();
    }
    restoreState(settings.value("windowState").toByteArray());

    maximumRecentAtlasFiles = settings.value("recent/maximum", 10).toInt();
    recentAtlasFolderName = settings.value("recent/folder").toString();
    recentAtlasFileNames.clear();
    for (int i = 0; i < maximumRecentAtlasFiles; ++i) {
        QString fileName = settings.value("recent/file-" + QString::number(i), "").toString();
        if (!fileName.isEmpty()) {
            recentAtlasFileNames.append(fileName);
        }
    }
    createRecentFileActions();

    if (!recentAtlasFolderName.isEmpty()) {
        loadAtlasDialog->setDirectory(recentAtlasFolderName);
        saveAtlasDialog->setDirectory(recentAtlasFolderName);
    }
    
    auto lastColorPaletteFolder = settings.value("recent/lastColorPaletteFolder").toString();
    ui->colorPickerDockWidgetContents->setLastFolderUsed(lastColorPaletteFolder);
    
    auto lastResourceSaveFolder = settings.value("recent/lastResourceSaveFolder").toString();
    resourcesViewDialog->setLastFolderUsed(lastResourceSaveFolder);
}


void MainWindow::rotateTileLeft() {
    
    auto session = Session::getCurrentSession();
    auto tile = session->getCurrentTile();
    if (!tile) {
        return;
    }
    
    tile->rotateLeft();
    ui->currentTileWidget->update();
}


void MainWindow::rotateTileRight() {
    
    auto session = Session::getCurrentSession();
    auto tile = session->getCurrentTile();
    if (!tile) {
        return;
    }
    
    tile->rotateRight();
    ui->currentTileWidget->update();
}


bool MainWindow::save() {
    
    auto session = Session::getCurrentSession();
    if (session->getFileName().isEmpty()) {
        return saveAs();
    }
    return saveAtlas(session->getFileName());
}


bool MainWindow::saveAs() {

    auto answer = saveAtlasDialog->exec();
    if ((answer == 0) || saveAtlasDialog->selectedFiles().empty()) {
        return false;
    }
    return saveAtlas(saveAtlasDialog->selectedFiles().first());
}


bool MainWindow::saveAtlas(QString fileName) {
    
    QFile file{fileName};
    QStringList log;

    bool saved = false;
    
    auto session = Session::getCurrentSession();
    if (!session->save(file, log)) {
        logDialog->setWindowTitle(tr("Save atlas failure"));
        logDialog->clear();
        logDialog->setMessage(tr("Failed to save atlas file."));
        logDialog->setLog(log);
        logDialog->exec();
    }
    else {
        addRecentFileName(session->getFileName());
        session->getCommandProcessor()->resetModifications();
        setApplicationWindowTitle();
        saved = true;
    }
    
    return saved;
}


void MainWindow::saveSettings() {
    
    QSettings settings{"rpgmapper", "rpgmapper"};
    
    saveSettingsWindow(settings);
    saveSettingsRecentFiles(settings);
    
    settings.setValue("recent/lastColorPaletteFolder", ui->colorPickerDockWidgetContents->getLastUsedFolder());
    settings.setValue("recent/lastResourceSaveFolder", resourcesViewDialog->getLastUsedFolder());
}


void MainWindow::saveSettingsRecentFiles(QSettings & settings) {

    settings.remove("recent");
    settings.setValue("recent/maximum", maximumRecentAtlasFiles);
    settings.setValue("recent/folder", recentAtlasFolderName);

    int fileIndex = 0;
    for (auto const & fileName : recentAtlasFileNames){
        settings.setValue("recent/file-" + QString::number(++fileIndex), fileName);
        if (fileIndex >= maximumRecentAtlasFiles) {
            break;
        }
    }
}


void MainWindow::saveSettingsWindow(QSettings & settings) {
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}


void MainWindow::selectedTile() {
    
    auto session = Session::getCurrentSession();
    auto tile = session->getCurrentTile();
    
    ui->currentTileWidget->setCurrentTile(tile);
    enableActions();
}


void MainWindow::setApplicationWindowTitle() {
    
    auto session = Session::getCurrentSession();
    auto atlas = session->getAtlas();
    auto processor = session->getCommandProcessor();
    
    auto changed = processor->modifications() == 0 ? "" : " * ";
    auto title = QString("%1%2 - %3").arg(atlas->getName()).arg(changed).arg(qApp->applicationName());
    setWindowTitle(title);
}


void MainWindow::setupDialogs() {

    QStringList fileNameFilters;
    fileNameFilters << tr("Atlas files [*.atlas] (*.atlas)")
                    << tr("Any files [*.*] (*)");

    aboutDialog = new AboutDialog(this);

    loadAtlasDialog = new QFileDialog(this);
    loadAtlasDialog->setFileMode(QFileDialog::ExistingFile);
    loadAtlasDialog->setNameFilters(fileNameFilters);
    loadAtlasDialog->setAcceptMode(QFileDialog::AcceptOpen);
    loadAtlasDialog->setWindowTitle(tr("Load Atlas file"));
    loadAtlasDialog->setDirectory(recentAtlasFolderName);

    logDialog = new LogDialog(this);

    mapPropertiesDialog = new MapPropertiesDialog(this);
    
    resourcesViewDialog = new ResourcesViewDialog(this);

    saveAtlasDialog = new QFileDialog(this);
    saveAtlasDialog->setFileMode(QFileDialog::AnyFile);
    saveAtlasDialog->setNameFilters(fileNameFilters);
    saveAtlasDialog->setAcceptMode(QFileDialog::AcceptSave);
    saveAtlasDialog->setWindowTitle(tr("Save Atlas file"));
    saveAtlasDialog->setDirectory(recentAtlasFolderName);
}


void MainWindow::shapeSelected(QString shapePath) {
    auto tile = TileFactory::create(TileType::shape, {{"path", shapePath}});
    auto session = Session::getCurrentSession();
    session->setCurrentTile(tile);
}


void MainWindow::showAboutDialog() {
    aboutDialog->exec();
}


void MainWindow::showCoordinates(int x, int y) {
    
    auto session = Session::getCurrentSession();
    auto mapName = session->getCurrentMapName();
    
    if (!mapName.isEmpty()) {
        auto map = session->findMap(mapName);
        if (map->isValid()) {
            
            auto coordinateSystem = map->getCoordinateSystem();
            auto mapPoint = coordinateSystem->translateToMap(QPoint{x, y});
            coordinatesWidget->showCoordinates(coordinateSystem->getNumeralCoordinates(mapPoint.x(), mapPoint.y()));
        }
        else {
            coordinatesWidget->clear();
        }
    }
}


void MainWindow::showResourcesViewDialog() {
    resourcesViewDialog->exec();
}


void MainWindow::showEvent(QShowEvent * cEvent) {

    QMainWindow::showEvent(cEvent);

    static bool bFirstTime = true;
    if (bFirstTime) {

        // ugly hack, since I did not investigate how Qt saves
        // the visibility state in the saveState() and restoreState()
        // methods of the QDockWindow children --> anyone?
        ui->actionViewMinimap->setChecked(ui->miniMapDockWidget->isVisible());
        ui->actionViewShapesDock->setChecked(ui->shapesDockWidget->isVisible());
        ui->actionViewStructureTree->setChecked(ui->atlasStructureDockWidget->isVisible());
        bFirstTime = false;
    }
}


void MainWindow::toogleCurrentAxisVisibility() {
    auto mapWidget = getCurrentMapWidget();
    if (mapWidget) {
        mapWidget->setAxisVisible(ui->actionShowAxis->isChecked());
    }
}


void MainWindow::toogleCurrentGridVisibility() {
    auto mapWidget = getCurrentMapWidget();
    if (mapWidget) {
        mapWidget->setGridVisible(ui->actionShowGrid->isChecked());
    }
}


void MainWindow::viewCurrentMap() {
    auto session = Session::getCurrentSession();
    auto currentMapName = session->getCurrentMapName();
    if (!currentMapName.isEmpty()) {
        ui->mapTabWidget->selectMap(currentMapName);
    }
}


void MainWindow::visibleColorPicker(bool visible) {
    ui->colorPickerDockWidget->setVisible(visible);
}


void MainWindow::visibleCurrentTile(bool visible) {
    ui->currentTileWidget->setVisible(visible);
}


void MainWindow::visibleMinimap(bool visible) {
    ui->miniMapDockWidget->setVisible(visible);
}


void MainWindow::visibleStructure(bool visible) {
    ui->atlasStructureDockWidget->setVisible(visible);
}


void MainWindow::visibleTiles(bool visible) {
    ui->shapesDockWidget->setVisible(visible);
}


void MainWindow::zoomChanged() {
    auto mapWidget = getCurrentMapWidget();
    if (mapWidget) {
        mapWidget->setTileSize(zoomSlider->getTileSize());
    }
}
