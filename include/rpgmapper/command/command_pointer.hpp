/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_COMMAND_POINTER_HPP
#define RPGMAPPER_MODEL_COMMAND_COMMAND_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper {
namespace model {
namespace command {


// fwd
class Command;


/**
* A smart pointer to a single command.
*/
using CommandPointer = QSharedPointer<Command>;


}
}
}


#endif