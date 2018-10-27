/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_ATLAS_COMMAND_HPP
#define RPGMAPPER_MODEL_COMMAND_ATLAS_COMMAND_HPP


#include <rpgmapper/command/command.hpp>
#include <rpgmapper/atlas.hpp>


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
    explicit AtlasCommand(QSharedPointer<rpgmapper::model::Atlas> & atlas)
        : atlas{atlas} {
    }

    /**
     * Returns the Atlas we are working on.
     *
     * @return  the current atlas instance.
     */
    QSharedPointer<rpgmapper::model::Atlas> getAtlas();

    /**
     * Returns the const Atals we are working on.
     *
     * @return  the current atlas instance (const version).
     */
    QSharedPointer<rpgmapper::model::Atlas> const getAtlas() const;
};


}
}
}


#endif
