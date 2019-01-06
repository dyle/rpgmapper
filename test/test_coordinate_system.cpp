/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/coordinate_system.hpp>

using namespace rpgmapper::model;


TEST(CoordinateSystemTest, DefaultSize) {

    CoordinateSystem coordinateSystem;
    auto size = coordinateSystem.getSize();

    EXPECT_EQ(size.width(), 10);
    EXPECT_EQ(size.height(), 10);
}


TEST(CoordinateSystemTest, SizeToMinium) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.resize(CoordinateSystem::getMinimumSize());
    auto size = coordinateSystem.getSize();

    EXPECT_EQ(size.width(), CoordinateSystem::getMinimumSize().width());
    EXPECT_EQ(size.height(), CoordinateSystem::getMinimumSize().height());
}


TEST(CoordinateSystemTest, SizeToMaximum) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.resize(CoordinateSystem::getMaximumSize());
    auto size = coordinateSystem.getSize();

    EXPECT_EQ(size.width(), CoordinateSystem::getMaximumSize().width());
    EXPECT_EQ(size.height(), CoordinateSystem::getMaximumSize().height());
}


TEST(CoordinateSystemTest, SizeBelowMinium) {

    CoordinateSystem coordinateSystem;
    auto oldSize = coordinateSystem.getSize();
    coordinateSystem.resize(QSize{0, 0});
    auto size = coordinateSystem.getSize();

    EXPECT_GE(size.width(), CoordinateSystem::getMinimumSize().width());
    EXPECT_GE(size.height(), CoordinateSystem::getMinimumSize().height());
    EXPECT_EQ(size.width(), oldSize.width());
    EXPECT_EQ(size.height(), oldSize.height());
}


TEST(CoordinateSystemTest, SizeAboveMaximum) {

    CoordinateSystem coordinateSystem;
    auto oldSize = coordinateSystem.getSize();
    coordinateSystem.resize(QSize{1000000, 1000000});
    auto size = coordinateSystem.getSize();

    EXPECT_LE(size.width(), CoordinateSystem::getMaximumSize().width());
    EXPECT_LE(size.height(), CoordinateSystem::getMaximumSize().height());
    EXPECT_EQ(size.width(), oldSize.width());
    EXPECT_EQ(size.height(), oldSize.height());
}


TEST(CoordinateSystemTest, NumeralsNumeric) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.setNumeralXAxis("numeric");
    coordinateSystem.setNumeralYAxis("numeric");
    EXPECT_TRUE(coordinateSystem.getNumeralXAxis()->isValid());
    EXPECT_TRUE(coordinateSystem.getNumeralYAxis()->isValid());
    EXPECT_EQ(coordinateSystem.getNumeralXAxis()->getName().toStdString(), "numeric");
    EXPECT_EQ(coordinateSystem.getNumeralYAxis()->getName().toStdString(), "numeric");

    auto coordinates = coordinateSystem.getNumeralCoordinates(QPoint{0, 0});
    EXPECT_EQ(coordinates.x.toStdString(), "0");
    EXPECT_EQ(coordinates.y.toStdString(), "0");

    coordinates = coordinateSystem.getNumeralCoordinates(QPoint{7, 5});
    EXPECT_EQ(coordinates.x.toStdString(), "7");
    EXPECT_EQ(coordinates.y.toStdString(), "5");
}


TEST(CoordinateSystemTest, NumeralsAlphaSmall) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.setNumeralXAxis("alphaSmall");
    coordinateSystem.setNumeralYAxis("alphaSmall");
    EXPECT_TRUE(coordinateSystem.getNumeralXAxis()->isValid());
    EXPECT_TRUE(coordinateSystem.getNumeralYAxis()->isValid());
    EXPECT_EQ(coordinateSystem.getNumeralXAxis()->getName().toStdString(), "alphaSmall");
    EXPECT_EQ(coordinateSystem.getNumeralYAxis()->getName().toStdString(), "alphaSmall");

    auto coordinates = coordinateSystem.getNumeralCoordinates(QPoint{0, 0});
    EXPECT_EQ(coordinates.x.toStdString(), "a");
    EXPECT_EQ(coordinates.y.toStdString(), "a");

    coordinates = coordinateSystem.getNumeralCoordinates(QPoint{7, 5});
    EXPECT_EQ(coordinates.x.toStdString(), "h");
    EXPECT_EQ(coordinates.y.toStdString(), "f");
}


