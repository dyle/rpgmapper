/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_OFFSET_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_OFFSET_HPP


#include <QPointF>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapNumeralOffset : public AtlasCommand {

    QString mapName;
    QPointF newOffset;
    QPointF oldOffset;

public:

    SetMapNumeralOffset(AtlasPointer & atlas, QString const & mapName, QPointF newOffset);

    ~SetMapNumeralOffset() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
