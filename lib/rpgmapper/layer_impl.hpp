/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_IMPL_HPP
#define RPGMAPPER_MODEL_LAYER_IMPL_HPP


#include <rpgmapper/map.hpp>
#include <rpgmapper/layer.hpp>

using namespace rpgmapper::model;


namespace rpgmapper {
namespace model {


class Layer::Impl final {

    Map * map = nullptr;

public:

    explicit Impl(Map * map);

    Impl(Impl const & ) = delete;
};

}
}


#endif
