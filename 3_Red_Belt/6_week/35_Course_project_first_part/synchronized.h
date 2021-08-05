#pragma once

#include <future>

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) : value(std::move(initial)) {}

    struct Access {
        Access(T& value, std::mutex& mutex) : ref_to_value(value), guard(mutex){}

        T& ref_to_value;
    private:
        std::lock_guard<std::mutex&> guard;
    };

    Access GetAccess() {
        //return Access(value, std::lock_guard(mutex));
        return {value, mutex};
    }

    Access GetAccess() const {
        //return Access(value, std::lock_guard(mutex));
        return {value, mutex};
    }

private:
    T value;
    std::mutex mutex;
};
