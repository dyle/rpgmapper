/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <QSharedPointer>

#include <rpgmapper/tile/tile.hpp>
#include <rpgmapper/tile/tile_factory.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::tile;


TEST(TileTest, CreateColorTile) {

    auto tile = TileFactory::create(TileType::color, {{"color", "foo"}});
    
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
            R"({"attributes": {"color": "foo", "type": "color"}, "map": null, "position": {"x": 0, "y": 0}})");

    EXPECT_EQ(tile->getType().toStdString(), "color");
}


TEST(TileTest, CreateShapeTile) {
    
    auto tile = TileFactory::create(TileType::shape, {{"path", "foo"}});
    
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "type": "shape"}, "map": null, "position": {"x": 0, "y": 0}})");
    
    EXPECT_EQ(tile->getType().toStdString(), "shape");
}


TEST(TileTest, RotateTileRight) {
    
    auto tile = TileFactory::create(TileType::shape, {{"path", "foo"}});
    
    tile->rotateRight();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "90", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateRight();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "180", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateRight();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "270", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateRight();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "0", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    tile->rotateRight();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "90", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateRight();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "180", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateRight();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "270", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateRight();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "0", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
}


TEST(TileTest, RotateTileLeft) {
    
    auto tile = TileFactory::create(TileType::shape, {{"path", "foo"}});
    
    tile->rotateLeft();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "270", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateLeft();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "180", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateLeft();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "90", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateLeft();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "0", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    tile->rotateLeft();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "270", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateLeft();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "180", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateLeft();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "90", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateLeft();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "0", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
}


TEST(TileTest, RotateTileLeftRight) {
    
    auto tile = TileFactory::create(TileType::shape, {{"path", "foo"}});
    
    tile->rotateLeft();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "270", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
    
    tile->rotateRight();
    EXPECT_EQ(static_cast<std::string>(*tile.data()),
              R"({"attributes": {"path": "foo", "rotation": "0", "type": "shape"}, )"\
              R"("map": null, "position": {"x": 0, "y": 0}})");
}
