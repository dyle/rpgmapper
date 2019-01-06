/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_SET_ATLAS_NAME_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_ATLAS_NAME_HPP

#include <QString>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper::model::command {


/**
 * This command gives the atlas a new name.
 */
class SetAtlasName : public Command {

    QString newName;            /**< The new name of the atlas. */
    QString oldName;            /**< The old name of the atlas. */

public:
    
    /**
     * Constructor.
     *
     * @param   name            the new name of the atlas.
     */
    SetAtlasName(QString name);
    
    /**
     * Destructor.
     */
    ~SetAtlasName() override = default;
    
    /**
     * Executes this command.
     */
    void execute() override;
    
    /**
     * Returns a human readable string for this command.
     *
     * @return  a string describing this command.
     */
    QString getDescription() const override;
    
    /**
     * Undoes the command.
     */
    void undo() override;
};


}


#endif
