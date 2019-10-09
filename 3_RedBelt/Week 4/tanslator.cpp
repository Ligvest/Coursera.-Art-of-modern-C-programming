#include <deque>
#include <map>
#include <string>
#include <string_view>
#include "test_runner.h"

using namespace std;

class Translator {
   public:
    void Add(string_view source, string_view target) {
        string_view& src = trgtToSrc_[target];
        string_view& trgt = srcToTrgt_[source];
        if (src == "") {
            src = dataBase_.emplace_back(source);
            trgt = dataBase_.emplace_back(target);
        } else {
            src = source;
            trgt = target;
        }
    }

    string_view TranslateForward(string_view source) const {
        std::string_view sv("");
        if (srcToTrgt_.count(source) > 0) {
            sv = srcToTrgt_.at(source);
        }
        return sv;
    }
    string_view TranslateBackward(string_view target) const {
        std::string_view sv("");
        if (trgtToSrc_.count(target) > 0) {
            sv = trgtToSrc_.at(target);
        }
        return sv;
    }

   private:
    std::map<std::string_view, std::string_view> srcToTrgt_;
    std::map<std::string_view, std::string_view> trgtToSrc_;
    std::deque<std::string> dataBase_{2, ""};
};

void TestSimple() {
    Translator translator;
    {
        std::string okno("okno");
        translator.Add(okno, string("window"));
    }
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");

    ASSERT_EQUAL(translator.TranslateForward("stol"), "table");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    translator.Add(string("stol"), string("aatable"));
    ASSERT_EQUAL(translator.TranslateForward("stol"), "aatable");
    ASSERT_EQUAL(translator.TranslateBackward("aatable"), "stol");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    std::string_view sv("hello");
    std::string s("string");
    sv = s;
    std::cout << s << std::endl;
    std::cout << sv << std::endl;
    return 0;
}
