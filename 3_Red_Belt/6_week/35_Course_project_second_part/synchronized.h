#pragma once

#include <future>

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) :
        value(std::move(initial)) {}

    struct Access {
        Access(T& value, std::mutex& mutex) :
            ref_to_value(value), mutex(mutex){
            mutex.lock();
        }

        ~Access() {
            mutex.unlock();
        }

        T& ref_to_value;
    private:
        std::mutex& mutex;
    };

    Access GetAccess() {
        return Access(value, mutex);
        //return {value, mutex};
    }

    std::mutex& GetMutex() {
        return mutex;
    }

private:
    T value;
    std::mutex mutex;
};
