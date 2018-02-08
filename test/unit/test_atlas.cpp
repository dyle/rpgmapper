/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <tuple>

#include <gtest/gtest.h>

#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;


TEST(AtlasTest, CreateAtlasIsValid) {

    Atlas atlas;

    ASSERT_TRUE(atlas.isValid());
}


TEST(AtlasTest, CreateAtlasPointerIsValid) {

    AtlasPointer atlas{new Atlas{}};

    EXPECT_NE(atlas.data(), nullptr);
    EXPECT_TRUE(atlas->isValid());
}


TEST(AtlasTest, CreateInvalidAtlasIsNotValid) {
    EXPECT_FALSE(InvalidAtlas{}.isValid());
}


TEST(AtlasTest, CreateInvalidAtlasPointerIsNotValid) {

    AtlasPointer atlas{new InvalidAtlas{}};

    EXPECT_NE(atlas.data(), nullptr);
    EXPECT_FALSE(atlas->isValid());
}


TEST(AtlasTest, InitialAtlasNameIsNewAtlas) {

    Atlas atlas;

    EXPECT_EQ(atlas.getName().toStdString(), "New Atlas");
}


TEST(AtlasTest, InitialAtlasRegionAndMap) {

    Atlas atlas;

    ASSERT_EQ(atlas.getRegions().size(), 1);
    auto region = (*std::begin(atlas.getRegions())).second;
    ASSERT_NE(region.data(), nullptr);
    EXPECT_EQ(region->getName().toStdString(), "New Region 1");

    ASSERT_EQ(region->getMaps().size(), 1);
    auto map = (*std::begin(region->getMaps())).second;
    ASSERT_NE(map.data(), nullptr);
    EXPECT_EQ(map->getName().toStdString(), "New Map 1");
}


TEST(AtlasTest, AtlasNameSet) {

    Atlas atlas;
    atlas.setName("foo");

    EXPECT_EQ(atlas.getName().toStdString(), "foo");
    EXPECT_TRUE(atlas.hasChanged());
}


TEST(AtlasTest, InitialAtlasIsNotModified) {

    Atlas atlas;

    EXPECT_FALSE(atlas.hasChanged());
}


TEST(AtlasTest, InitialAtlasRemoveRegionResultsInEmptyRegions) {

    Atlas atlas;
    auto regionName = atlas.getRegions().begin()->second->getName();
    atlas.removeRegion(regionName);

    EXPECT_TRUE(atlas.getRegions().empty());
    EXPECT_TRUE(atlas.hasChanged());
}


TEST(AtlasTest, CreateRegion) {

    Atlas atlas;
    auto region = atlas.createRegion("foo");

    EXPECT_TRUE(region->isValid());
    EXPECT_EQ(region->getAtlas(), &atlas);
    EXPECT_EQ(region->getName(), "foo");
    EXPECT_TRUE(atlas.hasChanged());
}


TEST(AtlasTest, AllRegionNames) {

    Atlas atlas;
    atlas.removeRegion("New Region 1");
    atlas.createRegion("foo");
    atlas.createRegion("bar");
    atlas.createRegion("baz");
    std::set<QString> allRegionNamesExpected{"foo", "bar", "baz"};

    EXPECT_TRUE(allRegionNamesExpected == atlas.getAllRegionNames());
}


TEST(AtlasTest, AllMapNamesOfAllRegions) {

    Atlas atlas;
    atlas.removeRegion("New Region 1");
    auto regionFoo = atlas.createRegion("foo");
    auto regionBar = atlas.createRegion("bar");

    MapPointer map;
    map = regionFoo->createMap("map 1");
    EXPECT_TRUE(map->isValid());
    map = regionFoo->createMap("map 2");
    EXPECT_TRUE(map->isValid());
    map = regionFoo->createMap("map 3");
    EXPECT_TRUE(map->isValid());
    map = regionFoo->createMap("map 3");
    EXPECT_FALSE(map->isValid());
    map = regionBar->createMap("map 3");
    EXPECT_FALSE(map->isValid());
    map = regionBar->createMap("map 4");
    EXPECT_TRUE(map->isValid());
    map = regionBar->createMap("map 5");
    EXPECT_TRUE(map->isValid());
    map = regionBar->createMap("map 5");
    EXPECT_FALSE(map->isValid());
    map = regionBar->createMap("map 1");
    EXPECT_FALSE(map->isValid());
    map = regionFoo->createMap("map 3");
    EXPECT_FALSE(map->isValid());

    std::set<QString> mapNamesExpected{"map 1", "map 2", "map 3", "map 4", "map 5"};
    std::set<QString> mapNamesExpectedForRegionFoo{"map 1", "map 2", "map 3"};
    std::set<QString> mapNamesExpectedForRegionBar{"map 4", "map 5"};

    EXPECT_TRUE(atlas.getRegion("foo")->getMapNames() == mapNamesExpectedForRegionFoo);
    EXPECT_TRUE(atlas.getRegion("bar")->getMapNames() == mapNamesExpectedForRegionBar);
    EXPECT_TRUE(atlas.getAllMapNames() == mapNamesExpected);
}


TEST(AtlasTest, CreateAndRemoveRegions) {

    std::vector<QString> regions{"Region 1",
                                 "Region 2",
                                 "Region 3",
                                 "Region 4",
                                 "Region 5"};

    Atlas atlas;
    auto regionName = atlas.getRegions().begin()->second->getName();
    atlas.removeRegion(regionName);

    int numberOfRegiopns = 0;
    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&](auto & name) {
                      atlas.createRegion(name);
                      EXPECT_EQ(atlas.getRegions().size(), ++numberOfRegiopns);
                      EXPECT_TRUE(atlas.hasChanged());
                  });

    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&](auto & name) {
                      atlas.removeRegion(name);
                      EXPECT_EQ(atlas.getRegions().size(), --numberOfRegiopns);
                      EXPECT_TRUE(atlas.hasChanged());
                  });
}


TEST(AtlasTest, CreateAndRemoveIdenticalRegions) {

    std::vector<QString> regions{"Region 1",
                                 "Region 1",
                                 "Region 1",
                                 "Region 1",
                                 "Region 1"};

    Atlas atlas;
    auto regionName = atlas.getRegions().begin()->second->getName();
    atlas.removeRegion(regionName);

    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&](auto & name) {
                      atlas.createRegion(name);
                      EXPECT_EQ(atlas.getRegions().size(), 1);
                      EXPECT_TRUE(atlas.hasChanged());
                  });

    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&](auto & name) {
                      atlas.removeRegion(name);
                      EXPECT_TRUE(atlas.getRegions().empty());
                      EXPECT_TRUE(atlas.hasChanged());
                  });
}


