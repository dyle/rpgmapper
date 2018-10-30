/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_AVERAGE_HPP
#define RPGMAPPER_MODEL_AVERAGE_HPP

#include <chrono>
#include <list>


namespace rpgmapper {
namespace model {


/**
 * This template defines a basic moving average.
 *
 * @tparam T    type of the values to claculate the average.
 */
template<typename T> class Average {

public:

    /**
     * Type of a single element.
     */
    using Element = struct {
        T value;                                                /**< The value. */
        std::chrono::system_clock::time_point timeStamp;        /**< The insertion time into the average. */
    };

    using Container = std::list<Element>;                       /**< This type contains all elements. */
    
protected:

    mutable Container container;        /**< Holds all values. */
    mutable T currentSum = 0;           /**< Intermediate sum of all values. */

public:

    /**
     * Constructor
     */
    Average() = default;

    /**
     * Adds a single value.
     *
     * @param   value       the value to add.
     * @return  *this
     */
    Average & add(T value) {
        container.push_back({value, std::chrono::system_clock::now()});
        currentSum += value;
        return *this;
    }
    
    /**
     * Calculate the average.
     *
     * @return  the avarage of all values held in this structure.
     */
    T average() const {
        trim();
        return container.size() > 0 ? currentSum / container.size() : T{0};
    }
    
    /**
     * Returns all items known.
     *
     * @return  all items of the average structure.
     */
    Container const & items() const {
        trim();
        return container;
    }

    /**
     * Gets the sum of all items in this container.
     *
     * @return  the sum of all values in the container.
     */
    T sum() const {
        trim();
        return currentSum;
    }

private:

    /**
     * Cuts off some values.
     */
    virtual void trim() const = 0;
};


/**
 * This is a moving average with holds up to the maxElements.
 */
template<typename T> class AverageOverSize : public Average<T> {

    unsigned int maxElements = 10;      /**< maximum amount of elements managed. */

    using Average<T>::container;
    using Average<T>::currentSum;

public:

    /**
     * Constructor
     *
     * @param   maxElements     maximum Number of elements to calcultae the average for.
     */
    explicit AverageOverSize(unsigned int maxElements = 10) : maxElements{maxElements} {};

private:

    /**
     * Cuts off the excess entries.
     */
    void trim() const override {
        while (container.size() > maxElements) {
            auto iter = std::begin(container);
            currentSum -= (*iter).value;
            container.erase(std::begin(container));
        }
    }
};


/**
 * This is a moving avberage over time.
 */
template<typename T> class AverageOverTime : public Average<T> {

    std::chrono::milliseconds maxDuration;          /**< maximum lifetime of a value in milliseconds. */

    using Average<T>::container;
    using Average<T>::currentSum;

public:

    /**
     * Creates a moving average of all values inserted in the last maxDuration milliseconds.
     *
     * @param   maxDuration     milliseconds managed by this moving average.
     */
    explicit AverageOverTime(std::chrono::milliseconds maxDuration = std::chrono::milliseconds(1000))
            : maxDuration{maxDuration} {};

private:

    /**
     * Cuts off values too old.
     */
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

/**
 * Streams any value into a moving average instance.
 *
 * @tparam  T           type of the moving average values.
 * @tparam  U           type of the value pushed into the average instance.
 * @param   average     the moving average instance.
 * @param   value       the value pushed into.
 * @return  average instance (modified)
 */
template<typename T, typename U> rpgmapper::model::Average<T> & operator<<(rpgmapper::model::Average<T> & average,
                                                                           U value) {
    return average.add(value);
}


#endif
