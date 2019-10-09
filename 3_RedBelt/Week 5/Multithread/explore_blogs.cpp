#include <functional>
#include <future>
#include <string_view>
#include "profile.h"
#include "test_runner.h"

#include <map>
#include <string>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats& other) {
        for (auto wordAndFreq : other.word_frequences) {
            word_frequences[wordAndFreq.first] += wordAndFreq.second;
        }
    }
};

void removeSpaces(std::string_view& str) {
    while (std::isspace(str[0])) {
        str.remove_prefix(1);
    }
}

template <typename T>
void showSet(std::set<T> c) {
    for (auto item : c) {
        std::cout << item << ", ";
    }
    std::cout << std::endl;
}

template <typename K, typename V>
void showMap(std::map<K, V> c) {
    for (auto item : c) {
        std::cout << item.first << "(" << item.second << "), ";
    }
    std::cout << std::endl;
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats result;
    std::string_view words(line);
    while (!words.empty()) {
        removeSpaces(words);

        if (words.empty()) {
            break;
        }
        size_t wordLen = words.find(' ');
        std::string word = std::string(words.substr(0, wordLen));
        if (key_words.count(word) > 0) {
            ++result.word_frequences[word];
        }

        if (wordLen == words.npos) {
            break;
        } else {
            words.remove_prefix(wordLen);
        }
    }

    return result;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
    Stats result;
    for (string line; getline(input, line);) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats result;
    using KeyWords = std::set<std::string>;
    std::vector<KeyWords> keyWordsParts;

    std::vector<future<Stats>> futures;
    size_t numOfThreads = 8;

    // we can't read from one stream in several threads
    std::vector<stringstream> inputs;
    for (int i = 0; i < numOfThreads; ++i) {
        std::stringstream ss;
        ss << input.rdbuf();
        input.clear();
        input.seekg(0);
        inputs.push_back(std::move(ss));
    }

    keyWordsParts.reserve(numOfThreads);
    size_t partSize = (key_words.size() / numOfThreads) + 1;
    auto allKeysPos = key_words.begin();
    for (int curPart = 0; curPart < numOfThreads; ++curPart) {
        KeyWords keyWordsPart;
        for (int curWord = 0; curWord < partSize; ++curWord) {
            if (allKeysPos == key_words.end()) {
                break;
            }
            keyWordsPart.insert(*(allKeysPos++));
        }

        keyWordsParts.push_back(std::move(keyWordsPart));
        futures.push_back(
            async(ExploreKeyWordsSingleThread, ref(keyWordsParts.back()), ref(inputs[curPart])));

        if (allKeysPos == key_words.end()) {
            break;
        }
    }

    for (auto& future : futures) {
        result += future.get();
    }

    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {{"yangle", 6}, {"rocks", 2}, {"sucks", 1}};
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
