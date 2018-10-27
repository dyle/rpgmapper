/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/processor.hpp>
#include "processor_impl.hpp"

using namespace rpgmapper::model::command;


Processor::Processor(QObject * parent) : QObject(parent) {
    impl = std::make_shared<Processor::Impl>();
}


void Processor::execute(QSharedPointer<rpgmapper::model::command::Command> & command) {
    impl->execute(command);
    emit commandExecuted();
}


Commands const & Processor::getHistory() const {
    return impl->getHistory();
}


Commands const & Processor::getUndone() const {
    return impl->getUndone();
}


int Processor::modifications() const {
    return impl->modifications();
}


void Processor::redo() {
    impl->redo();
}


void Processor::resetModifications() {
    impl->resetModifications();
}


void Processor::undo() {
    impl->undo();
}
