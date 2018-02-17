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

    coordinateSystem.setOrigin(CoordinatesOrigin::bottomLeft);
    position = coordinateSystem.transpose(2, 7);
    point = QPoint{2, 2};
    EXPECT_EQ(position, point);

    positionF = coordinateSystem.transpose(2.0, 7.0);
    pointF = QPointF{2.0, 2.0};
    EXPECT_EQ(positionF, pointF);

    coordinateSystem.setOrigin(CoordinatesOrigin::bottomRight);
    position = coordinateSystem.transpose(3, 4);
    point = QPoint{6, 5};
    EXPECT_EQ(position, point);

    positionF = coordinateSystem.transpose(3.0, 4.0);
    pointF = QPointF{6.0, 5.0};
    EXPECT_EQ(positionF, pointF);

    coordinateSystem.setOrigin(CoordinatesOrigin::topLeft);
    position = coordinateSystem.transpose(0, 8);
    point = QPoint{0, 8};
    EXPECT_EQ(position, point);

    positionF = coordinateSystem.transpose(0.0, 8.0);
    pointF = QPointF{0.0, 8.0};
    EXPECT_EQ(positionF, pointF);

    coordinateSystem.setOrigin(CoordinatesOrigin::topRight);
    position = coordinateSystem.transpose(9, 2);
    point = QPoint{0, 2};
    EXPECT_EQ(position, point);

    positionF = coordinateSystem.transpose(9.0, 2.0);
    pointF = QPointF{0.0, 2.0};
    EXPECT_EQ(positionF, pointF);
}


TEST(CoordinateSystemTest, NumeralsNumeric) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.setNumeralXAxis("Numeric");
    coordinateSystem.setNumeralYAxis("Numeric");
    EXPECT_TRUE(coordinateSystem.getNumeralXAxis()->isValid());
    EXPECT_TRUE(coordinateSystem.getNumeralYAxis()->isValid());
    EXPECT_EQ(coordinateSystem.getNumeralXAxis()->name().toStdString(), "Numeric");
    EXPECT_EQ(coordinateSystem.getNumeralYAxis()->name().toStdString(), "Numeric");

    auto coordinates = coordinateSystem.getNumeralCoordinates(QPoint{0, 0});
    EXPECT_EQ(coordinates.x.toStdString(), "0");
    EXPECT_EQ(coordinates.y.toStdString(), "0");

    coordinates = coordinateSystem.getNumeralCoordinates(QPoint{7, 5});
    EXPECT_EQ(coordinates.x.toStdString(), "7");
    EXPECT_EQ(coordinates.y.toStdString(), "5");
}


TEST(CoordinateSystemTest, NumeralsAlphaSmall) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.setNumeralXAxis("AlphaSmall");
    coordinateSystem.setNumeralYAxis("AlphaSmall");
    EXPECT_TRUE(coordinateSystem.getNumeralXAxis()->isValid());
    EXPECT_TRUE(coordinateSystem.getNumeralYAxis()->isValid());
    EXPECT_EQ(coordinateSystem.getNumeralXAxis()->name().toStdString(), "AlphaSmall");
    EXPECT_EQ(coordinateSystem.getNumeralYAxis()->name().toStdString(), "AlphaSmall");

    auto coordinates = coordinateSystem.getNumeralCoordinates(QPoint{0, 0});
    EXPECT_EQ(coordinates.x.toStdString(), "a");
    EXPECT_EQ(coordinates.y.toStdString(), "a");

    coordinates = coordinateSystem.getNumeralCoordinates(QPoint{7, 5});
    EXPECT_EQ(coordinates.x.toStdString(), "h");
    EXPECT_EQ(coordinates.y.toStdString(), "f");
}


TEST(CoordinateSystemTest, NumeralsAlphaBig) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.setNumeralXAxis("AlphaBig");
    coordinateSystem.setNumeralYAxis("AlphaBig");
    EXPECT_TRUE(coordinateSystem.getNumeralXAxis()->isValid());
    EXPECT_TRUE(coordinateSystem.getNumeralYAxis()->isValid());
    EXPECT_EQ(coordinateSystem.getNumeralXAxis()->name().toStdString(), "AlphaBig");
    EXPECT_EQ(coordinateSystem.getNumeralYAxis()->name().toStdString(), "AlphaBig");

    auto coordinates = coordinateSystem.getNumeralCoordinates(QPoint{0, 0});
    EXPECT_EQ(coordinates.x.toStdString(), "A");
    EXPECT_EQ(coordinates.y.toStdString(), "A");

    coordinates = coordinateSystem.getNumeralCoordinates(QPoint{7, 5});
    EXPECT_EQ(coordinates.x.toStdString(), "H");
    EXPECT_EQ(coordinates.y.toStdString(), "F");
}


TEST(CoordinateSystemTest, NumeralsRoman) {

    CoordinateSystem coordinateSystem;
    coordinateSystem.setNumeralXAxis("Roman");
    coordinateSystem.setNumeralYAxis("Roman");
    EXPECT_TRUE(coordinateSystem.getNumeralXAxis()->isValid());
    EXPECT_TRUE(coordinateSystem.getNumeralYAxis()->isValid());
    EXPECT_EQ(coordinateSystem.getNumeralXAxis()->name().toStdString(), "Roman");
    EXPECT_EQ(coordinateSystem.getNumeralYAxis()->name().toStdString(), "Roman");

    auto coordinates = coordinateSystem.getNumeralCoordinates(QPoint{0, 0});
    EXPECT_EQ(coordinates.x.toStdString(), "O");
    EXPECT_EQ(coordinates.y.toStdString(), "O");

    coordinates = coordinateSystem.getNumeralCoordinates(QPoint{7, 5});
    EXPECT_EQ(coordinates.x.toStdString(), "VII");
    EXPECT_EQ(coordinates.y.toStdString(), "V");
}
