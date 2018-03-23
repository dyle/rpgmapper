/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_IO_WRITER_RESULT_HPP
#define RPGMAPPER_MODEL_IO_WRITER_RESULT_HPP

#include <QStringList>
#include <utility>


namespace rpgmapper {
namespace model {
namespace io {


class WriterResult {

    bool success = false;
    QStringList log;

public:

    explicit WriterResult(bool success = false)
        : WriterResult{success, QStringList{}} {
    }

    WriterResult(bool success, QStringList log)
        : success{success},
          log{std::move(log)} {
    }

    virtual ~WriterResult() = default;

    QStringList & getLog() {
        return log;
    }

    QStringList const & getLog() const {
        return log;
    }

    bool hasSuccess() const {
        return success;
    }

    void setSuccess(bool success) {
        this->success = success;
    }

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
}

#endif
