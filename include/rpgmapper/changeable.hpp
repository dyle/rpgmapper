/*
 * changeable.hpp
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


#ifndef MODEL_CHANGEABLE_HPP
#define MODEL_CHANGEABLE_HPP


// ------------------------------------------------------------
// incs

#include <QObject>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A changeable object knows if its inner state has been changed.
 */
class Changeable : public QObject {


    Q_OBJECT


public:


    /**
     * Ctor.
     *
     * @param   cParent     parent object
     */
    explicit Changeable(QObject * cParent = nullptr);


    /**
     * State if the object instance data has changed.
     *
     * This will also check any of the object's children.
     *
     * @return  true if the object instance data and any of its children has changed
     */
    virtual bool modified() const;


    /**
     * Set the object instance data changed flag.
     *
     * The new flag is also applied to any of the object's children.
     *
     * @param   bModified       the new object instance data changed flag
     */
    virtual void modified(bool bModified);


signals:


    /**
     * The object has changed.
     */
    void changed();


private:


    bool m_bModified;

};


}
}


#endif
