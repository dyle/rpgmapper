/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_COMMANDS_HPP
#define RPGMAPPER_MODEL_COMMAND_COMMANDS_HPP

#include <list>

#include <rpgmapper/command/command_pointer.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * A series of Command instances.
 */
using Commands = std::list<CommandPointer>;


}
}
}


#endif
