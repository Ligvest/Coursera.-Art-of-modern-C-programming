#include "test_runner.h"

using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table {
   public:
    Table(size_t rows, size_t cols) { Resize(rows, cols); }

    std::pair<size_t, size_t> Size() const;
    void Resize(size_t newRows, size_t newCols);

    std::vector<T>& operator[](int rowNum);
    const std::vector<T>& operator[](int rowNum) const;

    size_t numRows_;
    size_t numCols_;

    std::vector<std::vector<T>> rows_;
};

template <typename T>
std::pair<size_t, size_t> Table<T>::Size() const {
    return std::make_pair(numRows_, numCols_);
}

template <typename T>
const std::vector<T>& Table<T>::operator[](int rowNum) const {
    return rows_[rowNum];
}

template <typename T>
std::vector<T>& Table<T>::operator[](int rowNum) {
    return rows_[rowNum];
}

template <typename T>
void Table<T>::Resize(size_t newRows, size_t newCols) {
    numRows_ = newRows;
    numCols_ = newCols;
    rows_.resize(numRows_);

    for (size_t i = 0; i < numRows_; ++i) {
        rows_[i].resize(numCols_);
    }
}

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
