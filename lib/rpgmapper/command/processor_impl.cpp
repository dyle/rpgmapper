/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/command.hpp>

#include "processor_impl.hpp"

using namespace rpgmapper::model::command;


void Processor::Impl::execute(CommandPointer & command) {
    redoList.clear();
    runCommand(command);
}


std::list<CommandPointer> const & Processor::Impl::getHistory() const {
    return history;
}


std::list<CommandPointer> const & Processor::Impl::getUndone() const {
    return redoList;
}


void Processor::Impl::redo() {
    if (redoList.empty()) {
        return;
    }
    auto command = redoList.back();
    redoList.pop_back();
    runCommand(command);
}


void Processor::Impl::runCommand(CommandPointer & command) {
    history.push_back(command);
    changes++;
    command->execute();
}


void Processor::Impl::undo() {
    if (history.empty()) {
        return;
    }
    auto command = history.back();
    history.pop_back();
    redoList.push_back(command);
    changes--;
    command->undo();
}
