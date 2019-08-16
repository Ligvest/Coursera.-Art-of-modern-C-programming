#include <algorithm>

using namespace std;

// [first, last)
template <typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last,
                               UnaryPredicate pred) {
    ForwardIterator maxIt = std::find_if(first, last, pred);
    ForwardIterator it = std::find_if(maxIt, last, pred);
    while (it != last) {
        if ((*maxIt) < (*it)) {
            maxIt = it;
        }
        it = std::find_if(std::next(it), last, pred);
    }
    return maxIt;
}

}
