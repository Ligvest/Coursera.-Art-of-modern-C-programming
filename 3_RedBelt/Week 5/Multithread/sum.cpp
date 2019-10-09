#include <future>
#include <list>
#include <vector>
#include "test_runner.h"
using namespace std;

template <typename Iterator>
class IteratorRange {
   public:
    IteratorRange(Iterator begin, Iterator end)
        : begin_(begin), end_(end), size_(std::distance(begin_, end_)) {}

    Iterator begin() { return begin_; }
    Iterator end() { return end_; }
    const Iterator begin() const { return begin_; }
    const Iterator end() const { return end_; }

    inline size_t size() const { return size_; }

    using iterator = Iterator;

   private:
    Iterator begin_;
    Iterator end_;
    size_t size_;
};

template <typename Iterator>
class Paginator {
    using PagesIterator = typename std::vector<IteratorRange<Iterator>>::iterator;

   public:
    Paginator(Iterator begin, Iterator end, size_t pageSize)
        : begin_(begin),
          end_(end),
          pageSize_(pageSize),
          sequenceSize_(std::distance(begin_, end_)) {
        divideOnPages();
    }

    // divide into several IteratorRanges
    void divideOnPages() {
        Iterator pageBegin = begin_;
        Iterator pageEnd;
        int rest = sequenceSize_;

        while (rest > 0) {
            pageEnd = std::next(pageBegin, std::min(pageSize_, rest));
            pages_.emplace_back(IteratorRange{pageBegin, pageEnd});

            pageBegin = pageEnd;
            rest -= pageSize_;
        }
    }

    inline size_t size() const { return pages_.size(); }
    inline PagesIterator begin() { return pages_.begin(); }
    inline PagesIterator end() { return pages_.end(); }

   private:
    std::vector<IteratorRange<Iterator>> pages_;

    Iterator begin_;
    Iterator end_;
    int pageSize_;
    int sequenceSize_;
};

template <typename Container>
Paginator<typename Container::iterator> Paginate(Container& container, size_t page_size) {
    return Paginator<typename Container::iterator>(container.begin(), container.end(), page_size);
}

template <typename Container>
Paginator<typename Container::const_iterator> Paginate(const Container& container,
                                                       size_t page_size) {
    return Paginator<typename Container::const_iterator>(container.begin(), container.end(),
                                                         page_size);
}

int64_t CalculateMatrixSumSingle(IteratorRange<vector<vector<int>>::const_iterator> itRange) {
    int64_t sum = 0;
    for (auto& row : itRange) {
        for (int num : row) {
            sum += num;
        }
    }
    return sum;
}
int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    size_t pageSize = matrix.size() / 8;
    std::vector<future<int64_t>> futures;
    for (auto& page : Paginate(matrix, pageSize)) {
        futures.push_back(async([page] { return CalculateMatrixSumSingle(page); }));
    }

    int64_t sum = 0;
    for (auto& future : futures) {
        sum += future.get();
    }

    return sum;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
