#pragma once

template<typename T>
class Singleton {
protected:
    Singleton() {};
    ~Singleton() {};

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static T& getInstance() {
        static std::unique_ptr<T> instance(new T);
        return *instance;
    }
};
