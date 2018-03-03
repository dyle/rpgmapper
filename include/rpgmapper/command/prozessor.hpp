/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_PROZESSOR_HPP
#define RPGMAPPER_MODEL_COMMAND_PROZESSOR_HPP


#include <memory>

#include <QObject>
#include <QString>
#include <QSharedPointer>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class Prozessor : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    Prozessor(QObject * parent = nullptr);

    ~Prozessor() = default;

    void execute(CommandPointer command);

    Commands const & getHistory() const;

    Commands const & getUndone() const;

    int modifications() const;

    void redo();

    void undo();

signals:

    void commandExecuted();

};

using ProzessorPointer = QSharedPointer<Prozessor>;


}
}
}


#endif
