/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_ATLAS_IO_HPP
#define RPGMAPPER_MODEL_ATLAS_IO_HPP

#include <QFile>
#include <QStringList>

#include <rpgmapper/atlas.hpp>


namespace rpgmapper {
namespace model {


class IOResult {

    bool success = false;
    QStringList log;

public:

    explicit IOResult(bool success = false) : success{success} {}

    IOResult(bool success, QStringList const & log) : success{success}, log{log} {}

    QStringList & getLog() { return log; }

    QStringList const & getLog() const { return log; }

    bool hasSuccess() const { return success; }

    void setSuccess(bool success) { this->success = success; }

    friend IOResult & operator<<(IOResult & lvalue, bool rvalue);

    friend IOResult & operator<<(IOResult & lvalue, QString const & rvalue);

    friend IOResult & operator<<(IOResult & lvalue, IOResult const & rvalue);
};


class ReaderResult : public IOResult {

    AtlasPointer atlas = AtlasPointer{new InvalidAtlas};

public:

    AtlasPointer const & getAtlas() const { return atlas; }

    void setAtlas(AtlasPointer & atlas) { this->atlas = atlas; }

    friend ReaderResult & operator<<(ReaderResult & lvalue, ReaderResult const & rvalue);
};


inline IOResult & operator<<(IOResult & lvalue, bool rvalue) {
    lvalue.success = rvalue;
    return lvalue;
}


inline IOResult & operator<<(IOResult & lvalue, QString const & rvalue) {
    lvalue.log << rvalue;
    return lvalue;
}


inline IOResult & operator<<(IOResult & lvalue, IOResult const & rvalue) {
    lvalue.success = rvalue.success;
    lvalue.log << rvalue.log;
    return lvalue;
}


inline ReaderResult & operator<<(ReaderResult & lvalue, ReaderResult const & rvalue) {
    static_cast<IOResult &>(lvalue) << static_cast<IOResult const &>(rvalue);
    lvalue.atlas = rvalue.atlas;
    return lvalue;
}

class AtlasIO {

public:

    AtlasIO() = default;

    ReaderResult read(QFile & file) const;
    IOResult write(Atlas & atlas, QFile & file) const;
};


}
}

#endif
