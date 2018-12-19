/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_SHAPE_POINTER_HPP
#define RPGMAPPER_MODEL_SHAPE_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper {
namespace model {


// fwd
class Shape;


/**
 * A smart pointer to a shape.
 */
using ShapePointer = QSharedPointer<Shape>;


}
}


#endif
