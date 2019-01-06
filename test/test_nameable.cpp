/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/nameable.hpp>

using namespace rpgmapper::model;


TEST(NameableTest, CreateNameable) {

    Nameable foo("foo");
    
    std::string n = foo;
    ASSERT_EQ(n, R"({ "name": "foo" })");
}
