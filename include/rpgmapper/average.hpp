/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_AVERAGE_HPP
#define RPGMAPPER_MODEL_AVERAGE_HPP


#include <chrono>
#include <list>
#include <numeric>


namespace rpgmapper {
namespace model {


template <typename T> class Average {

public:

    using Element = struct {
        T value;
        std::chrono::system_clock::time_point timeStamp;
    };

    using Container = std::list<Element>;

protected:

    mutable Container container;
    mutable T currentSum = 0;

public:

    Average() = default;

    Average & add(T value) {
        container.push_back({value, std::chrono::system_clock::now()});
        currentSum += value;
        return *this;
    }

    T average() const {
        trim();
        return container.size() > 0 ? currentSum / container.size() : T{0};
    }

private:

    virtual void trim() const = 0;
};


template <typename T> class AverageOverSize : public Average<T> {

    unsigned int maxElements = 10;

    using Average<T>::container;
    using Average<T>::currentSum;

public:

    explicit AverageOverSize(unsigned int maxElements = 10) : maxElements{maxElements} {};

private:

    void trim() const override {
        while (container.size() > maxElements) {
            auto iter = std::begin(container);
            currentSum -= (*iter).value;
            container.erase(std::begin(container));
        }
    }
};


template <typename T> class AverageOverTime : public Average<T> {

    std::chrono::milliseconds maxDuration;

    using Average<T>::container;
    using Average<T>::currentSum;

public:

    explicit AverageOverTime(std::chrono::milliseconds maxDuration = std::chrono::milliseconds(1000))
            : maxDuration{maxDuration} {};

private:

    void trim() const override {
        auto oldest = std::chrono::system_clock::now() - maxDuration;
        auto header = std::begin(container);
        while ((header != std::end(container)) && ((*header).timeStamp < oldest)) {
            currentSum -= (*header).value;
            container.erase(header);
            header = std::begin(container);
        }
    }
};


}
}


static inline rpgmapper::model::Average<int> & operator<<(rpgmapper::model::Average<int> & average,
                                                          int value) {
    return average.add(value);
}

static inline rpgmapper::model::Average<long> & operator<<(rpgmapper::model::Average<long> & average,
                                                           long value) {
    return average.add(value);
}

static inline rpgmapper::model::Average<float> & operator<<(rpgmapper::model::Average<float> & average,
                                                            float value) {
    return average.add(value);
}

static inline rpgmapper::model::Average<double> & operator<<(rpgmapper::model::Average<double> & average,
                                                             double value) {
    return average.add(value);
}


#endif
