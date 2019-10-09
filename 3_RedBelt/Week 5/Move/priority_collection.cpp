#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include "test_runner.h"
using namespace std;

template <typename T>
class PriorityCollection {
   public:
    // copy methods
    PriorityCollection(const PriorityCollection&) = delete;
    void operator=(const PriorityCollection&) = delete;

    // move methods
    PriorityCollection(PriorityCollection&& other) = default;
    PriorityCollection& operator=(PriorityCollection&& other) = default;

    // ctor and dtor
    PriorityCollection() = default;
    ~PriorityCollection() = default;

    using Id = typename std::list<T>::iterator;

    // Добавить объект с нулевым приоритетом
    Id Add(T object) {
        data_.push_back(std::move(object));
        auto itemIt = std::prev(data_.end());
        ItemInfo newItemInfo(itemIt, 0, ++itemCounter);
        worths_.insert(newItemInfo);
        ids_.insert(newItemInfo);
        return newItemInfo.itemIt;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
        for (auto curPos = range_begin; curPos != range_end; ++curPos, ++ids_begin) {
            *ids_begin = Add(std::move(*curPos));
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        if (ids_.count({id, 0}) > 0) {
            return true;
        }
        return false;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const { return *id; }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        auto& itemInfo = *ids_.find({id, 0});
        ItemInfo newItemInfo(itemInfo);
        newItemInfo.promote();

        auto worthPos = worths_.find(itemInfo);
        while (worthPos->itemIt != id) {
            ++worthPos;
        }

        worths_.erase(worthPos);
        ids_.erase(itemInfo);

        worths_.insert(newItemInfo);
        ids_.insert(newItemInfo);
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const {
        const ItemInfo& itemInfo = *std::prev(worths_.end());
        return {*itemInfo.itemIt, itemInfo.itemPriority};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax() {
        const ItemInfo& itemInfo = *std::prev(worths_.end());
        std::pair<T, int> retPair(std::move(*itemInfo.itemIt), itemInfo.itemPriority);
        data_.erase(itemInfo.itemIt);
        ids_.erase(itemInfo);
        worths_.erase(itemInfo);
        return retPair;
    }

   private:
    using Item = int;
    struct ItemInfo {
        // item iterator
        typename std::list<T>::iterator itemIt;
        T* itemAddr = nullptr;

        // item priority
        int itemPriority = 0;

        // order in same priority sequence
        unsigned long long itemOrder = 0;

        // ctor
        ItemInfo(typename std::list<T>::iterator it, int pr, unsigned long long order = 0)
            : itemIt(it), itemPriority(pr), itemOrder(order) {
            itemAddr = &(*it);
        }

        // cpy ctor
        ItemInfo(const ItemInfo& other) {
            itemIt = other.itemIt;
            itemAddr = other.itemAddr;
            itemPriority = other.itemPriority;
            itemOrder = other.itemOrder;
        }

        // promote
        void promote() { ++itemPriority; }
    };

    struct ComparePriority {
        bool operator()(const ItemInfo& lhs, const ItemInfo& rhs) const {
            return lhs.itemPriority < rhs.itemPriority ||
                   (lhs.itemPriority == rhs.itemPriority && lhs.itemOrder < rhs.itemOrder);
        }
    };
    class CompareItemAddr {
       public:
        bool operator()(const ItemInfo& lhs, const ItemInfo& rhs) const {
            return &(*lhs.itemIt) < &(*rhs.itemIt);
        }
    };

   public:
    unsigned long long itemCounter = 0;
    std::set<ItemInfo, CompareItemAddr> ids_;
    std::set<ItemInfo, ComparePriority> worths_;
    std::list<T> data_;
};

class StringNonCopyable : public string {
   public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

template <typename T>
void showInfo(const PriorityCollection<T>& strings) {
    std::cout << "data_:\n";
    for (auto& item : strings.data_) {
        std::cout << item << std::endl;
    }
    std::cout << std::endl;

    std::cout << "ids_ iterators:\n";
    for (auto& item : strings.ids_) {
        std::cout << *item.itemIt << std::endl;
    }
    std::cout << std::endl;

    std::cout << "ids_ addresses:\n";
    for (auto& item : strings.ids_) {
        std::cout << *item.itemAddr << std::endl;
    }
    std::cout << std::endl;

    std::cout << "data_ iterators:\n";
    for (auto& item : strings.worths_) {
        std::cout << *item.itemIt << std::endl;
    }
    std::cout << std::endl;

    std::cout << "data_ addresses:\n";
    for (auto& item : strings.worths_) {
        std::cout << *item.itemAddr << std::endl;
    }
    std::cout << std::endl;
}

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    std::cout << *white_id << std::endl;
    showInfo(strings);
    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
