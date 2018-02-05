/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_CHANGEABLE_HPP
#define RPGMAPPER_MODEL_CHANGEABLE_HPP


#include <QObject>


namespace rpgmapper {
namespace model {


class Changeable : public QObject {

    Q_OBJECT

    bool modified = false;

public:

    explicit Changeable(QObject * parent = nullptr);

    virtual bool isModified() const { return modified; }

    virtual void setModified(bool modified);

signals:

    void changed();

};


}
}


#endif
