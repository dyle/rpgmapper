/*
 * clickable_label.h
 *
 * A QLabel which can be clicked
 * 
 * Copyright (C) 2015, Oliver Maurhart, <dyle@dyle.org>
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


#ifndef __VIEW_CLICKABLE_LABEL_H
#define __VIEW_CLICKABLE_LABEL_H
 

// ------------------------------------------------------------
// incs

// Qt
#include <QLabel>

#include "common_macros.h"


// ------------------------------------------------------------
// decl


/**
 * a QLabel which emits clicked() signals
 */
class clickable_label : public QLabel {


    Q_OBJECT


public:


    /**
     * ctor
     *
     * @param   cParent     parent widget
     * @param   f           Window Flags
     */
    clickable_label(QWidget * cParent = 0, Qt::WindowFlags f = 0) : QLabel(cParent, f) {};


    /**
     * ctor
     *
     * @param   sText       initial label text
     * @param   cParent     parent widget
     * @param   f           Window Flags
     */
    clickable_label(QString const & sText, QWidget * cParent = 0, Qt::WindowFlags f = 0) : QLabel(sText, cParent, f) {};


    /**
     * dtor
     */
    virtual ~clickable_label() {};


signals:


    /**
     * label has been clicked
     */
    void clicked();


protected:


    /**
     * handle mouse release events
     *
     * @param   cEvent      the event passed
     */
    void mouseReleaseEvent(UNUSED QMouseEvent * cEvent) { emit clicked(); };


};


#endif

