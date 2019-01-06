/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_PROCESSOR_POINTER_HPP
#define RPGMAPPER_MODEL_COMMAND_PROCESSOR_POINTER_HPP

#include <QSharedPointer>


namespace rpgmapper::model::command {


// fwd
class Processor;


/**
 * A smart pointer to a command processor.
 */
using ProcessorPointer = QSharedPointer<Processor>;


}


#endif
