/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef VIEW_MAPPROPERTIESDIALOG_HPP
#define VIEW_MAPPROPERTIESDIALOG_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QDialog>
#include <QFile>
#include <QLabel>

#include <rpgmapper/types.hpp>
#include <rpgmapper/unitconverter.hpp>


// ------------------------------------------------------------
// decl


// fwd
class Ui_mappropertiesdialog;


namespace rpgmapper {
namespace view {


/**
 * A widget to let the user select the map's point of origin.
 */
class MapPropertiesDialog : public QDialog {


Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent         parent widget instance
     */
    explicit MapPropertiesDialog(QWidget * cParent);


public slots:


    /**
     * Evaluate all widgets anew.
     */
    void evaluate();


    /**
     * Set the map to be configured.
     *
     * @param   cMap        the map to be configured
     */
    void setMap(rpgmapper::model::MapPointer & cMap);


private slots:


    /**
     * The height value changed.
     *
     * @param   nValue      the new value
     */
    void heightChanged(int nValue);


    /**
     * Select a color for the axis.
     */
    void selectAxisColor();


    /**
     * Select a font for the axis.
     */
    void selectAxisFont();


    /**
     * Select a color for the background.
     */
    void selectBackgroundColor();


    /**
     * Select a image for the background.
     */
    void selectBackgroundImage();


    /**
     * The background image render mode changed.
     */
    void setBackgroundImageRenderMode();


    /**
     * Show examples for units on the X Axis.
     */
    void showSampleXAxis();


    /**
     * Show examples for units on the Y Axis.
     */
    void showSampleYAxis();


    /**
     * The width value changed.
     *
     * @param   nValue      the new value
     */
    void widthChanged(int nValue);


private:


    std::shared_ptr<Ui_mappropertiesdialog> ui;     /**< User interface. */

    rpgmapper::model::MapPointer m_cMap;            /**< The map to configure. */

    QFont m_cAxisFont;                              /**< Font used for the axis. */
    QColor m_cAxisColor;                            /**< Color for the axis. */
    QColor m_cBackgroundColor;                      /**< Color for the background. */
    QImage m_cBackgroundImage;                      /**< Background image for map. */
    QString m_sImageFile;                           /**< Path to background image file. */
    QLabel * m_cBackgroundPreview;                  /**< Preview of background image. */
};


}
}


#endif
