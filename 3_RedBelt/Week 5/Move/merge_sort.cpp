#include <algorithm>
#include <memory>
#include <vector>
#include "test_runner.h"

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    int rangeSize = std::distance(range_begin, range_end);
    if (rangeSize < 2) {
        return;
    }

    int partSize = rangeSize / 3;

    using Range = std::vector<typename RandomIt::value_type>;

    // first part
    auto begin = range_begin;
    auto end = range_begin + partSize;
    Range firstPart(std::make_move_iterator(begin), std::make_move_iterator(end));
    MergeSort(firstPart.begin(), firstPart.end());

    // second part
    begin += partSize;
    end += partSize;
    Range secPart(std::make_move_iterator(begin), std::make_move_iterator(end));
    MergeSort(secPart.begin(), secPart.end());

    // merge first and second
    Range firstPlusSec;
    std::merge(std::make_move_iterator(firstPart.begin()), std::make_move_iterator(firstPart.end()),
               std::make_move_iterator(secPart.begin()), std::make_move_iterator(secPart.end()),
               std::back_inserter(firstPlusSec));

    // third part
    begin += partSize;
    end += partSize;
    Range thirdPart(std::make_move_iterator(begin), std::make_move_iterator(end));
    MergeSort(thirdPart.begin(), thirdPart.end());

    std::merge(std::make_move_iterator(firstPlusSec.begin()),
               std::make_move_iterator(firstPlusSec.end()),
               std::make_move_iterator(thirdPart.begin()), std::make_move_iterator(thirdPart.end()),
               range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
