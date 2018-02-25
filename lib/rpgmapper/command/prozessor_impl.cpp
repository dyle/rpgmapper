/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "prozessor_impl.hpp"

using namespace rpgmapper::model::command;


void Prozessor::Impl::execute(CommandPointer & command) {
    redoList.clear();
    runCommand(command);
}


Commands const & Prozessor::Impl::getHistory() const {
    return history;
}


Commands const & Prozessor::Impl::getUndone() const {
    return redoList;
}


void Prozessor::Impl::redo() {
    if (redoList.empty()) {
        return;
    }
    auto command = redoList.back();
    redoList.pop_back();
    runCommand(command);
}

void Prozessor::Impl::runCommand(CommandPointer & command) {
    history.push_back(command);
    changes++;
    command->execute();
}


void Prozessor::Impl::undo() {
    if (history.empty()) {
        return;
    }
    auto command = history.back();
    history.pop_back();
    redoList.push_back(command);
    command->undo();
    changes--;
}
