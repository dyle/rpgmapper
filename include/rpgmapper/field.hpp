/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_FIELD_HPP
#define RPGMAPPER_MODEL_FIELD_HPP


#include <map>
#include <vector>

#include <QPoint>
#include <QSharedPointer>
#include <QString>


namespace rpgmapper {
namespace model {

class Field;

using FieldPointer = QSharedPointer<Field>;

using Tile = std::map<QString, QString>;

using Tiles = std::vector<Tile>;

class Field {

    QPoint position;
    Tiles tiles;

public:

    explicit Field(int x = 0, int y = 0);

    explicit Field(QPoint const & position);

    int getIndex() const { return getIndex(position); }

    static int getIndex(int x, int y);

    static int getIndex(QPoint const & point) { return getIndex(point.x(), point.y()); }

    virtual bool isValid() const { return true; }

    static Field const & nullField();
};

class InvalidField final : public Field {

public:

    InvalidField() : Field(0, 0) {}

    bool isValid() const override { return false; }
};


}
}


#endif
