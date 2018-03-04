/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_AXIS_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_NUMERAL_AXIS_HPP


#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapNumeralAxis : public AtlasCommand {

    QString mapName;
    bool xAxis;
    QString newNumeral;
    QString oldNumeral;

public:

    SetMapNumeralAxis(AtlasPointer & atlas, QString const & mapName, bool xAxis, QString newNumeral);

    ~SetMapNumeralAxis() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
