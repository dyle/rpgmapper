/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_ATLAS_COMMAND_HPP
#define RPGMAPPER_MODEL_COMMAND_ATLAS_COMMAND_HPP

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/command/command.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


namespace rpgmapper {
namespace model {
namespace command {


class AtlasCommand : public Command {

    QWeakPointer<Atlas> atlas;

public:

    explicit AtlasCommand(AtlasPointer & atlas) : atlas{atlas} {}

    AtlasPointer getAtlas();

    AtlasPointer const getAtlas() const;
};


}
}
}


#endif
