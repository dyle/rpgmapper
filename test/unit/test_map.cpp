/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

#include <rpgmapper/map.hpp>

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


TEST(MapTest, GetBackgroundLayer) {

    Map map{"foo"};
    LayerPointer layer = map.getBackgroundLayer();

    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, GetGridLayer) {

    Map map{"foo"};
    LayerPointer layer = map.getGridLayer();

    EXPECT_TRUE(layer->isValid());
}

