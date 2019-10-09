#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Deque {
   public:
    Deque();
    inline bool Empty() const;                //+
    inline size_t Size() const;               //+
    T& operator[](size_t index);              //+
    const T& operator[](size_t index) const;  //+
    T& At(size_t index);                      //+
    const T& At(size_t index) const;          //+
    T& Front();                               //+
    const T& Front() const;                   //+
    T& Back();                                //+
    const T& Back() const;                    //+
    void PushFront(const T&);                 //+
    void PushBack(const T&);                  //+

   private:
    std::vector<T> frontDeque;
    std::vector<T> backDeque;
    size_t size_;
};

template <typename T>
Deque<T>::Deque() {
    size_ = 0;
}

template <typename T>
bool Deque<T>::Empty() const {
    return size_ > 0 ? false : true;
}

template <typename T>
size_t Deque<T>::Size() const {
    return size_;
}

template <typename T>
T& Deque<T>::operator[](size_t index) {
    if (frontDeque.size() > index) {
        size_t reversedIndex = (frontDeque.size() - 1) - index;
        return frontDeque[reversedIndex];
    } else {
        return backDeque[index - frontDeque.size()];
    }
}

template <typename T>
const T& Deque<T>::operator[](size_t index) const {
    if (frontDeque.size() > index) {
        size_t reversedIndex = (frontDeque.size() - 1) - index;
        return frontDeque[reversedIndex];
    } else {
        return backDeque[index - frontDeque.size()];
    }
}

template <typename T>
T& Deque<T>::At(size_t index) {
    if (index >= Size()) {
        throw std::out_of_range("T& At(): Index=" + std::to_string(index) + ", but deque size is " +
                                std::to_string(Size()));
    }
    return operator[](index);
}

template <typename T>
const T& Deque<T>::At(size_t index) const {
    if (index >= Size()) {
        throw std::out_of_range("const T& At() const: Index=" + std::to_string(index) +
                                ", but deque size is " + std::to_string(Size()));
    }
    return operator[](index);
}

template <typename T>
T& Deque<T>::Front() {
    if (frontDeque.size() > 0) {
        return frontDeque.back();
    } else {
        return backDeque.front();
    }
}

template <typename T>
const T& Deque<T>::Front() const {
    if (frontDeque.size() > 0) {
        return frontDeque.back();
    } else {
        return backDeque.front();
    }
}

template <typename T>
T& Deque<T>::Back() {
    if (backDeque.size() > 0) {
        return backDeque.back();
    } else {
        return frontDeque.front();
    }
}

template <typename T>
const T& Deque<T>::Back() const {
    if (backDeque.size() > 0) {
        return backDeque.back();
    } else {
        return frontDeque.front();
    }
}

template <typename T>
void Deque<T>::PushFront(const T& val) {
    frontDeque.push_back(val);
    ++size_;
}

template <typename T>
void Deque<T>::PushBack(const T& val) {
    backDeque.push_back(val);
    ++size_;
}
