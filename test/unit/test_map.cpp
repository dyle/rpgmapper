/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>

using namespace rpgmapper::model;


TEST(MapTest, CreateMapIsValid) {

    Map map{"foo"};

    ASSERT_TRUE(map.isValid());
}


TEST(MapTest, CreateMapPointerIsValid) {

    MapPointer map{new Map{"foo"}};

    EXPECT_NE(map.data(), nullptr);
    EXPECT_TRUE(map->isValid());
}


TEST(MapTest, CreateInvalidMapIsNotValid) {
    EXPECT_FALSE(InvalidMap{}.isValid());
}


TEST(MapTest, CreateInvalidMapPointerIsNotValid) {

    MapPointer map{new InvalidMap{}};

    EXPECT_NE(map.data(), nullptr);
    EXPECT_FALSE(map->isValid());
}


TEST(MapTest, MapGetAndSetName) {

    Map map{"foo"};
    EXPECT_EQ(map.getName().toStdString(), "foo");

    map.setName("bar");
    EXPECT_EQ(map.getName().toStdString(), "bar");
}


TEST(MapTest, GetRegionNameOfMap) {

    Region region{"foo"};
    region.createMap("bar");
    auto map = region.findMap("bar");

    ASSERT_TRUE(map->isValid());

    auto regionName = map->getRegionName();
    EXPECT_EQ(regionName.toStdString(), "foo");
}


TEST(MapTest, GetNameOfMapWithInavlidRegion) {

    Map map{"foo"};
    auto regionName = map.getRegionName();

    EXPECT_EQ(regionName, QString::null);
}


TEST(MapTest, GetBackgroundLayer) {

    Map map{"foo"};
    auto layer = map.getBackgroundLayer();

    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, GetBaseLayers) {

    Map map{"foo"};
    auto layers = map.getBaseLayers();

    EXPECT_GT(layers.size(), 0);
    for (auto const & layer : layers) {
        EXPECT_TRUE(layer->isValid());
    }
}


TEST(MapTest, GetGridLayer) {

    Map map{"foo"};
    auto layer = map.getGridLayer();

    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, GetTileLayers) {

    Map map{"foo"};
    auto layers = map.getTileLayers();

    EXPECT_GT(layers.size(), 0);
    for (auto const & layer : layers) {
        EXPECT_TRUE(layer->isValid());
    }
}


TEST(MapTest, GetTextLayer) {

    Map map{"foo"};
    auto layer = map.getTextLayer();

    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, ValidNames) {

    EXPECT_TRUE(Map::isNameValid("Middleearth"));
    EXPECT_TRUE(Map::isNameValid("A land far far away"));
    EXPECT_TRUE(Map::isNameValid("Asgard!"));
    EXPECT_FALSE(Map::isNameValid("This is: invalid"));
    EXPECT_FALSE(Map::isNameValid("This is also \\ invalid"));
    EXPECT_FALSE(Map::isNameValid("This is invalid * as well"));
    EXPECT_FALSE(Map::isNameValid("And this ? is also invalid"));
}
