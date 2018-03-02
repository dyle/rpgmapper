/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/composite_command.hpp>

using namespace rpgmapper::model::command;


void CompositeCommand::addCommand(CommandPointer command) {
    commands.push_back(command);
}


void CompositeCommand::clearCommands() {
    commands.clear();
}


QString CompositeCommand::getDescription() const {

    QStringList commandDescriptions;
    for (auto iter = std::begin(commands); iter != std::end(commands); ++iter) {
        commandDescriptions << (*iter)->getDescription();
    }

    return QString{"Composite command of [%1]."}.arg(commandDescriptions.join(", "));
}


void CompositeCommand::execute() {
    for (auto iter = std::begin(commands); iter != std::end(commands); ++iter) {
        (*iter)->execute();
    }
}


void CompositeCommand::undo() {
    for (auto iter = std::rbegin(commands); iter != std::rend(commands); ++iter) {
        (*iter)->undo();
    }
}
