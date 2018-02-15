/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
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


TEST(CoordinateSystemTest, TransposeCoordinates) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.resize(10, 10);
    Coordinates position;
    CoordinatesF positionF;
    QPoint point;
    QPointF pointF;

    coordinateSystem.setOrigin(CoordinateOrigin::bottomLeft);
    position = coordinateSystem.transpose(2, 7);
    point = QPoint{2, 2};
    EXPECT_EQ(position, point);

    positionF = coordinateSystem.transpose(2.0, 7.0);
    pointF = QPointF{2.0, 2.0};
    EXPECT_EQ(positionF, pointF);

    coordinateSystem.setOrigin(CoordinateOrigin::bottomRight);
    position = coordinateSystem.transpose(3, 4);
    point = QPoint{6, 5};
    EXPECT_EQ(position, point);

    positionF = coordinateSystem.transpose(3.0, 4.0);
    pointF = QPointF{6.0, 5.0};
    EXPECT_EQ(positionF, pointF);

    coordinateSystem.setOrigin(CoordinateOrigin::topLeft);
    position = coordinateSystem.transpose(0, 8);
    point = QPoint{0, 8};
    EXPECT_EQ(position, point);

    positionF = coordinateSystem.transpose(0.0, 8.0);
    pointF = QPointF{0.0, 8.0};
    EXPECT_EQ(positionF, pointF);

    coordinateSystem.setOrigin(CoordinateOrigin::topRight);
    position = coordinateSystem.transpose(9, 2);
    point = QPoint{0, 2};
    EXPECT_EQ(position, point);

    positionF = coordinateSystem.transpose(9.0, 2.0);
    pointF = QPointF{0.0, 2.0};
    EXPECT_EQ(positionF, pointF);
}
