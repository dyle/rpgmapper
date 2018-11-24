/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_MAPPROPERTIESDIALOG_HPP
#define RPGMAPPER_VIEW_MAPPROPERTIESDIALOG_HPP

#include <memory>

#include <QDialog>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QRadioButton>

#include <rpgmapper/command/composite_command.hpp>
#include <rpgmapper/numerals.hpp>
#include "background_image_label.hpp"


// fwd
class Ui_mapPropertiesDialog;


namespace rpgmapper {
namespace view {


/**
 * This dialog lets the user fine tune all properties of a single map.
 */
class MapPropertiesDialog : public QDialog {

    Q_OBJECT

    std::shared_ptr<Ui_mapPropertiesDialog> ui;                 /**< The User Interface as created by the uic. */

    std::map<QString, QImage> backgroundImages;                 /**< All known background images. */
    BackgroundImageLabel * backgroundPreviewLabel;              /**< The background image preview widget. */

    /**
     * This structure holds all known numeral converters.
     */
    struct {
        QSharedPointer<rpgmapper::model::NumeralConverter> alphabeticalBigCaps;
        QSharedPointer<rpgmapper::model::NumeralConverter> alphabeticalSmallCaps;
        QSharedPointer<rpgmapper::model::NumeralConverter> numerical;
        QSharedPointer<rpgmapper::model::NumeralConverter> roman;
    } numeralConverters;

    std::list<QRadioButton *> xAxisNumeralButtons;          /**< List for each numeral converter on the x-axis. */
    std::list<QRadioButton *> yAxisNumeralButtons;          /**< List for each numeral converter on the y-axis. */
    
    /**
     * The current map we work on.
     */
    QString mapName;

public:

    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit MapPropertiesDialog(QWidget * parent);

    /**
     * Selects a new map to display.
     *
     * @param   mapName     The new map to display.
     */
    void setMap(QString mapName);

private:

    /**
     * Loads a file as background image and adds it as a possible selection for the background image.
     *
     * @param   fileInfo        Structure defining the file to load.
     */
    void addBackgroundImageFromFile(QFileInfo const & fileInfo);

    /**
     * Creates a composite command reflecting all changes to apply to the map in regard to the axis.
     *
     * @param   commands        commands needed to modify the map.
     * @param   newMapName      the (maybe new) name of the map
     */
    void applyAxisValuesToMap(rpgmapper::model::command::CompositeCommand * & commands, QString newMapName);
    
    /**
     * Creates a composite command reflecting all changes to apply to the map in regard to the background.
     *
     * @param   commands        commands needed to modify the map.
     * @param   newMapName      the (maybe new) name of the map
     */
    void applyBackgroundValuesToMap(rpgmapper::model::command::CompositeCommand * & commands, QString newMapName);
    
    /**
     * Creates a composite command reflecting all changes to apply to the map in regard to the dimension.
     *
     * @param   commands        commands needed to modify the map.
     * @param   newMapName      the (maybe new) name of the map
     */
    void applyDimensionValuesToMap(rpgmapper::model::command::CompositeCommand * & commands, QString newMapName);

    /**
     * Applies all user changes to the selected map.
     */
    void applyValuesToMap();

    /**
     * Collects all available background images.
     */
    void collectBackgroundImages();
    
    /**
     * Collects all available background images from the installed system sources.
     */
    void collectBackgroundImagesFromSystem();
    
    /**
     * Collects all available background images from user provided sources.
     */
    void collectBackgroundImagesFromUser();
    
    /**
     * Load all background images in a folder and below.
     */
    void collectBackgroundImagesInPath(QDir const & path);

    /**
     * Gets the selected image render mode as set by the user.
     *
     * @return  an ImageRenderMode enum value, as clicked by the user.
     */
    rpgmapper::model::ImageRenderMode getSelectedImageRenderMode() const;

    /**
     * Returns the margin the user has set for the map.
     *
     * @return  the margins as the user has defined them.
     */
    QMargins getSelectedMargins() const;

    /**
     * Returns the numeral converter for the X-Axis the user has set for the map.
     *
     * @return  the identifier for the X-Axis numeral converter.
     */
    QString getSelectedXAxisNumeral() const;
    
    /**
     * Returns the numeral converter for the Y-Axis the user has set for the map.
     *
     * @return  the identifier for the Y-Axis numeral converter.
     */
    QString getSelectedYAxisNumeral() const;

    /**
     * Init all numeral converters known.
     */
    void initNumeralConverters();

    /**
     * Checks if the properties the user switched are valid.
     *
     * @return  true, if there are no conflicting properties set.
     */
    bool isUserInputValid();

    /**
     * Applies the axis values from the map to the user interfaces.
     */
    void setAxisUiFromMap();
    
    /**
     * Applies the background map information to the user interface.
     */
    void setBackgroundUiFromMap();

    /**
     * Applies the dimension values of the map to the user interface.
     */
    void setDimensionUiFromMap();
    
    /**
     * Applies the X-Axis values from the map to the user interface.
     */
    void setXAxisUiFromMap();
    
    /**
     * Applies the Y-Axis values from the map to the user interface.
     */
    void setYAxisUiFromMap();

private slots:

    /**
     * The user selected a new image background for the map.
     *
     * @param   backgroundImage     The identifier for the new image.
     */
    void backgroundImageSelected(QString backgroundImage);

    /**
     * The user clicked the "Ok" (apply) button.
     */
    void clickedOk();

    /**
     * The user changed the map height value.
     *
     * @param   value       the new map height value.
     */
    void heightChanged(int value);

    /**
     * The user has selected a new axis color.
     */
    void selectAxisColor();
    
    /**
     * The user has selected a new axis font.
     */
    void selectAxisFont();
    
    /**
     * The user has selected a new background color.
     */
    void selectBackgroundColor();
    
    /**
     * The user has selected a new background image.
     */
    void selectBackgroundImage();
    
    /**
     * The user has selected a new grid color.
     */
    void selectGridColor();
    
    /**
     * The user has selected a new background image render mode.
     */
    void setBackgroundImageRenderMode();

    /**
     * Sets the background margins information to the user interface.
     */
    void setMargins();

    /**
     * Display the axis text as a sample for the X-Axis.
     */
    void showSampleXAxis();
    
    /**
     * Display the axis text as a sample for the Y-Axis.
     */
    void showSampleYAxis();

    /**
     * The user changed the width of the map.
     * @param   value       The new width value.
     */
    void widthChanged(int value);
};


}
}


#endif
