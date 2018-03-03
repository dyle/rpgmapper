/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_ORIGINHPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_ORIGINHPP

#include <QString>

#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapOrigin : public AtlasCommand {

    QString mapName;
    CoordinatesOrigin newOrigin;
    CoordinatesOrigin oldOrigin;

public:

    SetMapOrigin(AtlasPointer & atlas, QString const & mapName, rpgmapper::model::CoordinatesOrigin origin);

    ~SetMapOrigin() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
