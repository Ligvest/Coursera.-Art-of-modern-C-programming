#include "test_runner.h"

#include <algorithm>
#include <list>
#include <set>
#include <string>
#include <vector>

using namespace std;

template <typename String>
using Group = vector<String>;

template <typename String>  // == <
using Char = typename String::value_type;

template <typename String>
bool includesSymbols(const String& symbols, const String& word) {
    std::set<Char<String>> toCheckSize;
    bool mismatch = true;
    bool rightWord = true;
    for (const auto& strChar : word) {
        mismatch = true;
        for (const auto& matchChar : symbols) {
            if (matchChar == strChar) {
                mismatch = false;
                break;
            }
        }

        if (mismatch) {
            rightWord = false;
            break;
        }
        toCheckSize.insert(strChar);
    }

    return rightWord && symbols.size() == toCheckSize.size();
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    //    move all words to list
    std::list<String> words;
    for (auto& str : strings) {
        words.push_back(std::move(str));
    }

    // copy sorted and uniqued words to special list
    std::list<String> wordsToMatch;
    for (auto str : words) {
        std::sort(str.begin(), str.end());
        auto uniquePos = std::unique(str.begin(), str.end());
        str.erase(uniquePos, str.end());
        wordsToMatch.push_back(std::move(str));
    }
    wordsToMatch.sort();
    wordsToMatch.unique();

    vector<Group<String>> groups;
    Group<String> group;
    for (auto& matchSymbols : wordsToMatch) {
        for (auto wordPos = words.begin(); wordPos != words.end();) {
            if (includesSymbols(matchSymbols, *wordPos)) {
                group.push_back(std::move(*wordPos));
                ++wordPos;
                words.erase(std::prev(wordPos));
                continue;
            }
            ++wordPos;
        }
        groups.push_back(std::move(group));
    }
    return groups;
}

void TestGroupingABC() {
    vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
    ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
    vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
    ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
    ASSERT_EQUAL(groups[2], vector<string>({"port"}));
    ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
    //    std::string symbols("abc");
    //    std::string word("abcabc");
    //    std::cout << std::boolalpha << includesSymbols(symbols, word) << std::endl;
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}
