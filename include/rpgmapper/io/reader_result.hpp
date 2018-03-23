/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_IO_READER_RESULT_HPP
#define RPGMAPPER_MODEL_IO_READER_RESULT_HPP


#include <rpgmapper/atlas.hpp>
#include <rpgmapper/io/writer_result.hpp>


namespace rpgmapper {
namespace model {
namespace io {


class ReaderResult : public WriterResult {

    AtlasPointer atlas = AtlasPointer{new InvalidAtlas};

public:

    virtual ~ReaderResult() = default;

    AtlasPointer const & getAtlas() const {
        return atlas;
    }

    void setAtlas(AtlasPointer & atlas) {
        this->atlas = atlas;
    }

    friend ReaderResult & operator<<(ReaderResult & lvalue, ReaderResult const & rvalue);
};


inline ReaderResult & operator<<(ReaderResult & lvalue, ReaderResult const & rvalue) {

    static_cast<WriterResult &>(lvalue) << static_cast<WriterResult const &>(rvalue);
    lvalue.atlas = rvalue.atlas;
    return lvalue;
}


}
}
}

#endif
