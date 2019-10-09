#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "profiler.h"

using namespace std;

class Learner {
   private:
    std::set<string> dict;

   public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        for (const auto& word : words) {
            if (!dict.count(word)) {
                ++newWords;
                dict.insert(word);
            }
        }
        return newWords;
    }

    vector<string> KnownWords() { return std::vector<std::string>(dict.begin(), dict.end()); }
};

int main() {
    Learner learner;
    string line("one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve");
    //    while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
    //    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}

// int main() {
//    int number = 0;
//    vector<string> words;
//    words.resize(20000, "");
//    std::generate(words.begin(), words.end(), [&]() { return std::to_string(number++); });
//    std::random_shuffle(words.begin(), words.end());

//    Learner learner;
//    {
//        LOG_DURATION("Total");
//        {
//            LOG_DURATION("Learn");
//            learner.Learn(words);
//        }

//        {
//            LOG_DURATION("KnownWords()");
//            learner.KnownWords();
//        }
//    }

//    return 0;
//}
