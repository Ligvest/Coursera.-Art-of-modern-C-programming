#pragma once

#include <array>

template <typename T, size_t N>
class StackVector {
   public:
    explicit StackVector(size_t a_size = 0) : size_(a_size) {
        if (size_ > capacity_) {
            throw std::invalid_argument("wrong capacity parameter");
        }
    }

    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    const T* begin() const { return &data_[0]; }
    const T* end() const { return &data_[size_]; }
    T* begin() { return &data_[0]; }
    T* end() { return &data_[size_]; }

    size_t Size() const { return size_; }
    size_t Capacity() const { return capacity_; }

    void PushBack(const T& value) {
        if (size_ == capacity_) {
            throw std::overflow_error("can't to push back");
        }
        data_[size_++] = value;
    }
    T PopBack() {
        if (size_ == 0) {
            throw std::underflow_error("can't to pop back");
        }
        return data_[--size_];
    }

   private:
    std::array<T, N> data_;
    size_t size_ = 0;
    size_t capacity_ = N;
};
