/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_WRITER_RESULT_HPP
#define RPGMAPPER_MODEL_WRITER_RESULT_HPP

#include <QStringList>


namespace rpgmapper {
namespace model {


class WriterResult {

    bool success = false;
    QStringList log;

public:

    explicit WriterResult(bool success = false) : success{success} {}

    virtual ~WriterResult() = default;

    WriterResult(bool success, QStringList const & log) : success{success}, log{log} {}

    QStringList & getLog() { return log; }

    QStringList const & getLog() const { return log; }

    bool hasSuccess() const { return success; }

    void setSuccess(bool success) { this->success = success; }

    friend WriterResult & operator<<(WriterResult & lvalue, bool rvalue);

    friend WriterResult & operator<<(WriterResult & lvalue, QString const & rvalue);

    friend WriterResult & operator<<(WriterResult & lvalue, WriterResult const & rvalue);
};

inline WriterResult & operator<<(WriterResult & lvalue, bool rvalue) {
    lvalue.success = rvalue;
    return lvalue;
}

inline WriterResult & operator<<(WriterResult & lvalue, QString const & rvalue) {
    lvalue.log << rvalue;
    return lvalue;
}

inline WriterResult & operator<<(WriterResult & lvalue, WriterResult const & rvalue) {
    lvalue.success = rvalue.success;
    lvalue.log << rvalue.log;
    return lvalue;
}


}
}

#endif
