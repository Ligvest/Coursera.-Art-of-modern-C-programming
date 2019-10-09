#pragma once

#include <algorithm>
#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
   public:
    SimpleVector() {}
    void operator=(const SimpleVector& other) {
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[size_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    void operator=(SimpleVector&& other) {
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    SimpleVector(const SimpleVector& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[size_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    SimpleVector(SimpleVector&& other) {
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    explicit SimpleVector(size_t size) : size_(size), capacity_(size), data_(new T[size]) {}
    ~SimpleVector();

    T& operator[](size_t index) { return data_[index]; }

    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }

    size_t Size() const { return size_; }
    size_t Capacity() const { return capacity_; }
    void PushBack(const T& value);
    void PushBack(T&& value);

   private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template <typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] data_;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
    if (capacity_ <= size_) {
        capacity_ = capacity_ > 0 ? capacity_ * 2 : 1;
        T* newData = new T[capacity_];
        std::move(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
    }

    data_[size_++] = value;
}

template <typename T>
void SimpleVector<T>::PushBack(T&& value) {
    if (capacity_ <= size_) {
        capacity_ = capacity_ > 0 ? capacity_ * 2 : 1;
        T* newData = new T[capacity_];
        std::move(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
    }

    data_[size_++] = std::move(value);
}
