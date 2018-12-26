/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/resource/shape.hpp>
#include <rpgmapper/resource/shape_catalog.hpp>
#include <rpgmapper/tile/tile_insert_modes.hpp>

using namespace rpgmapper::model::resource;
using namespace rpgmapper::model::tile;


ShapeCatalog::ShapeCatalog(QString name, QByteArray const & data) : Resource{std::move(name), data} {
    fromJSON();
}


void ShapeCatalog::addShape(QJsonObject const & json) {
    
    QString shapeName;
    if (json.contains("name") && json["name"].isString()) {
        shapeName = json["name"].toString();
    }
    
    QString shapePath;
    if (json.contains("file") && json["file"].isString()) {
        shapePath = getCatalogBase() + "/" + json["file"].toString();
    }
    
    if (!shapeName.isEmpty() && !shapePath.isEmpty()) {
        shapes.emplace(shapeName, shapePath);
    }
    
    auto resource = ResourceDB::getResource(shapePath);
    auto shape = dynamic_cast<rpgmapper::model::resource::Shape *>(resource.data());
    if (shape) {
    
        shape->setName(shapeName);
        
        if (json.contains("layer") && json["layer"].isString()) {
            shape->setTargetLayer(Shape::targetLayerFromString(json["layer"].toString()));
        }
    
        if (json.contains("z") && json["z"].isDouble()) {
            auto z = static_cast<unsigned int>(json["z"].toDouble(0.0));
            shape->setZOrdering(z);
        }
        
        if (json.contains("mode") && json["mode"].isString()) {
            auto mode = getInsertModeFromString(json["mode"].toString());
            shape->setInsertMode(mode);
        }
    }
}


void ShapeCatalog::fromJSON() {
    
    valid = false;
    
    auto jsonDocument = QJsonDocument::fromJson(getData());
    if (!jsonDocument.isObject()) {
        return;
    }
    
    auto json = jsonDocument.object();
    if (json.contains("name") && json["name"].isString()) {
        setName(json["name"].toString());
    }
    
    if (json.contains("shapes") && json["shapes"].isArray()) {
        
        auto jsonArray = json["shapes"].toArray();
        for (auto && element : jsonArray) {
            if (element.isObject()) {
                auto jsonShape = element.toObject();
                addShape(jsonShape);
            }
        }
        
        valid = true;
    }
}


QString ShapeCatalog::getCatalogBase() const {
    QFileInfo fileInfo{getPath()};
    return fileInfo.dir().path();
}


bool ShapeCatalog::isShapeCatalog(QByteArray const & data) {
    
    auto jsonDocument = QJsonDocument::fromJson(data);
    if (!jsonDocument.isObject()) {
        return false;
    }
    
    auto json = jsonDocument.object();
    bool namePresent = json.contains("name") && json["name"].isString();
    bool shapesPresent = json.contains("shapes") && json["shapes"].isArray();
    
    return namePresent && shapesPresent;
}


void ShapeCatalog::setData(QByteArray const & data) {
    Resource::setData(data);
    fromJSON();
}
