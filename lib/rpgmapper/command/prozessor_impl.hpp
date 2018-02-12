/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_PROZESSOR_IMPL_HPP
#define RPGMAPPER_MODEL_COMMAND_PROZESSOR_IMPL_HPP


#include <rpgmapper/command/prozessor.hpp>

using namespace rpgmapper::model;


namespace rpgmapper {
namespace model {
namespace command {


class Prozessor::Impl final {

    Commands history;
    Commands redoList;

public:

    void execute(CommandPointer command);

    Commands const & getHistory() const;

    Commands const & getUndone() const;

    void redo();

    void undo();

};


}
}
}


#endif
