/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_COMMAND_POINTER_HPP
#define RPGMAPPER_MODEL_COMMAND_COMMAND_POINTER_HPP

#include <list>

#include <QSharedPointer>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
* A smart pointer to a single command.
*/
using CommandPointer = QSharedPointer<Command>;


}
}
}


#endif
