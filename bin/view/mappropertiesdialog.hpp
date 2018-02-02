/*
 * mappropertiesdialog.hpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef VIEW_MAPPROPERTIESDIALOG_HPP
#define VIEW_MAPPROPERTIESDIALOG_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QDialog>

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


    /**
     * Reset all widgets to an initial state.
     */
    void reset();


private slots:


    /**
     * The height value changed.
     *
     * @param   nValue      the new value
     */
    void heightChanged(int nValue);


    /**
     * Select a font for the X Axis.
     */
    void selectXAxisFont();


    /**
     * Select a font for the Y Axis.
     */
    void selectYAxisFont();


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

    QFont m_cFontXAxis;                             /**< Font used for the X Axis. */
    QFont m_cFontYAxis;                             /**< Font used for the Y Axis. */
};


}
}


#endif
