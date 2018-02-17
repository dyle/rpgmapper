/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MAINWINDOW_HPP
#define RPGMAPPER_MAINWINDOW_HPP


#include <memory>

#include <QMainWindow>
#include <QSettings>

#include <rpgmapper/atlas.hpp>


namespace rpgmapper {
namespace view {


class MainWindow : public QMainWindow {

    Q_OBJECT

    class Impl;
    std::shared_ptr<MainWindow::Impl> impl;

public:

    MainWindow();

    rpgmapper::model::AtlasPointer getAtlas();

    rpgmapper::model::AtlasPointer const getAtlas() const;

protected:

    void closeEvent(QCloseEvent * event) override;

    void showEvent(QShowEvent * event) override;

private:

    void centerWindow();

    void connectActions();

    void loadSettings();

    void saveSettings();

    void saveSettingsWindow(QSettings & settings);

    void setupDialogs();
};


}
}


#endif







#if 0

class MainWindow : public QMainWindow {

    Q_OBJECT

    class Impl;
    std::shared_ptr<MainWindow::Impl> impl;

public:

    MainWindow();

public slots:

    void editAtlasProperties();

    void editMapProperties();

    void editRegionProperties();

    void enableActions();

    void deleteMap();

    void deleteRegion();

    void newMap();

    void newRegion();

    void resetAtlas();

    void showCoordinates(int x, int y);

    void visibleMinimap(bool bView);

    void visibleStructure(bool bView);

    void visibleTiles(bool bView);

protected:

    void closeEvent(QCloseEvent * cEvent) override;

    void showEvent(QShowEvent * cEvent) override;

private slots:

    void changedAtlas();

    void clearListOfRecentFiles();

    void load();

    void loadRecentFile();

    void save();

    void saveAs();

private:

    void addRecentFileName(QString const & sFileName);

    void centerWindow();

    void clearRecentFileActions();

    void connectActions();

    void createRecentFileActions();

    void loadAtlas(QString const & sFileName);

    void loadSettings();

    void saveAtlas(QString const & sFileName);

    void saveSettings();

    void saveSettingsRecentFiles(QSettings & cSettings);

    void saveSettingsWindow(QSettings & cSettings);

    void setupDialogs();

    void showAboutDialog();


};


}
}


#endif
