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


namespace rpgmapper {
namespace model {

class Map;

class Layer : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    using Attributes = std::map<QString, QString>;

    explicit Layer(rpgmapper::model::Map * map, QObject * parent = nullptr);

    ~Layer() override = default;

    virtual void draw(QPainter & painter, int tileSize) const = 0;

    Attributes & getAttributes();

    Attributes const & getAttributes() const;

    virtual QJsonObject getJsonObject() const;

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
