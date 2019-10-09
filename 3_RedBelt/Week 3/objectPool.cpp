#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
using namespace std;

template <class T>
class ObjectPool {
   public:
    T* Allocate();
    T* TryAllocate();

    void Deallocate(T* object);

    ~ObjectPool();

   private:
    std::queue<T*> deallocated_;
    std::set<T*> allocated_;
    // Добавьте сюда поля
};
template <typename T>
ObjectPool<T>::~ObjectPool() {
    for (auto allocObj : allocated_) {
        delete allocObj;
    }
    allocated_.clear();

    if (deallocated_.size() > 0) {
        int deallocSize = deallocated_.size();
        for (int i = 0; i < deallocSize; ++i) {
            delete deallocated_.front();
            deallocated_.pop();
        }
    }
}

template <typename T>
T* ObjectPool<T>::Allocate() {
    T* object;
    if (deallocated_.size() > 0) {
        object = deallocated_.front();
        deallocated_.pop();
    } else {
        object = new T;
    }
    allocated_.emplace(object);
    return object;
}

template <typename T>
T* ObjectPool<T>::TryAllocate() {
    T* object = nullptr;
    if (!deallocated_.empty()) {
        object = Allocate();
    }

    return object;
}

template <typename T>
void ObjectPool<T>::Deallocate(T* object) {
    auto objectPos = allocated_.find(object);
    if (objectPos == allocated_.end()) {
        throw std::invalid_argument("can't to deallocate due object is not allocated");
    } else {
        deallocated_.push(*objectPos);
        allocated_.erase(objectPos);
    }
}

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
