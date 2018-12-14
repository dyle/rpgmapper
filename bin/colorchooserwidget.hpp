/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_COLORCHOOSERWIDGET_HPP
#define RPGMAPPER_VIEW_COLORCHOOSERWIDGET_HPP

#include <map>
#include <memory>

#include <QColor>
#include <QFileDialog>
#include <QWidget>

#include <rpgmapper/colorpalette.hpp>


// fwd
class Ui_ColorChooserWidget;


namespace rpgmapper {
namespace view {


/**
 * This widget lets the user choose a color and a color palette (including load/save and recent colors).
 */
class ColorChooserWidget : public QWidget {

    Q_OBJECT
    
    std::shared_ptr<Ui_ColorChooserWidget> ui;                      /**< The User Interface as created by the uic. */
    
    std::map<QString, rpgmapper::model::ColorPalette> palettes;     /**< Known palettes. */
    
    QFileDialog * loadPaletteDialog = nullptr;                      /**< Load color palette dialog. */
    QFileDialog * savePaletteDialog = nullptr;                      /**< Save color palette dialog. */
    
public:
    
    /**
     * Constructor.
     *
     * @param   parent      The parent QWidget instance.
     */
    explicit ColorChooserWidget(QWidget * parent = nullptr);
    
public slots:
    
    /**
     * Loads the color palettes form the resources.
     */
    void loadPalettes();
    
private:
    
    /**
     * Changes the name of a color palette from an oldname to a new name.
     *
     * @param   oldName     old name of the color palette.
     * @param   newName     new name of the color palette.
     */
    void changeName(QString const & oldName, QString const & newName);
    
    /**
     * Checks if the given name is already assigned to a color palette.
     *
     * @param   name        the name queried.
     * @return  true, if the given name already denotes a color palette.
     */
    bool isNameAssigned(QString const & name) const;
    
    /**
     * Loads a color palette from a file and adds it to the atlas and this widget.
     *
     * @param   filename        name of the file to load.
     */
    void loadPaletteFromFile(QString filename);
    
    /**
     * Saves the current color palette to a file.
     *
     * @param   filename        the file name to save to.
     */
    void saveCurrentPaletteToFile(QString filename);
    
    /**
     * Suggests a new name which is not yet assigned to a color palette in this widget.
     *
     * @param   name        the name to base the new suggest on
     * @return  a new name which is not yet assigned to any color palette known to this widhget.
     */
    QString suggestNewName(QString const & name) const;
    
private slots:
    
    /**
     * A color has been selected in the color palette.
     */
    void colorSelectedInPalette();
    
    /**
     * A color has been selected in the list of recent colors.
     */
    void colorSelectedInRecentList();
    
    /**
     * Lets the user copy the current palette.
     */
    void copyPalette();
    
    /**
     * Lets the user edit the current palette.
     */
    void editPalette();
    
    /**
     * Lets the user load a new palette.
     */
    void loadPalette();

    /**
     * Lets the user picksa color.
     */
    void pickColor();

    /**
     * Lets the user save current palette.
     */
    void savePalette();
    
    /**
     * The user selected a new palette.
     */
    void selectedPaletteChanged();

signals:
    
    /**
     * A color has been selected by the user.
     *
     * @param   color       the color selected.
     */
    void colorSelected(QColor color);
};


}
}


#endif
