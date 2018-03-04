/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_FONT_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_AXIS_FONT_HPP


#include <QFont>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapAxisFont : public AtlasCommand {

    QString mapName;
    QFont newFont;
    QFont oldFont;

public:

    SetMapAxisFont(AtlasPointer & atlas, QString const & mapName, QFont newFont);

    ~SetMapAxisFont() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
