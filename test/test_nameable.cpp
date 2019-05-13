/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/nameable.hpp>
#include <rpgmapper/exception/invalid_json.hpp>

using namespace rpgmapper::model;


TEST(NameableTest, getName) {

    Nameable foo("foo");

    ASSERT_EQ(foo.getName().toStdString(), "foo");
}


TEST(NameableTest, setName) {

    Nameable foo("foo");
    ASSERT_EQ(foo.getName().toStdString(), "foo");
    foo.setName("bar");
    ASSERT_EQ(foo.getName().toStdString(), "bar");
}


TEST(NameableTest, static_cast_std_string) {

    Nameable foo("foo");
    
    std::string s = static_cast<std::string>(foo);
    ASSERT_EQ(s, R"({"name": "foo"})");
}


TEST(NameableTest, setJson) {

    Nameable foo("foo");

    QJsonObject json = {{"name", "bar"}};
    foo.applyJson(json);
    ASSERT_EQ(foo.getName().toStdString(), "bar");
}


TEST(NameableTest, setJsonInvalid) {

    Nameable foo("foo");

    QJsonObject json = {{"x", "FAIL"}};
    ASSERT_THROW(foo.applyJson(json), rpgmapper::model::exception::invalid_json);
}
