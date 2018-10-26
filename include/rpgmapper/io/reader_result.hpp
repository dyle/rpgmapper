/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_IO_READER_RESULT_HPP
#define RPGMAPPER_MODEL_IO_READER_RESULT_HPP

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/io/result.hpp>


namespace rpgmapper {
namespace model {
namespace io {


/**
 * This class encapsulates the read operation result.
 */
class ReaderResult : public Result {
    
    /**
     * The atlas we read.
     */
    AtlasPointer atlas = AtlasPointer{new InvalidAtlas};

public:
    
    /**
     * Constructor.
     *
     * @param   success     has the operation succeeded flag
     */
    ReaderResult(AtlasPointer & atlas, bool success, QStringList log);
    
    /**
     * Destructor.
     */
    ~ReaderResult() override = default;

    /**
     * Returns the atlas loaded.
     *
     * @return  the loaded atlas.
     */
    AtlasPointer const & getAtlas() const {
        return atlas;
    }
    
private:
    
    /**
     * Sets the atlas loaded.
     *
     * @param   atlas       the atlas we've loaded.
     */
/*
    void setAtlas(AtlasPointer & atlas) {
        this->atlas = atlas;
    }
*/
//    friend ReaderResult & operator<<(ReaderResult & lvalue, ReaderResult const & rvalue);
};


/*
inline ReaderResult & operator<<(ReaderResult & lvalue, ReaderResult const & rvalue) {

    static_cast<WriterResult &>(lvalue) << static_cast<WriterResult const &>(rvalue);
    lvalue.atlas = rvalue.atlas;
    return lvalue;
}
*/

}
}
}

#endif
