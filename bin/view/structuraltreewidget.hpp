/*
 * structuraltreewidget.hpp
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


#ifndef VIEW_STRUCTURALTREEWIDGET_HPP
#define VIEW_STRUCTURALTREEWIDGET_HPP


// ------------------------------------------------------------
// incs

// Qt
#include <QTreeWidget>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace view {


/**
 * A QTreeWidget which displays the Atlas structure.
 */
class StructuralTreeWidget : public QTreeWidget {


    Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent     parent widget
     */
    explicit StructuralTreeWidget(QWidget * cParent = nullptr);


public slots:


    /**
     * Reset structure (builds Atlas structure anew)
     */
    void resetStructure();

};


}
}


#endif
