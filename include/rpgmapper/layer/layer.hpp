/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_HPP


#include <memory>

#include <QJsonObject>
#include <QObject>
#include <QPainter>
#include <QSharedPointer>

#include <rpgmapper/field.hpp>
#include <rpgmapper/resource_db.hpp>
#include <rpgmapper/io/content.hpp>


namespace rpgmapper {
namespace model {


// Forward declaration of Map class.
class Map;

/**
 * A single map is built by Layer objects stacked upon each other.
 *
 * A Layer has a specific purpose: there are base (ground) layers, wall layers, etc.
 * Layers are stacked in a Z-order. The lowest layer will be rendered first.
 */
class Layer : public QObject {

    Q_OBJECT

    class Impl;                                 /**< Implmentation class. */
    std::shared_ptr<Impl> impl;                 /**< Pimpl idiom. */

public:

    using Attributes = std::map<QString, QString>;

    explicit Layer(rpgmapper::model::Map * map, QObject * parent = nullptr);

    ~Layer() override = default;

    virtual bool applyJsonObject(QJsonObject const & json);

    virtual void draw(QPainter & painter, int tileSize) const = 0;

    Attributes & getAttributes();

    Attributes const & getAttributes() const;

    virtual QJsonObject getJsonObject(rpgmapper::model::io::Content & content) const;

    ResourceDBPointer & getResourceDB();

    ResourceDBPointer const & getResourceDB() const;

    void hide();

    virtual bool isValid() const {
        return true;
    }

    bool isVisible() const;

    void show();

protected:

    Map * getMap();

    Map const * getMap() const;

signals:

    void visibilityChanged();
};


class InvalidLayer final : public Layer {

public:

    InvalidLayer()
        : Layer{nullptr, nullptr} {
    }

    bool isValid() const override {
        return false;
    }
};


}
}

#endif
