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


TEST(MapTest, MapDefaultSize) {

    Map map{"foo"};
    auto size = map.getSize();

    EXPECT_EQ(size.width(), 10);
    EXPECT_EQ(size.height(), 10);
}


TEST(MapTest, MapSizeToMinium) {

    Map map{"foo"};
    map.resize(Map::getSizeMinimum());
    auto size = map.getSize();

    EXPECT_EQ(size.width(), Map::getSizeMinimum().width());
    EXPECT_EQ(size.height(), Map::getSizeMinimum().height());
}


TEST(MapTest, MapSizeToMaximum) {

    Map map{"foo"};
    map.resize(Map::getSizeMaximum());
    auto size = map.getSize();

    EXPECT_EQ(size.width(), Map::getSizeMaximum().width());
    EXPECT_EQ(size.height(), Map::getSizeMaximum().height());
}


TEST(MapTest, MapSizeBelowMinium) {

    Map map{"foo"};
    auto oldSize = map.getSize();
    map.resize(QSize{0, 0});
    auto size = map.getSize();

    EXPECT_GE(size.width(), Map::getSizeMinimum().width());
    EXPECT_GE(size.height(), Map::getSizeMinimum().height());
    EXPECT_EQ(size.width(), oldSize.width());
    EXPECT_EQ(size.height(), oldSize.height());
}


TEST(MapTest, MapSizeAboveMaximum) {

    Map map{"foo"};
    auto oldSize = map.getSize();
    map.resize(QSize{1000000, 1000000});
    auto size = map.getSize();

    EXPECT_LE(size.width(), Map::getSizeMaximum().width());
    EXPECT_LE(size.height(), Map::getSizeMaximum().height());
    EXPECT_EQ(size.width(), oldSize.width());
    EXPECT_EQ(size.height(), oldSize.height());
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
