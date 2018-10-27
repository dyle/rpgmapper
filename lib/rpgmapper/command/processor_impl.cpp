/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "processor_impl.hpp"

using namespace rpgmapper::model::command;


void Processor::Impl::execute(QSharedPointer<rpgmapper::model::command::Command> & command) {
    redoList.clear();
    runCommand(command);
}


std::list<QSharedPointer<rpgmapper::model::command::Command>> const & Processor::Impl::getHistory() const {
    return history;
}


std::list<QSharedPointer<rpgmapper::model::command::Command>> const & Processor::Impl::getUndone() const {
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


void Processor::Impl::runCommand(QSharedPointer<rpgmapper::model::command::Command> & command) {
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
