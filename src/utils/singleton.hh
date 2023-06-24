#pragma once

#include <iostream>
#include <string>

template<typename T>
class Singleton
{
public:
    Singleton(const Singleton &) = delete;

    Singleton &operator=(Singleton) = delete;

    static T *instance()
    {
        if (instance_ == nullptr)
            instance_ = new T();
        return instance_;
    }

protected:
    Singleton() = default;

    static T *instance_;
};

template<typename T>
T *Singleton<T>::instance_ = nullptr;