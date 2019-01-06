/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_COMMAND_POINTER_HPP
#define RPGMAPPER_MODEL_COMMAND_COMMAND_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper::model::command {


// fwd
class Command;


/**
* A smart pointer to a single command.
*/
using CommandPointer = QSharedPointer<Command>;


}


#endif
