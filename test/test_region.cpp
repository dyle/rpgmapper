/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/region.hpp>
#include <rpgmapper/region_name_validator.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;


TEST(RegionTest, CreateRegionIsValid) {
    
    Session::setCurrentSession(Session::init());
    auto region = Session::getCurrentSession()->createRegion("foo");

    ASSERT_TRUE(region->isValid());
}


TEST(RegionTest, DeleteRegionAndMap) {

    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    EXPECT_EQ(session->getAllRegionNames().size(), 1);
    EXPECT_EQ(session->getAllMapNames().size(), 1);

    session->createRegion("foo");
    session->createMap("bar", "foo");

    EXPECT_EQ(session->getAllRegionNames().size(), 2);
    EXPECT_EQ(session->getAllMapNames().size(), 2);
    session->deleteRegion("foo");
    EXPECT_EQ(session->getAllRegionNames().size(), 1);
    EXPECT_EQ(session->getAllMapNames().size(), 1);
}


TEST(RegionTest, RegionGetAndSetName) {
    
    Session::setCurrentSession(Session::init());
    auto region = Session::getCurrentSession()->createRegion("foo");

    EXPECT_EQ(region->getName().toStdString(), "foo");
    region->setName("bar");
    EXPECT_EQ(region->getName().toStdString(), "bar");
}


TEST(RegionTest, GetAllMapNames) {
    
    Session::setCurrentSession(Session::init());
    auto region = Session::getCurrentSession()->createRegion("foo");
    
    Session::getCurrentSession()->createMap("map 1", "foo");
    Session::getCurrentSession()->createMap("map 2", "foo");
    Session::getCurrentSession()->createMap("map 3", "foo");
    Session::getCurrentSession()->createMap("map 4", "foo");
    std::set<QString> mapNamesExpected{"map 1", "map 2", "map 3", "map 4" };

    EXPECT_TRUE(mapNamesExpected == region->getMapNames());
}


TEST(RegionTest, CreateAndRemoveMaps) {
    
    Session::setCurrentSession(Session::init());
    auto region = Session::getCurrentSession()->createRegion("foo");

    std::vector<QString> maps{"map 1", "map 2", "map 3", "map 4", "map 5"};

    int numberOfMaps = 0;
    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&](auto & name) {
                      Session::getCurrentSession()->createMap(name, "foo");
                      EXPECT_EQ(region->getMapNames().size(), ++numberOfMaps);
                  });

    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&](auto & name) {
                      region->removeMap(name);
                      EXPECT_EQ(region->getMapNames().size(), --numberOfMaps);
                  });
}


TEST(RegionTest, ValidNames) {

    EXPECT_TRUE(RegionNameValidator::isValid("Middleearth"));
    EXPECT_TRUE(RegionNameValidator::isValid("A land far far away"));
    EXPECT_TRUE(RegionNameValidator::isValid("Asgard!"));
    EXPECT_FALSE(RegionNameValidator::isValid("This is: invalid"));
    EXPECT_FALSE(RegionNameValidator::isValid("This is also \\ invalid"));
    EXPECT_FALSE(RegionNameValidator::isValid("This is invalid * as well"));
    EXPECT_FALSE(RegionNameValidator::isValid("And this ? is also invalid"));
}