TEST(CoordinateSystemTest, NumeralsAlphaBig) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.setNumeralXAxis("alphaBig");
    coordinateSystem.setNumeralYAxis("alphaBig");
    EXPECT_TRUE(coordinateSystem.getNumeralXAxis()->isValid());
    EXPECT_TRUE(coordinateSystem.getNumeralYAxis()->isValid());
    EXPECT_EQ(coordinateSystem.getNumeralXAxis()->getName().toStdString(), "alphaBig");
    EXPECT_EQ(coordinateSystem.getNumeralYAxis()->getName().toStdString(), "alphaBig");

    auto coordinates = coordinateSystem.getNumeralCoordinates(QPoint{0, 0});
    EXPECT_EQ(coordinates.x.toStdString(), "A");
    EXPECT_EQ(coordinates.y.toStdString(), "A");

    coordinates = coordinateSystem.getNumeralCoordinates(QPoint{7, 5});
    EXPECT_EQ(coordinates.x.toStdString(), "H");
    EXPECT_EQ(coordinates.y.toStdString(), "F");
}


TEST(CoordinateSystemTest, NumeralsRoman) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.setNumeralXAxis("roman");
    coordinateSystem.setNumeralYAxis("roman");
    EXPECT_TRUE(coordinateSystem.getNumeralXAxis()->isValid());
    EXPECT_TRUE(coordinateSystem.getNumeralYAxis()->isValid());
    EXPECT_EQ(coordinateSystem.getNumeralXAxis()->getName().toStdString(), "roman");
    EXPECT_EQ(coordinateSystem.getNumeralYAxis()->getName().toStdString(), "roman");

    auto coordinates = coordinateSystem.getNumeralCoordinates(QPoint{0, 0});
    EXPECT_EQ(coordinates.x.toStdString(), "O");
    EXPECT_EQ(coordinates.y.toStdString(), "O");

    coordinates = coordinateSystem.getNumeralCoordinates(QPoint{7, 5});
    EXPECT_EQ(coordinates.x.toStdString(), "VII");
    EXPECT_EQ(coordinates.y.toStdString(), "V");
}


TEST(CoordinateSystemTest, OuterRect) {
    
    CoordinateSystem coordinateSystem;
    coordinateSystem.resize(QSize{10, 10});
    
    coordinateSystem.setMargin(0.0);
    EXPECT_EQ(coordinateSystem.getMargin(), 0.0);
    
    auto outerRect = coordinateSystem.getOuterRect(48);
    EXPECT_EQ(outerRect.x(), 0);
    EXPECT_EQ(outerRect.y(), 0);
    EXPECT_EQ(outerRect.width(), 48 * 12 + 48 * 0.0 * 2);
    EXPECT_EQ(outerRect.width(), 48 * 12 + 48 * 0.0 * 2);
    
    outerRect = coordinateSystem.getOuterRect(32);
    EXPECT_EQ(outerRect.x(), 0);
    EXPECT_EQ(outerRect.y(), 0);
    EXPECT_EQ(outerRect.width(), 32 * 12 + 32 * 0.0 * 2);
    EXPECT_EQ(outerRect.width(), 32 * 12 + 32 * 0.0 * 2);
    
    coordinateSystem.setMargin(1.0);
    EXPECT_EQ(coordinateSystem.getMargin(), 1.0);
    
    outerRect = coordinateSystem.getOuterRect(32);
    EXPECT_EQ(outerRect.x(), 0);
    EXPECT_EQ(outerRect.y(), 0);
    EXPECT_EQ(outerRect.width(), 32 * 12 + 32 * 1.0 * 2);
    EXPECT_EQ(outerRect.width(), 32 * 12 + 32 * 1.0 * 2);
    
    coordinateSystem.setMargin(2.5);
    EXPECT_EQ(coordinateSystem.getMargin(), 2.5);
    
    outerRect = coordinateSystem.getOuterRect(48);
    EXPECT_EQ(outerRect.x(), 0);
    EXPECT_EQ(outerRect.y(), 0);
    EXPECT_EQ(outerRect.width(), 48 * 12 + 48 * 2.5 * 2);
    EXPECT_EQ(outerRect.width(), 48 * 12 + 48 * 2.5 * 2);
}
