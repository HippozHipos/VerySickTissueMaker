#pragma once

#include <atomic>
#include <memory>

template <typename T>
class SingletonHolder {
public:
    using ObjectType = T;

    static T* Instance() {
        T* tmp = instance.load(std::memory_order_acquire);
        if (tmp == nullptr) {
            tmp = new T();
            T* expected = nullptr;
            if (!instance.compare_exchange_strong(expected, tmp,
                std::memory_order_acq_rel,
                std::memory_order_acquire)) {
                delete tmp;
                tmp = expected;
            }
        }
        return tmp;
    }

    SingletonHolder(const SingletonHolder&) = delete;
    SingletonHolder& operator=(const SingletonHolder&) = delete;

private:
    SingletonHolder() = default;
    static std::atomic<T*> instance;
};

template <typename T>
std::atomic<T*> SingletonHolder<T>::instance{ nullptr };