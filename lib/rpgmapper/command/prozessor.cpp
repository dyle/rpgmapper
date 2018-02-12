/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/prozessor.hpp>
#include "prozessor_impl.hpp"

using namespace rpgmapper::model::command;


Prozessor::Prozessor() {
    impl = std::make_shared<Prozessor::Impl>();
}


void Prozessor::execute(CommandPointer command) {
    impl->execute(command);
}


Commands const & Prozessor::getList() const {
    return impl->getList();
}


void Prozessor::redo() {
    impl->redo();
}


void Prozessor::undo() {
    impl->undo();
}
