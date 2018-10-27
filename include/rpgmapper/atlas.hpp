/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_ATLAS_HPP
#define RPGMAPPER_MODEL_ATLAS_HPP

#include <memory>
#include <set>

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QSharedPointer>

#include <rpgmapper/command/processor.hpp>
#include <rpgmapper/io/content.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session_aware.hpp>


namespace rpgmapper {
namespace model {


/**
 * This is the main class.
 *
 * An atlas as a set of regions, each with a set of maps.
 */
class Atlas : public QObject, public SessionAware {

    Q_OBJECT

    class Impl;                         /**< Internal data class. */
    std::shared_ptr<Impl> impl;         /**< Pointer to implementation [PIMPL C++ Idiom] */

public:

    /**
     * Construtor
     *
     * @param   parent      parent Qt object.
     */
    explicit Atlas(QObject * parent = nullptr);

    /**
     * Destructor.
     */
    ~Atlas() override = default;

    bool applyJSON(QJsonObject json);

    void collectContent(rpgmapper::model::io::Content & content) const;

    QSharedPointer<rpgmapper::model::Region> & createRegion(QString const & name);

    QSharedPointer<rpgmapper::model::Map> & findMap(QString const & name);

    QSharedPointer<rpgmapper::model::Map> const & findMap(QString const & name) const;

    QSharedPointer<rpgmapper::model::Region> & findRegion(QString const & name);

    QSharedPointer<rpgmapper::model::Region> const & findRegion(QString const & name) const;

    std::set<QString> getAllMapNames() const;

    std::set<QString> getAllRegionNames() const;

    QSharedPointer<rpgmapper::model::command::Processor> & getCommandProzessor();

    QSharedPointer<rpgmapper::model::command::Processor> const & getCommandProzessor() const;

    QString const & getFileName() const;

    static QString getInvalidCharactersInName();

    QString const & getName() const;

    Regions const & getRegions() const;

    void init();

    bool isModified() const;

    static bool isNameValid(QString name);

    virtual bool isValid() const {
        return true;
    }

    bool moveMap(QString const & map, QString const & regionTo) {
        return moveMap(findMap(map), findRegion(regionTo));
    }

    bool moveMap(QSharedPointer<rpgmapper::model::Map> map, QSharedPointer<rpgmapper::model::Region> regionTo);

    static QSharedPointer<Atlas> const & null();

    void readIOContent(rpgmapper::model::io::Content const & content);

    void removeRegion(QString const & name);

    void resetChanged();

    void setFileName(QString const & fileName);

    void setName(QString const & name);

private:

    void connectRegionSignals(QSharedPointer<rpgmapper::model::Region> & region);

private slots:

    void changedRegionName(QString nameBefore, QString nameAfter);

signals:

    void commandExecuted();

    void mapAdded(QString regionName, QString mapName);

    void mapCreated(QString regionName, QString mapName);

    void mapNameChanged(QString regionName, QString nameBefore, QString nameAfter);

    void mapNumeralForAxisChanged(QString regionName, QString mapName);

    void mapRemoved(QString regionName, QString mapName);

    void mapResized(QString regionName, QString mapName);

    void nameChanged(QString name);

    void regionCreated(QString name);

    void regionNameChanged(QString nameBefore, QString nameAfter);

    void regionRemoved(QString name);
};


class InvalidAtlas final : public Atlas {
public:
    InvalidAtlas() : Atlas{nullptr} {}
    bool isValid() const override { return false; }
};


}
}


#endif
