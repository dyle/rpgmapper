/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_MARGINS_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_MARGINS_HPP


#include <QMargins>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapMargins : public AtlasCommand {

    QString mapName;
    QMargins newMargins;
    QMargins oldMargins;

public:

    SetMapMargins(AtlasPointer & atlas, QString const & mapName, QMargins newMargins);

    ~SetMapMargins() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
