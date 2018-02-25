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


Commands const & Prozessor::getHistory() const {
    return impl->getHistory();
}


Commands const & Prozessor::getUndone() const {
    return impl->getUndone();
}


int Prozessor::modifications() const {
    return impl->modifications();
}


void Prozessor::redo() {
    impl->redo();
}


void Prozessor::undo() {
    impl->undo();
}
