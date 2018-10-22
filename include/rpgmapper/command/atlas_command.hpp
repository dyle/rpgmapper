/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_ATLAS_COMMAND_HPP
#define RPGMAPPER_MODEL_COMMAND_ATLAS_COMMAND_HPP


#include <rpgmapper/atlas.hpp>
#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * The AtlasCommand class is the base class of all commands dealing the an atlas.
 */
class AtlasCommand : public Command {

    /**
     * Pointer to the atlas managed.
     */
    QWeakPointer<rpgmapper::model::Atlas> atlas;

public:

    /**
     * Constructor.
     *
     * @param   atlas       the atlas managed.
     */
    explicit AtlasCommand(rpgmapper::model::AtlasPointer & atlas)
        : atlas{atlas} {
    }

    /**
     * Returns the Atlas we are working on.
     *
     * @return  the current atlas instance.
     */
    rpgmapper::model::AtlasPointer getAtlas();

    /**
     * Returns the const Atals we are working on.
     *
     * @return  the current atlas instance (const version).
     */
    rpgmapper::model::AtlasPointer const getAtlas() const;
};


}
}
}


#endif
