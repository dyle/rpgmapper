/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/map.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;


TEST(MapTest, CreateMapIsValid) {
    
    Session::setCurrentSession(Session::init());
    Session::getCurrentSession()->createRegion("region-1");
    auto map = Session::getCurrentSession()->createMap("foo", "region-1");

    ASSERT_TRUE(map->isValid());
}


TEST(MapTest, CreateInvalidMapIsNotValid) {
    EXPECT_FALSE(InvalidMap{}.isValid());
}



TEST(MapTest, MapGetAndSetName) {
    
    Session::setCurrentSession(Session::init());
    Session::getCurrentSession()->createRegion("region-1");
    
    auto map = Session::getCurrentSession()->createMap("foo", "region-1");

    EXPECT_EQ(map->getName().toStdString(), "foo");
    map->setName("bar");
    EXPECT_EQ(map->getName().toStdString(), "bar");
}


TEST(MapTest, GetRegionNameOfMap) {
    
    Session::setCurrentSession(Session::init());
    Session::getCurrentSession()->createRegion("region-1");
    Session::getCurrentSession()->createMap("foo", "region-1");
    
    auto map = Session::getCurrentSession()->findMap("foo");

    ASSERT_TRUE(map->isValid());
    auto regionName = map->getRegionName();
    EXPECT_EQ(regionName.toStdString(), "region-1");
}


TEST(MapTest, GetAxisLayer) {

    Session::setCurrentSession(Session::init());
    Session::getCurrentSession()->createRegion("region-1");
    auto map = Session::getCurrentSession()->createMap("foo", "region-1");

    auto layer = map->getLayers().getAxisLayer();
    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, GetBackgroundLayer) {
    
    Session::setCurrentSession(Session::init());
    Session::getCurrentSession()->createRegion("region-1");
    auto map = Session::getCurrentSession()->createMap("foo", "region-1");

    auto layer = map->getLayers().getBackgroundLayer();
    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, GetBaseLayers) {
    
    Session::setCurrentSession(Session::init());
    Session::getCurrentSession()->createRegion("region-1");
    auto map = Session::getCurrentSession()->createMap("foo", "region-1");

    auto layers = map->getLayers().getBaseLayers();
    EXPECT_GT(layers.size(), 0);
    for (auto const & layer : layers) {
        EXPECT_TRUE(layer->isValid());
    }
}


TEST(MapTest, GetGridLayer) {
    
    Session::setCurrentSession(Session::init());
    Session::getCurrentSession()->createRegion("region-1");
    auto map = Session::getCurrentSession()->createMap("foo", "region-1");

    auto layer = map->getLayers().getGridLayer();
    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, GetTileLayers) {
    
    Session::setCurrentSession(Session::init());
    Session::getCurrentSession()->createRegion("region-1");
    auto map = Session::getCurrentSession()->createMap("foo", "region-1");

    auto layers = map->getLayers().getTileLayers();
    EXPECT_GT(layers.size(), 0);
    for (auto const & layer : layers) {
        EXPECT_TRUE(layer->isValid());
    }
}


TEST(MapTest, GetTextLayer) {
    
    Session::setCurrentSession(Session::init());
    Session::getCurrentSession()->createRegion("region-1");
    auto map = Session::getCurrentSession()->createMap("foo", "region-1");

    auto layer = map->getLayers().getTextLayer();
    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, ValidNames) {

    EXPECT_TRUE(MapNameValidator::isValid("Middleearth"));
    EXPECT_TRUE(MapNameValidator::isValid("A land far far away"));
    EXPECT_TRUE(MapNameValidator::isValid("Asgard!"));
    EXPECT_FALSE(MapNameValidator::isValid("This is: invalid"));
    EXPECT_FALSE(MapNameValidator::isValid("This is also \\ invalid"));
    EXPECT_FALSE(MapNameValidator::isValid("This is invalid * as well"));
    EXPECT_FALSE(MapNameValidator::isValid("And this ? is also invalid"));
}


TEST(MapTest, DeleteMap) {

    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto region1 = session->createRegion("region-1");
    auto map = session->createMap("foo", "region-1");

    EXPECT_EQ(session->getAllRegionNames().size(), 2);
    EXPECT_EQ(region1->getMapNames().size(), 1);
    ASSERT_EQ(session->getAllMapNames().size(), 2);
    EXPECT_EQ(*(session->getAllMapNames().begin()), "foo");

    session->deleteMap("foo");

    EXPECT_EQ(session->getAllRegionNames().size(), 2);
    EXPECT_EQ(region1->getMapNames().size(), 0);
    ASSERT_EQ(session->getAllMapNames().size(), 1);
}


TEST(MapTest, MoveMapToOtherRegion) {

    Session::setCurrentSession(Session::init());
    auto region1 = Session::getCurrentSession()->createRegion("region-1");
    auto region2 = Session::getCurrentSession()->createRegion("region-2");
    auto map = Session::getCurrentSession()->createMap("foo", "region-1");

    ASSERT_EQ(region1->getMapNames().size(), 1);
    EXPECT_EQ(*(region1->getMapNames().begin()), "foo");
    ASSERT_EQ(region2->getMapNames().size(), 0);
    EXPECT_EQ(map->getRegionName(), "region-1");

    map->setRegionName("region-2");

    ASSERT_EQ(region1->getMapNames().size(), 0);
    ASSERT_EQ(region2->getMapNames().size(), 1);
    EXPECT_EQ(*(region2->getMapNames().begin()), "foo");
    EXPECT_EQ(map->getRegionName(), "region-2");
}
