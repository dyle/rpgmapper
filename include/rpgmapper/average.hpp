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

    using AverageElement = struct {
        T value;
        std::chrono::system_clock::time_point timeStamp;
    };

    using container = std::list<AverageElement>;

private:

    unsigned int maxElements = 10;
    std::chrono::milliseconds maxDuration;

    mutable container elements;
    mutable T currentSum = 0;

public:

    explicit Average(unsigned int maxElements = 10, std::chrono::milliseconds maxDuration = std::chrono::milliseconds(0))
            : maxElements{maxElements}, maxDuration{maxDuration} {};

    Average & add(T value) {
        elements.push_back({value, std::chrono::system_clock::now()});
        currentSum += value;
        return *this;
    }

    T average() const {
        if (elements.size() == 0) {
            return 0;
        }
        if (maxElements == 0) {
            return averageOverTime();
        }
        return averageOverSize();
    }

private:

    T averageOverSize() const {

        while (elements.size() > maxElements) {
            auto iter = std::begin(elements);
            currentSum -= (*iter).value;
            elements.erase(std::begin(elements));
        }
        return elements.size() > 0 ? currentSum / elements.size() : T{0};
    }


    T averageOverTime() const {

        auto oldest = std::chrono::system_clock::now() - maxDuration;
        auto header = std::begin(elements);
        while ((header != std::end(elements)) && ((*header).timeStamp < oldest)) {
            currentSum -= (*header).value;
            elements.erase(header);
            header = std::begin(elements);
        }

        return elements.size() > 0 ? currentSum / elements.size() : T{0};
    }
};


}
}


#endif
