/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
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
    for (auto const & command : commands) {
        commandDescriptions << command->getDescription();
    }

    return QString{"Composite command of [%1]."}.arg(commandDescriptions.join(", "));
}


void CompositeCommand::execute() {
    for (auto & command : commands) {
        command->execute();
    }
}


void CompositeCommand::undo() {
    for (auto iter = std::rbegin(commands); iter != std::rend(commands); ++iter) {
        (*iter)->undo();
    }
}
