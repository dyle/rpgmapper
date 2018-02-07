/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_OPERATION_RESULT_HPP
#define RPGMAPPER_MODEL_OPERATION_RESULT_HPP

#include <QStringList>

namespace rpgmapper {
namespace model {

struct OperationResult {

    bool success = false;

    QStringList log;
};


inline OperationResult & operator<<(OperationResult & lvalue, OperationResult const & rvalue) {
    lvalue.success = rvalue.success;
    lvalue.log << rvalue.log;
    return lvalue;
}


}
}


#endif
