/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_FIELD_POINTER_HPP
#define RPGMAPPER_MODEL_FIELD_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper::model {


// fwd
class Field;


/**
 * A smart pointer to a single field.
 */
using FieldPointer = QSharedPointer<Field>;


}


#endif
